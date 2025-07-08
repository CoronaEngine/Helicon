#pragma once
#include <cstdint>
#include <iostream>
#include <ktm/type_mat.h>
#include <ktm/type_vec.h>

namespace EmbeddedShader::Ast
{
	enum class ShaderStage
	{
		Vertex,
		Fragment,
		//Compute,
	};

	enum class VariateType
	{
		Undefined = -1,
		Int8,
		Int16,
		Int,
		Int64,
		Uint8,
		Uint16,
		Uint,
		Uint64,
		Float,
		Double,
		Bool,
		Half,

		Vec2,
		Vec3,
		Vec4,
		IVec2,
		IVec3,
		IVec4,
		UVec2,
		UVec3,
		UVec4,
		DVec2,
		DVec3,
		DVec4,
		BVec2,
		BVec3,
		BVec4,

		Mat2,
		Mat3,
		Mat4,
		Mat2x3,
		Mat2x4,
		Mat3x2,
		Mat3x4,
		Mat4x2,
		Mat4x3,
	};

	template<typename T> auto variateTypeToEnum = VariateType::Undefined;
	template<> inline auto variateTypeToEnum<int32_t> = VariateType::Int;
	template<> inline auto variateTypeToEnum<uint32_t> = VariateType::Uint;
	template<> inline auto variateTypeToEnum<float> = VariateType::Float;
	template<> inline auto variateTypeToEnum<double> = VariateType::Double;
	template<> inline auto variateTypeToEnum<bool> = VariateType::Bool;
	template<> inline auto variateTypeToEnum<ktm::fvec2> = VariateType::Vec2;
	template<> inline auto variateTypeToEnum<ktm::fvec3> = VariateType::Vec3;
	template<> inline auto variateTypeToEnum<ktm::fvec4> = VariateType::Vec4;
	template<> inline auto variateTypeToEnum<ktm::svec2> = VariateType::IVec2;
	template<> inline auto variateTypeToEnum<ktm::svec3> = VariateType::IVec3;
	template<> inline auto variateTypeToEnum<ktm::svec4> = VariateType::IVec4;
	template<> inline auto variateTypeToEnum<ktm::uvec2> = VariateType::UVec2;
	template<> inline auto variateTypeToEnum<ktm::uvec3> = VariateType::UVec3;
	template<> inline auto variateTypeToEnum<ktm::uvec4> = VariateType::UVec4;
	template<> inline auto variateTypeToEnum<ktm::dvec2> = VariateType::DVec2;
	template<> inline auto variateTypeToEnum<ktm::dvec3> = VariateType::DVec3;
	template<> inline auto variateTypeToEnum<ktm::dvec4> = VariateType::DVec4;
	template<> inline auto variateTypeToEnum<ktm::vec<2,bool>> = VariateType::BVec2;
	template<> inline auto variateTypeToEnum<ktm::vec<3,bool>> = VariateType::BVec3;
	template<> inline auto variateTypeToEnum<ktm::vec<4,bool>> = VariateType::BVec4;
	template<> inline auto variateTypeToEnum<ktm::fmat2x2> = VariateType::Mat2;
	template<> inline auto variateTypeToEnum<ktm::fmat3x3> = VariateType::Mat3;
	template<> inline auto variateTypeToEnum<ktm::fmat4x4> = VariateType::Mat4;
	template<> inline auto variateTypeToEnum<ktm::fmat2x3> = VariateType::Mat2x3;
	template<> inline auto variateTypeToEnum<ktm::fmat2x4> = VariateType::Mat2x4;
	template<> inline auto variateTypeToEnum<ktm::fmat3x2> = VariateType::Mat3x2;
	template<> inline auto variateTypeToEnum<ktm::fmat3x4> = VariateType::Mat3x4;
	template<> inline auto variateTypeToEnum<ktm::fmat4x2> = VariateType::Mat4x2;
	template<> inline auto variateTypeToEnum<ktm::fmat4x3> = VariateType::Mat4x3;

	enum class AccessPermissions : uint8_t
	{
		None = 0,
		ReadOnly = 0b1,
		WriteOnly = 0b10,
		ReadAndWrite = ReadOnly | WriteOnly,
	};

	inline AccessPermissions operator|(AccessPermissions a, AccessPermissions b)
	{
		using UnderlyingType = std::underlying_type_t<AccessPermissions>;
		return static_cast<AccessPermissions>(static_cast<UnderlyingType>(a) |static_cast<UnderlyingType>(b));
	}

	inline std::ostream& operator<<(std::ostream& os, AccessPermissions a)
	{
		switch (a)
		{
			case AccessPermissions::None:
				return os << "None (Not used)";
			case AccessPermissions::ReadOnly:
				return os << "ReadOnly";
				case AccessPermissions::WriteOnly:
				return os << "WriteOnly";
			case AccessPermissions::ReadAndWrite:
				return os << "ReadAndWrite";
				default:break;
		}

		return os << "Unknown AccessPermissions";
	}
}
