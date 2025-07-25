#pragma once

#include <ktm/ktm.h>
#include "VariateProxy.h"

namespace EmbeddedShader
{
	template<typename Type>
	VariateProxy<Type> abs(const VariateProxy<Type>& a)
	{
		return {Ast::AST::callFunc("abs", Ast::AST::createType<Type>(),{a.node})};
	}

	template<typename Type>
	VariateProxy<Type> pow(const VariateProxy<Type>& x,const VariateProxy<Type>& y)
	{
		return {Ast::AST::callFunc("pow", Ast::AST::createType<Type>(),{x.node,y.node})};
	}

	template<typename Type>
	VariateProxy<Type> clamp(const VariateProxy<Type>& x, const VariateProxy<Type>& min,const VariateProxy<Type>& max)
	{
		return {Ast::AST::callFunc("clamp", Ast::AST::createType<Type>(),{x.node, min.node,max.node})};
	}

	template<typename Type> requires ktm::is_vector_v<Type>
	VariateProxy<Type> normalize(const VariateProxy<Type>& x)
	{
		return {Ast::AST::callFunc("normalize", Ast::AST::createType<Type>(),{x.node})};
	}

	template<typename Type>
	VariateProxy<Type> max(const VariateProxy<Type>& a, const VariateProxy<Type>& b)
	{
		return {Ast::AST::callFunc("max", Ast::AST::createType<Type>(),{a.node, b.node})};
	}

	template<typename Type>
	VariateProxy<Type> min(const VariateProxy<Type>& a, const VariateProxy<Type>& b)
	{
		return {Ast::AST::callFunc("min", Ast::AST::createType<Type>(),{a.node, b.node})};
	}

	template<size_t N,typename Type>
	VariateProxy<Type> dot(const VariateProxy<ktm::vec<N,Type>>& a, const VariateProxy<ktm::vec<N,Type>>& b)
	{
		return {Ast::AST::callFunc("dot", Ast::AST::createType<Type>(),{a.node, b.node})};
	}

	template<typename Type>
	VariateProxy<Type> lerp(const VariateProxy<Type>& x, const VariateProxy<Type>& y,const VariateProxy<Type>& s)
	{
		return {Ast::AST::callFunc("lerp", Ast::AST::createType<Type>(),{x.node, y.node,s.node})};
	}

	template<typename Type>
	VariateProxy<Type> mix(const VariateProxy<Type>& x, const VariateProxy<Type>& y,const VariateProxy<Type>& s)
	{
		return lerp(x,y,s);
	}
}
