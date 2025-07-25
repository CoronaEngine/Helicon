#pragma once

#include "boost/pfr.hpp"
#include <sstream>
#include <regex>
#include <type_traits>
#include <cassert>
#include <unordered_map>
#include <string>
#include <tuple>
#include <ktm/ktm.h>
#include <ktm/type/vec.h>
#include <Codegen/AST/AST.hpp>
#include <Codegen/ParseHelper.h>
#include <Codegen/MathProxy.h>


namespace EmbeddedShader
{
	template<typename T>
	concept is_mathematical = requires(T a)
	{
		a = a + a;
		a = a - a;
	};

	template<typename Type>
	struct VariateProxy
	{
		template<typename T>
		friend struct ArrayProxy;
		template<typename T>
		friend struct Texture2DProxy;
	    template<typename OtherType>
	    friend struct VariateProxy;
		friend struct GPU_IF_BRANCH;
		friend struct GPU_ELSEIF_BRANCH;
		friend struct GPU_ELSE_BRANCH;
	public:
	    friend VariateProxy<ktm::fvec4> position();
		friend class RasterizedPipelineObject;
		friend class Generator::SlangGenerator;
		using value_type = Type;
		VariateProxy()
		{
            value = std::make_unique<Type>();

            if (ParseHelper::notInitNode())
		        return;

			if (auto parent = ParseHelper::getVecParent())
			{
				auto name = ParseHelper::getVecComponentName();
				node = Ast::AST::access(parent,name,Ast::AST::createType<Type>());
				return;
			}

            if (auto parent = ParseHelper::getAggregateParent())
		    {
		        auto index = ParseHelper::getAggregateMemberIndex();
		        auto aggregateType = reinterpret_cast<Ast::AggregateType*>(parent->type.get());
		        auto member = aggregateType->members[index];
		        node = Ast::AST::access(parent,member->name, member->type);
		        return;
		    }

			//Uniform,Input,Local Variate
			if (ParseHelper::isInInputParameter())
			{
				node = Ast::AST::defineInputVariate<Type>(ParseHelper::getCurrentInputIndex());
				return;
			}

			if (ParseHelper::isInShaderCodeLambda())
			{
				node = Ast::AST::defineLocalVariate<Type>({});
				return;
			}
			node = Ast::AST::defineUniformVariate<Type>();
		}

	    VariateProxy() requires std::is_aggregate_v<Type>
		{
		    if (ParseHelper::notInitNode())
		    {
		        value = std::make_unique<Type>();
		        return;
		    }

            //Uniform,Input,Local Variate
		    ParseHelper::beginNotInitNode();
		    if (auto parent = ParseHelper::getAggregateParent())
		    {
		        auto index = ParseHelper::getAggregateMemberIndex();
		        auto aggregateType = reinterpret_cast<Ast::AggregateType*>(parent->type.get());
		        auto member = aggregateType->members[index];
		        node = Ast::AST::access(parent,member->name, member->type);
		    }
		    else if (ParseHelper::isInInputParameter())
		    {
		        node = Ast::AST::defineInputVariate<Type>(ParseHelper::getCurrentInputIndex());
		    }
		    else if (ParseHelper::isInShaderCodeLambda())
		    {
		        node = Ast::AST::defineLocalVariate<Type>({});
		    }
		    else
		    {
		        node = Ast::AST::defineUniformVariate<Type>();
		    }
		    ParseHelper::endNotInitNode();

            ParseHelper::beginAggregateParent(node);
		    value = std::make_unique<Type>();
		    ParseHelper::endAggregateParent();
		}

		VariateProxy(const Type& value) requires (!std::is_aggregate_v<Type>)
		{
		    if (ParseHelper::notInitNode())
		    {
		        this->value = std::make_unique<Type>(value);
		        return;
		    }

			//Local Variate
			if (ParseHelper::isInShaderCodeLambda())
			{
				node = Ast::AST::defineLocalVariate(value);
				return;
			}

			node = Ast::AST::defineUniformVariate<Type>();
		}

		VariateProxy(const VariateProxy& value)
		{
			//Local Variate
			node = Ast::AST::defineLocalVariate(value.node->type, value.node);
		}

