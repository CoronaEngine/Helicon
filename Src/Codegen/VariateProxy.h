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
		friend class RasterizedPipelineObject;
		friend class Generator::SlangGenerator;
		using value_type = Type;
		VariateProxy()
		{
            value = std::make_unique<Type>();
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

		VariateProxy(const Type& value) requires !std::is_aggregate_v<Type>
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

		VariateProxy(const std::initializer_list<Type>& value)
		{
			//Array 后续特化
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

		VariateProxy& operator[](uint32_t input)
		{
			//Array 后续特化
			return *(new VariateProxy());
		}

		Type* operator->()
		{
			return value.get();
		}

		VariateProxy& operator=(const VariateProxy& rhs)
		{
			Ast::AST::assign(node,rhs.node);
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


	private:
		VariateProxy(std::shared_ptr<Ast::Value> node) : node(std::move(node))
		{
		}
		std::unique_ptr<Type> value{};
		std::shared_ptr<Ast::Value> node;
	};
}
