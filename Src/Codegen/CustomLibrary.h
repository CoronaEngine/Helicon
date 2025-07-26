#pragma once

#include <ktm/ktm.h>
#include <Codegen/VariateProxy.h>
#include <Codegen/AST/Node.hpp>

namespace EmbeddedShader
{
	template<typename Type>
	VariateProxy<Type> abs(const VariateProxy<Type>& a)
	{
		a.node->access(Ast::AccessPermissions::ReadOnly);
		return {Ast::AST::callFunc("abs", Ast::AST::createType<Type>(),{a.node})};
	}

	template<typename Type>
	VariateProxy<Type> pow(const VariateProxy<Type>& x,const VariateProxy<Type>& y)
	{
		return {Ast::AST::callFunc("pow", Ast::AST::createType<Type>(),Ast::Node::accessAll({x.node,y.node},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type>
	VariateProxy<Type> clamp(const VariateProxy<Type>& x, const VariateProxy<Type>& min,const VariateProxy<Type>& max)
	{
		return {Ast::AST::callFunc("clamp", Ast::AST::createType<Type>(),Ast::Node::accessAll({x.node, min.node,max.node},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type> requires ktm::is_vector_v<Type>
	VariateProxy<Type> normalize(const VariateProxy<Type>& x)
	{
		return VariateProxy<Type>{Ast::AST::callFunc("normalize", Ast::AST::createType<Type>(),Ast::Node::accessAll({x.node},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type>
	VariateProxy<Type> max(const VariateProxy<Type>& a, const VariateProxy<Type>& b)
	{
		return {Ast::AST::callFunc("max", Ast::AST::createType<Type>(),Ast::Node::accessAll({a.node, b.node},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type>
	VariateProxy<Type> min(const VariateProxy<Type>& a, const VariateProxy<Type>& b)
	{
		return {Ast::AST::callFunc("min", Ast::AST::createType<Type>(),Ast::Node::accessAll({a.node, b.node},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type,size_t N>
	VariateProxy<Type> dot(const VariateProxy<ktm::vec<N,Type>>& a, const VariateProxy<ktm::vec<N,Type>>& b)
	{
		return {Ast::AST::callFunc("dot", Ast::AST::createType<Type>(),Ast::Node::accessAll({a.node, b.node},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type>
	VariateProxy<Type> lerp(const VariateProxy<Type>& x, const VariateProxy<Type>& y,const VariateProxy<Type>& s)
	{
		return {Ast::AST::callFunc("lerp", Ast::AST::createType<Type>(),Ast::Node::accessAll({x.node, y.node,s.node},Ast::AccessPermissions::ReadOnly))};
	}

	template<size_t N,typename Type>
	VariateProxy<ktm::vec<N,Type>> lerp(const VariateProxy<ktm::vec<N,Type>>& x, const VariateProxy<ktm::vec<N,Type>>& y,const VariateProxy<Type>& s)
	{
		return VariateProxy<ktm::vec<N,Type>>{Ast::AST::callFunc("lerp", Ast::AST::createType<Type>(),Ast::Node::accessAll({x.node, y.node,s.node},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type>
	VariateProxy<Type> mix(const VariateProxy<Type>& x, const VariateProxy<Type>& y,const VariateProxy<Type>& s)
	{
		return lerp(x,y,s);
	}

	template<size_t N,typename Type>
	VariateProxy<ktm::vec<N,Type>> mix(const VariateProxy<ktm::vec<N,Type>>& x, const VariateProxy<ktm::vec<N,Type>>& y,const VariateProxy<Type>& s)
	{
		return lerp(x,y,s);
	}

	template<typename Type,size_t Rows,size_t Columns>
	VariateProxy<ktm::mat<Columns,Rows,Type>> transpose(const VariateProxy<ktm::mat<Rows,Columns,Type>>& x)
	{
		x.node->access(Ast::AccessPermissions::ReadOnly);
		return {Ast::AST::callFunc("transpose", Ast::AST::createType<ktm::mat<Columns,Rows,Type>>(),{x.node})};
	}

	// template<typename Type> requires ktm::is_matrix_v<Type>
	// VariateProxy<Type> inverse(const VariateProxy<Type>& x)
	// {
	// 	return {Ast::AST::callFunc("inverse", Ast::AST::createType<Type>(),{x.node})};
	// }

	template<typename Type> requires std::is_arithmetic_v<Type>
	VariateProxy<Type> mul(const VariateProxy<Type>& x, const VariateProxy<Type>& y)
	{
		return {Ast::AST::callFunc("mul", Ast::AST::createType<Type>(),Ast::Node::accessAll({x.node, y.node},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type1, typename Type2> requires (std::is_arithmetic_v<Type1> && (ktm::is_vector_v<Type2> || ktm::is_matrix_v<Type2>))
	VariateProxy<Type2> mul(const VariateProxy<Type1>& x, const VariateProxy<Type2>& y)
	{
		return {Ast::AST::callFunc("mul", Ast::AST::createType<Type2>(),Ast::Node::accessAll({x.node, y.node},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type1, typename Type2> requires (ktm::is_vector_v<Type1> && std::is_arithmetic_v<Type2>)
	VariateProxy<Type1> mul(const VariateProxy<Type1>& x, const VariateProxy<Type2>& y)
	{
		return {Ast::AST::callFunc("mul", Ast::AST::createType<Type1>(),Ast::Node::accessAll({x.node, y.node},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type,size_t N>
	VariateProxy<Type> mul(const VariateProxy<ktm::vec<N,Type>>& a, const VariateProxy<ktm::vec<N,Type>>& b)
	{
		return {Ast::AST::callFunc("mul", Ast::AST::createType<Type>(),Ast::Node::accessAll({a.node, b.node},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type,size_t N,size_t Columns>
	VariateProxy<ktm::vec<N,Type>> mul(const VariateProxy<ktm::vec<N,Type>>& a, const VariateProxy<ktm::mat<N,Columns,Type>>& b)
	{
		return {Ast::AST::callFunc("mul", Ast::AST::createType<ktm::vec<N,Type>>(),Ast::Node::accessAll({a.node, b.node},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type1, typename Type2> requires (ktm::is_matrix_v<Type1> && std::is_arithmetic_v<Type2>)
	VariateProxy<Type1> mul(const VariateProxy<Type1>& x, const VariateProxy<Type2>& y)
	{
		return {Ast::AST::callFunc("mul", Ast::AST::createType<Type1>(),Ast::Node::accessAll({x.node, y.node},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type,size_t Rows,size_t Columns>
	VariateProxy<ktm::vec<Rows,Type>> mul(const VariateProxy<ktm::mat<Rows,Columns,Type>>& a, const VariateProxy<ktm::vec<Columns,Type>>& b)
	{
		auto func = Ast::AST::callFunc("mul", Ast::AST::createType<ktm::vec<Rows,Type>>(),Ast::Node::accessAll({a.node, b.node},Ast::AccessPermissions::ReadOnly));
		return VariateProxy<ktm::vec<Rows,Type>>{func};
	}

	template<typename Type,size_t Rows,size_t Columns,size_t ColumnsB>
	VariateProxy<ktm::mat<Rows,ColumnsB,Type>> mul(const VariateProxy<ktm::mat<Rows,Columns,Type>>& a, const VariateProxy<ktm::mat<Columns,ColumnsB,Type>>& b)
	{
		return {Ast::AST::callFunc("mul", Ast::AST::createType<ktm::mat<Rows,ColumnsB,Type>>(),Ast::Node::accessAll({a.node, b.node},Ast::AccessPermissions::ReadOnly))};
	}
}