		VariateProxy(VariateProxy&& value) = default;

		~VariateProxy()
		{
			if (isNeedUniversalStatementCheck && node && node.use_count() == 1)
				Ast::AST::addLocalUniversalStatement(node);
		}

		Type* operator->() requires (std::is_aggregate_v<Type> && !ktm::is_vector_v<Type>)
		{
			return value.get();
		}

		auto operator->() requires (ktm::is_vector_v<Type>)
		{
			ParseHelper::beginVecComponentInit(node);
			auto vecComponents = std::make_unique<typename VecProxyMap<Type>::proxy_type>();
			vecComponents->parent = node;
			ParseHelper::endVecComponentInit();
			return std::move(vecComponents);
		}

		VariateProxy& operator=(const VariateProxy& rhs)
		{
			if (this == &rhs)
				return *this;
		    Ast::AST::assign(node,rhs.node);
		    return *this;
		}

		VariateProxy& operator=(const Type& rhs)
		{
			Ast::AST::assign(node,Ast::AST::createValue(rhs));
			return *this;
		}

		VariateProxy& operator=(Type&& rhs)
		{
			Ast::AST::assign(node,Ast::AST::createValue(std::forward<Type>(rhs)));
			return *this;
		}

		const VariateProxy operator++()
		{
			VariateProxy proxy(Ast::AST::unaryOperator(node,"++",true,Ast::AccessPermissions::ReadAndWrite));
			proxy.isNeedUniversalStatementCheck = true;
			return proxy;
		}

		const VariateProxy operator--()
		{
			VariateProxy proxy(Ast::AST::unaryOperator(node,"--",true,Ast::AccessPermissions::ReadAndWrite));
			proxy.isNeedUniversalStatementCheck = true;
			return proxy;
		}

		const VariateProxy operator++(int)
		{
			VariateProxy proxy(Ast::AST::unaryOperator(node,"++",false,Ast::AccessPermissions::ReadAndWrite));
			proxy.isNeedUniversalStatementCheck = true;
			return proxy;
		}

		const VariateProxy operator--(int)
		{
			VariateProxy proxy(Ast::AST::unaryOperator(node,"--",false,Ast::AccessPermissions::ReadAndWrite));
			proxy.isNeedUniversalStatementCheck = true;
			return proxy;
		}

		VariateProxy operator+(const VariateProxy& rhs) const
		{
			return VariateProxy(Ast::AST::binaryOperator(node,rhs.node,"+"));
		}

		VariateProxy operator-(const VariateProxy& rhs)
		{
			return VariateProxy(Ast::AST::binaryOperator(node,rhs.node,"-"));
		}

		VariateProxy operator*(const VariateProxy& rhs)
		{
			return VariateProxy(Ast::AST::binaryOperator(node,rhs.node,"*"));
		}

		VariateProxy operator/(const VariateProxy& rhs)
		{
			return VariateProxy(Ast::AST::binaryOperator(node,rhs.node,"/"));
		}

		VariateProxy operator%(const VariateProxy& rhs)
		{
			return VariateProxy(Ast::AST::binaryOperator(node,rhs.node,"%"));
		}

		VariateProxy operator!()
		{
			return VariateProxy(Ast::AST::unaryOperator(node,"!"));
		}

		VariateProxy operator||(const VariateProxy& rhs)
		{
			return VariateProxy(Ast::AST::binaryOperator(node,rhs.node,"||"));
		}

		VariateProxy operator&&(const VariateProxy& rhs)
		{
			return VariateProxy(Ast::AST::binaryOperator(node,rhs.node,"&&"));
		}

		VariateProxy operator~()
		{
			return VariateProxy(Ast::AST::unaryOperator(node,"~"));
		}

		VariateProxy operator&(const VariateProxy& rhs)
		{
			return VariateProxy(Ast::AST::binaryOperator(node,rhs.node,"&"));
		}

		VariateProxy operator|(const VariateProxy& rhs)
		{
			return VariateProxy(Ast::AST::binaryOperator(node,rhs.node,"|"));
		}

