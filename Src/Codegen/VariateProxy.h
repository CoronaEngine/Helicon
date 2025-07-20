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
		using value_type = Type;
		VariateProxy()
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

		VariateProxy(const Type& value)
		{
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

		VariateProxy(VariateProxy&& value)
		{
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
			puts("c");
			fflush(stdout);
		}
		Type* value{};
		std::shared_ptr<Ast::Value> node;
	};
}
