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
	    template<typename OtherType>
	    friend struct VariateProxy;
	private:
	    template<typename T>
        struct ArrayProxyTraits
	    {
	        static constexpr bool value = false;
	    };

	    template<typename T> requires (!ArrayProxyTraits<T>::value)
        struct ArrayProxyTraits<VariateProxy<T>>
	    {
	        static constexpr bool value = true;
	    };

	    template<typename T>
        struct Texture2DProxyTraits
	    {
	        static constexpr bool value = false;
	    };

	    template<typename T> requires (!ArrayProxyTraits<T>::value)
        struct Texture2DProxyTraits<VariateProxy<VariateProxy<T>>>
	    {
	        static constexpr bool value = true;
	    };
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

		VariateProxy() requires ArrayProxyTraits<Type>::value
		{
			node = Ast::AST::defineUniversalArray<typename Type::value_type>();
		}

	    VariateProxy() requires Texture2DProxyTraits<Type>::value
		{
		    node = Ast::AST::defineUniversalTexture2D<typename Type::value_type::value_type>();
		}

		VariateProxy(const VariateProxy& value)
		{
			//Local Variate
			node = Ast::AST::defineLocalVariate(value.node->type, value.node);
		}

		VariateProxy(VariateProxy&& value) = default;

		~VariateProxy()
		{
		}

		Type operator[](uint32_t input) requires ArrayProxyTraits<Type>::value
		{
			return Type(Ast::AST::at(reinterpret_cast<std::shared_ptr<Ast::Variate>&>(node), input));
		}

	    template<typename IndexType>
	    Type operator[](const VariateProxy<IndexType>& input) requires ArrayProxyTraits<Type>::value && std::is_integral_v<IndexType>
	    {
	        return Type(Ast::AST::at(reinterpret_cast<std::shared_ptr<Ast::Variate>&>(node), input.node));
	    }

	    template<typename IndexType> requires std::is_integral_v<IndexType>
	    auto operator[](ktm::vec<2,IndexType> input) requires Texture2DProxyTraits<Type>::value
	    {
	        return typename Type::value_type(Ast::AST::at(reinterpret_cast<std::shared_ptr<Ast::Variate>&>(node), input));
	    }

	    template<typename IndexType> requires std::is_integral_v<IndexType>
        auto operator[](const VariateProxy<ktm::vec<2,IndexType>>& input) requires Texture2DProxyTraits<Type>::value
        {
            return typename Type::value_type(Ast::AST::at(reinterpret_cast<std::shared_ptr<Ast::Variate>&>(node), input.node));
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

		VariateProxy& operator=(const VariateProxy& rhs) requires (!ArrayProxyTraits<Type>::value && !Texture2DProxyTraits<Type>::value)
		{
			if (this == &rhs)
				return *this;
		    Ast::AST::assign(node,rhs.node);
		    return *this;
		}

		VariateProxy& operator=(const Type& rhs) requires (!ArrayProxyTraits<Type>::value && !Texture2DProxyTraits<Type>::value)
		{
			Ast::AST::assign(node,Ast::AST::createValue(rhs));
			return *this;
		}

		VariateProxy& operator=(Type&& rhs) requires (!ArrayProxyTraits<Type>::value && !Texture2DProxyTraits<Type>::value)
		{
			Ast::AST::assign(node,Ast::AST::createValue(std::forward<Type>(rhs)));
			return *this;
		}

		VariateProxy& operator++()
		{
			return *this;
		}

		VariateProxy& operator--()
		{
			return *this;
		}

		VariateProxy& operator++(int)
		{
			return *this;
		}

		VariateProxy& operator--(int)
		{
			return *this;
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

		VariateProxy& operator!()
		{
			return *this;
		}

		VariateProxy& operator||(const VariateProxy& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,"||");
			return *this;
		}

		VariateProxy& operator&&(const VariateProxy& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,"&&");
			return *this;
		}

		VariateProxy& operator~()
		{
			return *this;
		}

		VariateProxy& operator&(const VariateProxy& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,"&");
			return *this;
		}

		VariateProxy& operator|(const VariateProxy& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,"|");
			return *this;
		}

		VariateProxy& operator^(const VariateProxy& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,"^");
			return *this;
		}

		VariateProxy& operator<<(const VariateProxy& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,"<<");
			return *this;
		}

		VariateProxy& operator>>(const VariateProxy& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,">>");
			return *this;
		}

		VariateProxy& operator+=(const VariateProxy& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,"+=");
			return *this;
		}

		VariateProxy& operator-=(const VariateProxy& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,"-=");
			return *this;
		}

		VariateProxy& operator*=(const VariateProxy& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,"*=");
			return *this;
		}

		VariateProxy& operator/=(const VariateProxy& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,"/=");
			return *this;
		}

		VariateProxy& operator%=(const VariateProxy& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,"%=");
			return *this;
		}

		VariateProxy& operator&=(const VariateProxy& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,"&=");
			return *this;
		}

		VariateProxy& operator|=(const VariateProxy& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,"|=");
			return *this;
		}

		VariateProxy& operator^=(const VariateProxy& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,"^=");
			return *this;
		}

		VariateProxy& operator>>=(const VariateProxy& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,">>=");
			return *this;
		}

		VariateProxy& operator<<=(const VariateProxy& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,"<<=");
			return *this;
		}
		
		VariateProxy<bool>& operator>(const VariateProxy& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,">");
			return *(new VariateProxy<bool>(true));
		}

		VariateProxy<bool>& operator>=(const VariateProxy& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,">=");
			return *(new VariateProxy<bool>(true));
		}

		VariateProxy<bool>& operator<(const VariateProxy& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,"<");
			return *(new VariateProxy<bool>(true));
		}

		VariateProxy<bool>& operator<=(const VariateProxy& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,"<=");
			return *(new VariateProxy<bool>(true));
		}

		VariateProxy<bool>& operator!=(const VariateProxy& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,"!=");
			return *(new VariateProxy<bool>(true));
		}

		VariateProxy<bool>& operator==(const VariateProxy& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,"==");
			return *(new VariateProxy<bool>(true));
		}


		//VariateProxy& operator+() { return *(new VariateProxy()); }
		//VariateProxy& operator-() { return *(new VariateProxy()); }
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

	protected:
		VariateProxy(std::shared_ptr<Ast::Value> node) : node(std::move(node))
		{
		}
		std::unique_ptr<Type> value{};
		std::shared_ptr<Ast::Value> node;
	};
}