		VariateProxy operator^(const VariateProxy& rhs)
		{
			return VariateProxy(Ast::AST::binaryOperator(node,rhs.node,"^"));
		}

		VariateProxy operator<<(const VariateProxy& rhs)
		{
			return VariateProxy(Ast::AST::binaryOperator(node,rhs.node,"<<"));
		}

		VariateProxy operator>>(const VariateProxy& rhs)
		{
			return VariateProxy(Ast::AST::binaryOperator(node,rhs.node,">>"));
		}

		VariateProxy& operator+=(const VariateProxy& rhs)
		{
			return *this = *this + rhs;
		}

		VariateProxy& operator-=(const VariateProxy& rhs)
		{
			return *this = *this - rhs;
		}

		VariateProxy& operator*=(const VariateProxy& rhs)
		{
			return *this = *this * rhs;
		}

		VariateProxy& operator/=(const VariateProxy& rhs)
		{
			return *this = *this / rhs;
		}

		VariateProxy& operator%=(const VariateProxy& rhs)
		{
			return *this = *this % rhs;
		}

		VariateProxy& operator&=(const VariateProxy& rhs)
		{
			return *this = *this & rhs;
		}

		VariateProxy& operator|=(const VariateProxy& rhs)
		{
			return *this = *this | rhs;
		}

		VariateProxy& operator^=(const VariateProxy& rhs)
		{
			return *this = *this ^ rhs;
		}

		VariateProxy& operator>>=(const VariateProxy& rhs)
		{
			return *this = *this >> rhs;
		}

		VariateProxy& operator<<=(const VariateProxy& rhs)
		{
			return *this = *this << rhs;
		}
		
		VariateProxy<bool> operator>(const VariateProxy& rhs)
		{
			return VariateProxy<bool>(Ast::AST::binaryOperator(node,rhs.node,">",Ast::AST::createType<bool>()));
		}

		VariateProxy<bool> operator>(const Type& rhs)
		{
			return VariateProxy<bool>(Ast::AST::binaryOperator(node,Ast::AST::createValue(rhs),">",Ast::AST::createType<bool>()));
		}

		VariateProxy<bool> operator>=(const VariateProxy& rhs)
		{
			return VariateProxy<bool>(Ast::AST::binaryOperator(node,rhs.node,">=",Ast::AST::createType<bool>()));
		}

		VariateProxy<bool> operator>=(const Type& rhs)
		{
			return VariateProxy<bool>(Ast::AST::binaryOperator(node,Ast::AST::createValue(rhs),">=",Ast::AST::createType<bool>()));
		}

		VariateProxy<bool> operator<(const VariateProxy& rhs)
		{
			return VariateProxy<bool>(Ast::AST::binaryOperator(node,rhs.node,"<",Ast::AST::createType<bool>()));
		}

		VariateProxy<bool> operator<(const Type& rhs)
		{
			return VariateProxy<bool>(Ast::AST::binaryOperator(node,Ast::AST::createValue(rhs),"<",Ast::AST::createType<bool>()));
		}

		VariateProxy<bool> operator<=(const VariateProxy& rhs)
		{
			return VariateProxy<bool>(Ast::AST::binaryOperator(node,rhs.node,"<=",Ast::AST::createType<bool>()));
		}

		VariateProxy<bool> operator<=(const Type& rhs)
		{
			return VariateProxy<bool>(Ast::AST::binaryOperator(node,Ast::AST::createValue(rhs),"<=",Ast::AST::createType<bool>()));
		}

		VariateProxy<bool> operator!=(const VariateProxy& rhs)
		{
			return VariateProxy<bool>(Ast::AST::binaryOperator(node,rhs.node,"!=",Ast::AST::createType<bool>()));
		}

		VariateProxy<bool> operator!=(const Type& rhs)
		{
			return VariateProxy<bool>(Ast::AST::binaryOperator(node,Ast::AST::createValue(rhs),"!=",Ast::AST::createType<bool>()));
		}

		VariateProxy<bool> operator==(const VariateProxy& rhs)
		{
			return VariateProxy<bool>(Ast::AST::binaryOperator(node,rhs.node,"==",Ast::AST::createType<bool>()));
		}

