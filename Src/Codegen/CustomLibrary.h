#pragma once

#include <ktm/ktm.h>
#include <Codegen/VariateProxy.h>
#include <Codegen/AST/Node.hpp>

namespace EmbeddedShader
{
	template<typename Type>
	VariateProxy<base_type_t<Type>> abs(Type&& a)
	{
		proxy_wrap(std::forward<Type>(a))->access(Ast::AccessPermissions::ReadOnly);
		return {Ast::AST::callFunc("abs", Ast::AST::createType<base_type_t<Type>>(),{proxy_wrap(std::forward<Type>(a))})};
	}

	template<typename Type>
	VariateProxy<base_type_t<Type>> pow(Type&& x, proxy_wrapper<Type> auto&& y)
	{
		return {Ast::AST::callFunc("pow", Ast::AST::createType<base_type_t<Type>>(),Ast::Node::accessAll({proxy_wrap(std::forward<Type>(x)),proxy_wrap(std::forward<Type>(y))},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type>
	VariateProxy<base_type_t<Type>> clamp(Type&& x, proxy_wrapper<Type> auto&& min,proxy_wrapper<Type> auto& max)
	{
		return {Ast::AST::callFunc("clamp", Ast::AST::createType<base_type_t<Type>>(),Ast::Node::accessAll({proxy_wrap(std::forward<Type>(x)), proxy_wrap(std::forward<Type>(min)),proxy_wrap(std::forward<Type>(max))},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type> requires ktm::is_vector_v<base_type_t<Type>>
	VariateProxy<base_type_t<Type>> normalize(Type&& x)
	{
		return VariateProxy<base_type_t<Type>>{Ast::AST::callFunc("normalize", Ast::AST::createType<base_type_t<Type>>(),Ast::Node::accessAll({proxy_wrap(std::forward<Type>(x))},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type>
	VariateProxy<base_type_t<Type>> max(Type&& a, proxy_wrapper<Type> auto&& b)
	{
		return {Ast::AST::callFunc("max", Ast::AST::createType<base_type_t<Type>>(),Ast::Node::accessAll({proxy_wrap(std::forward<Type>(a)), proxy_wrap(std::forward<Type>(b))},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type>
	VariateProxy<base_type_t<Type>> min(Type&& a, proxy_wrapper<Type> auto&& b)
	{
		return {Ast::AST::callFunc("min", Ast::AST::createType<base_type_t<Type>>(),Ast::Node::accessAll({proxy_wrap(std::forward<Type>(a)), proxy_wrap(std::forward<Type>(b))},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type> requires ktm::is_vector_v<base_type_t<Type>>
	VariateProxy<ktm::vec_traits_base_t<base_type_t<Type>>> dot(Type&& a, proxy_wrapper<Type> auto&& b)
	{
		return {Ast::AST::callFunc("dot", Ast::AST::createType<base_type_t<Type>>(),Ast::Node::accessAll({proxy_wrap(std::forward<Type>(a)), proxy_wrap(std::forward<Type>(b))},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type>
	VariateProxy<base_type_t<Type>> lerp(Type&& x, proxy_wrapper<Type> auto&& y,proxy_wrapper<Type> auto&& s)
	{
		return {Ast::AST::callFunc("lerp", Ast::AST::createType<base_type_t<Type>>(),Ast::Node::accessAll({proxy_wrap(std::forward<Type>(x)), proxy_wrap(std::forward<Type>(y)),proxy_wrap(std::forward<Type>(s))},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type> requires ktm::is_vector_v<base_type_t<Type>>
	VariateProxy<base_type_t<Type>> lerp(Type&& x, proxy_wrapper<Type> auto&& y,proxy_wrapper<ktm::vec_traits_base_t<base_type_t<Type>>> auto&& s)
	{
		return VariateProxy<base_type_t<Type>>{Ast::AST::callFunc("lerp", Ast::AST::createType<base_type_t<Type>>(),Ast::Node::accessAll({proxy_wrap(std::forward<Type>(x)), proxy_wrap(std::forward<Type>(y)),proxy_wrap(std::forward<Type>(s))},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type>
	VariateProxy<base_type_t<Type>> mix(Type&& x, proxy_wrapper<Type> auto&& y,proxy_wrapper<Type> auto&& s)
	{
		return lerp(x,y,s);
	}

	template<typename Type> requires ktm::is_vector_v<base_type_t<Type>>
	VariateProxy<base_type_t<Type>> mix(Type&& x, proxy_wrapper<Type> auto&& y,proxy_wrapper<ktm::vec_traits_base_t<base_type_t<Type>>> auto&& s)
	{
		return lerp(x,y,s);
	}

	template<typename Type> requires ktm::is_matrix_v<base_type_t<Type>>
	VariateProxy<ktm::mat<ktm::mat_traits_col_v<base_type_t<Type>>,ktm::mat_traits_row_v<base_type_t<Type>>,ktm::mat_traits_base_t<base_type_t<Type>>>> transpose(Type&& x)
	{
		proxy_wrap(std::forward<Type>(x))->access(Ast::AccessPermissions::ReadOnly);
		return {Ast::AST::callFunc("transpose", Ast::AST::createType<base_type_t<Type>>(),{proxy_wrap(std::forward<Type>(x))})};
	}

	// template<typename Type> requires ktm::is_matrix_v<Type>
	// VariateProxy<Type> inverse(const VariateProxy<Type>& x)
	// {
	// 	return {Ast::AST::callFunc("inverse", Ast::AST::createType<base_type_t<Type>>(),{x.node})};
	// }

	template<typename Type> requires std::is_arithmetic_v<base_type_t<Type>>
	VariateProxy<base_type_t<Type>> mul(Type&& x, proxy_wrapper<Type> auto&& y)
	{
		return {Ast::AST::callFunc("mul", Ast::AST::createType<base_type_t<Type>>(),Ast::Node::accessAll({proxy_wrap(std::forward<Type>(x)), proxy_wrap(std::forward<Type>(y))},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type1, typename Type2> requires (std::is_arithmetic_v<base_type_t<Type1>> && (ktm::is_vector_v<base_type_t<Type2>> || ktm::is_matrix_v<base_type_t<Type2>>))
	VariateProxy<base_type_t<Type2>> mul(Type1&& x, Type2&& y)
	{
		return {Ast::AST::callFunc("mul", Ast::AST::createType<base_type_t<Type2>>(),Ast::Node::accessAll({proxy_wrap(std::forward<Type1>(x)), proxy_wrap(std::forward<Type2>(y))},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type1, typename Type2> requires (ktm::is_vector_v<base_type_t<Type1>> && std::is_arithmetic_v<base_type_t<Type2>>)
	VariateProxy<base_type_t<Type1>> mul(Type1&& x, Type2&& y)
	{
		return {Ast::AST::callFunc("mul", Ast::AST::createType<base_type_t<Type1>>(),Ast::Node::accessAll({proxy_wrap(std::forward<Type1>(x)), proxy_wrap(std::forward<Type2>(y))},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type>
	VariateProxy<ktm::vec_traits_base_t<base_type_t<Type>>> mul(Type&& a, proxy_wrapper<Type> auto&& b)
	{
		return {Ast::AST::callFunc("mul", Ast::AST::createType<ktm::vec_traits_base_t<base_type_t<Type>>>(),Ast::Node::accessAll({proxy_wrap(std::forward<Type>(a)), proxy_wrap(std::forward<Type>(b))},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type1, typename Type2> requires (ktm::is_vector_v<base_type_t<Type1>> && ktm::is_matrix_v<base_type_t<Type2>> && std::same_as<ktm::vec_traits_base_t<base_type_t<Type1>>,ktm::mat_traits_base_t<base_type_t<Type2>>> && ktm::mat_traits_row_v<base_type_t<Type2>> == ktm::vec_traits_len<base_type_t<Type1>>)
	VariateProxy<base_type_t<Type1>> mul(Type1&& a, Type2&& b)
	{
		return {Ast::AST::callFunc("mul", Ast::AST::createType<base_type_t<Type1>>(),Ast::Node::accessAll({proxy_wrap(std::forward<Type1>(a)), proxy_wrap(std::forward<Type2>(a))},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type1, typename Type2> requires (ktm::is_matrix_v<base_type_t<Type1>> && std::is_arithmetic_v<base_type_t<Type2>>)
	VariateProxy<base_type_t<Type1>> mul(Type1&& x, Type2&& y)
	{
		return {Ast::AST::callFunc("mul", Ast::AST::createType<base_type_t<Type1>>(),Ast::Node::accessAll({proxy_wrap(std::forward<Type1>(x)), proxy_wrap(std::forward<Type2>(y))},Ast::AccessPermissions::ReadOnly))};
	}

	template<typename Type1,typename Type2> requires (ktm::is_matrix_v<base_type_t<Type1>> && ktm::is_vector_v<base_type_t<Type2>> && std::same_as<ktm::mat_traits_base_t<base_type_t<Type1>>,ktm::vec_traits_base_t<base_type_t<Type2>>> && ktm::mat_traits_col_v<base_type_t<Type1>> == ktm::vec_traits_len<base_type_t<Type2>>)
	VariateProxy<ktm::vec<ktm::mat_traits_row_v<base_type_t<Type1>>,ktm::vec_traits_base_t<base_type_t<Type1>>>> mul(Type1&& a,Type2&& b)//const VariateProxy<ktm::mat<Rows,Columns,Type>>& a, const VariateProxy<ktm::vec<Columns,Type>>& b)
	{
		return {Ast::AST::callFunc("mul", Ast::AST::createType<ktm::vec<ktm::mat_traits_row_v<base_type_t<Type1>>,ktm::vec_traits_base_t<base_type_t<Type1>>>>(),Ast::Node::accessAll({a.node, b.node},Ast::AccessPermissions::ReadOnly))};
	}

	//暂时禁掉，之后来补
	// template<typename Type,size_t Rows,size_t Columns,size_t ColumnsB>
	// VariateProxy<ktm::mat<Rows,ColumnsB,Type>> mul(const VariateProxy<ktm::mat<Rows,Columns,Type>>& a, const VariateProxy<ktm::mat<Columns,ColumnsB,Type>>& b)
	// {
	// 	return {Ast::AST::callFunc("mul", Ast::AST::createType<ktm::mat<Rows,ColumnsB,Type>>(),Ast::Node::accessAll({a.node, b.node},Ast::AccessPermissions::ReadOnly))};
	// }
}
