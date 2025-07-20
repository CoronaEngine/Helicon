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
	public:
		VariateProxy()// requires (std::is_class<Type>::value&& std::is_aggregate<Type>::value && !is_mathematical<Type>)
		{
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

		VariateProxy() requires (std::is_class<Type>::value&& std::is_aggregate<Type>::value && !is_mathematical<Type>)
		{
			//Uniform,Input,Local Variate
		}

		VariateProxy(const Type& value) requires is_mathematical<Type>&& std::is_fundamental<Type>::value
		{
			//Local Variate
			node = Ast::AST::defineLocalVariate<Type>(value);
		}


		VariateProxy(const Type& value) requires (is_mathematical<Type> && !std::is_fundamental<Type>::value)
		{
			node = Ast::AST::defineLocalVariate<Type>(value);
		}


		VariateProxy(const Type& value) requires (std::is_class<Type>::value&& std::is_aggregate<Type>::value && !is_mathematical<Type>)
		{
			auto lammdaReflect = [&](auto& structMember)
				{
				};

			boost::pfr::for_each_field(value, lammdaReflect);
		}

		VariateProxy(const std::initializer_list<Type>& value)
		{
			//Array 后续特化
		}

		VariateProxy(const VariateProxy<Type>& value)
		{
			//Input(from Output),Local Variate
			// if (auto outputVar = std::dynamic_pointer_cast<Ast::OutputVariate>(value.node);ParseHelper::isInInputParameter() && outputVar)
			// {
			// 	node = Ast::AST::defineInputVariate(outputVar->type,outputVar->location);
			// 	return;
			// }
			node = Ast::AST::defineLocalVariate(reinterpret_cast<Ast::Variate*>(value.node.get())->type,value.node);
		}

		VariateProxy(VariateProxy&& value)
		{
			auto outputVar = std::dynamic_pointer_cast<Ast::OutputVariate>(value.node);
			puts("move!");
			fflush(stdout);
			if (ParseHelper::isInInputParameter() && outputVar)
			{
				node = Ast::AST::defineInputVariate(outputVar->type,outputVar->location);
				return;
			}
			node = std::move(value.node);
		}

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
			return value;
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

		VariateProxy& operator+(const Type& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,"+");
			return *this;
		}

		VariateProxy& operator-(const Type& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,"-");
			return *this;
		}

		VariateProxy& operator*(const Type& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,"*");
			return *this;
		}

		VariateProxy& operator/(const Type& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,"/");
			return *this;
		}

		VariateProxy& operator%(const Type& rhs)
		{
			Ast::AST::binaryOperator(node,rhs.node,"%");
			return *this;
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
		Type* value;
		std::shared_ptr<Ast::Value> node;
	};
}