		VariateProxy<bool> operator==(const Type& rhs)
		{
			return VariateProxy<bool>(Ast::AST::binaryOperator(node,Ast::AST::createValue(rhs),"==",Ast::AST::createType<bool>()));
		}

		VariateProxy operator+() { return VariateProxy(Ast::AST::unaryOperator(node,"+")); }
		VariateProxy operator-() { return VariateProxy(Ast::AST::unaryOperator(node,"-")); }
		//VariateProxy& operator!() { return *(new VariateProxy()); }
		//VariateProxy& operator~() { return *(new VariateProxy()); }

		//VariateProxy& operator+(const VariateProxy& rhs) { return *(new VariateProxy()); }
		//VariateProxy& operator-(const VariateProxy& rhs) { return *(new VariateProxy()); }
		//VariateProxy& operator*(const VariateProxy& rhs) { return *(new VariateProxy()); }
		//VariateProxy& operator/(const VariateProxy& rhs) { return *(new VariateProxy()); }
		//VariateProxy& operator%(const VariateProxy& rhs) { return *(new VariateProxy()); }
		//VariateProxy& operator||(const VariateProxy& rhs) { return *(new VariateProxy()); }
		//VariateProxy& operator&&(const VariateProxy& rhs) { return *(new VariateProxy()); }
		//VariateProxy& operator&(const VariateProxy& rhs) { return *(new VariateProxy()); }
		//VariateProxy& operator|(const VariateProxy& rhs) { return *(new VariateProxy()); }
		//VariateProxy& operator^(const VariateProxy& rhs) { return *(new VariateProxy()); }
		//VariateProxy& operator<<(const VariateProxy& rhs) { return *(new VariateProxy()); }
		//VariateProxy& operator>>(const VariateProxy& rhs) { return *(new VariateProxy()); }
		//VariateProxy& operator+=(const VariateProxy& rhs) { return *(new VariateProxy()); }
		//VariateProxy& operator-=(const VariateProxy& rhs) { return *(new VariateProxy()); }
		//VariateProxy& operator*=(const VariateProxy& rhs) { return *(new VariateProxy()); }
		//VariateProxy& operator/=(const VariateProxy& rhs) { return *(new VariateProxy()); }
		//VariateProxy& operator%=(const VariateProxy& rhs) { return *(new VariateProxy()); }
		//VariateProxy& operator&=(const VariateProxy& rhs) { return *(new VariateProxy()); }
		//VariateProxy& operator|=(const VariateProxy& rhs) { return *(new VariateProxy()); }
		//VariateProxy& operator^=(const VariateProxy& rhs) { return *(new VariateProxy()); }
		//VariateProxy& operator>>=(const VariateProxy& rhs) { return *(new VariateProxy()); }
		//VariateProxy& operator<<=(const VariateProxy& rhs) { return *(new VariateProxy()); }

		//VariateProxy<bool>& operator>(const VariateProxy& rhs) { return *(new VariateProxy<bool>(true)); }
		//VariateProxy<bool>& operator>=(const VariateProxy& rhs) { return *(new VariateProxy<bool>(true)); }
		//VariateProxy<bool>& operator<(const VariateProxy& rhs) { return *(new VariateProxy<bool>(true)); }
		//VariateProxy<bool>& operator<=(const VariateProxy& rhs) { return *(new VariateProxy<bool>(true)); }
		//VariateProxy<bool>& operator!=(const VariateProxy& rhs) { return *(new VariateProxy<bool>(true)); }
		//VariateProxy<bool>& operator==(const VariateProxy& rhs) { return *(new VariateProxy<bool>(true)); }

		VariateProxy(std::shared_ptr<Ast::Value> node) : node(std::move(node))//,value(std::make_unique<Type>())
	    {
	    }

	    std::unique_ptr<Type> value{};
		std::shared_ptr<Ast::Value> node;
		bool isNeedUniversalStatementCheck = false;
	};

	template<typename Type>
	struct Texture2DProxyTraits
	{
		static constexpr bool value = false;
	};

	template<typename Type>
	struct Texture2DProxyTraits<Texture2DProxy<Type>>
	{
		static constexpr bool value = true;
	};

	template<typename Type>
	struct ArrayProxy
	{
		using value_type = Type;
		ArrayProxy()
		{
			if (ParseHelper::notInitNode())
				return;

			if (auto parent = ParseHelper::getAggregateParent())
			{
				auto index = ParseHelper::getAggregateMemberIndex();
				auto aggregateType = reinterpret_cast<Ast::AggregateType*>(parent->type.get());
				auto member = aggregateType->members[index];
				node = Ast::AST::access(parent,member->name, member->type);
				return;
			}

			if constexpr (Texture2DProxyTraits<Type>::value)
			{
				auto textureType = std::make_shared<Ast::Texture2DType>();
				textureType->texelType = Ast::AST::createType<Type::value_type>();
				node = Ast::AST::defineUniversalArray(std::move(textureType));
			}
			else node = Ast::AST::defineUniversalArray<Type>();
		}

		template<std::integral IndexType>
		VariateProxy<Type> operator[](IndexType index)
		{
			if constexpr (std::is_aggregate_v<Type>)
			{
				VariateProxy<Type> proxy{Ast::AST::at(node, index)};
				ParseHelper::beginAggregateParent(proxy.node);
				proxy->value = std::make_unique<Type>();
				ParseHelper::endAggregateParent(proxy.node);
				return proxy;
			}
			else return {Ast::AST::at(node, index)};
		}

		template<std::integral IndexType>
		VariateProxy<Type> operator[](VariateProxy<IndexType> index)
		{
			if constexpr (std::is_aggregate_v<Type>)
			{
				VariateProxy<Type> proxy{Ast::AST::at(node, index.node)};
				ParseHelper::beginAggregateParent(proxy.node);
				proxy->value = std::make_unique<Type>();
				ParseHelper::endAggregateParent(proxy.node);
				return proxy;
			}
			return {Ast::AST::at(node, index.node)};
		}

		template<std::integral IndexType>
		Type operator[](IndexType index) requires Texture2DProxyTraits<Type>::value
		{
			return {Ast::AST::at(node, index)};
		}

		template<std::integral IndexType>
		Type operator[](VariateProxy<IndexType> index) requires Texture2DProxyTraits<Type>::value
		{
			return {Ast::AST::at(node, index.node)};
		}
	private:
		std::shared_ptr<Ast::Value> node;
	};

	template<typename Type>
	struct Texture2DProxy
	{
		using value_type = Type;
		Texture2DProxy()
		{
			if (ParseHelper::notInitNode())
				return;

			if (auto parent = ParseHelper::getAggregateParent())
			{
				auto index = ParseHelper::getAggregateMemberIndex();
				auto aggregateType = reinterpret_cast<Ast::AggregateType*>(parent->type.get());
				auto member = aggregateType->members[index];
				node = Ast::AST::access(parent,member->name, member->type);
				return;
			}

			node = Ast::AST::defineUniversalTexture2D<Type>();
		}

		template<std::integral IndexType>
		VariateProxy<Type> operator[](ktm::vec<2,IndexType> index)
		{
			if constexpr (std::is_aggregate_v<Type>)
			{
				VariateProxy<Type> proxy{Ast::AST::at(node, index)};
				ParseHelper::beginAggregateParent(proxy.node);
				proxy->value = std::make_unique<Type>();
				ParseHelper::endAggregateParent(proxy.node);
				return proxy;
			}
			else return {Ast::AST::at(node, index)};
		}

		template<std::integral IndexType>
		VariateProxy<Type> operator[](VariateProxy<ktm::vec<2,IndexType>> index)
		{
			if constexpr (std::is_aggregate_v<Type>)
			{
				VariateProxy<Type> proxy{Ast::AST::at(node, index.node)};
				ParseHelper::beginAggregateParent(proxy.node);
				proxy->value = std::make_unique<Type>();
				ParseHelper::endAggregateParent(proxy.node);
				return proxy;
			}
			return {Ast::AST::at(node, index.node)};
		}

		Texture2DProxy(std::shared_ptr<Ast::Value> node) : node(std::move(node)) {}
	private:
		std::shared_ptr<Ast::Value> node;
	};
}
