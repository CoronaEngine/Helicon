#include <ShaderGenerator/OpenGL/ShaderGenerator.hpp>

std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getVariateTypeName(Ast::VariateType variateType)
{
	switch (variateType)
	{
		case Ast::VariateType::Undefined:
			break;
		case Ast::VariateType::Int:
			return "int";
		case Ast::VariateType::Uint:
			return "uint";
		case Ast::VariateType::Float:
			return "float";
		case Ast::VariateType::Double:
			return "double";
		case Ast::VariateType::Bool:
			return "bool";
		case Ast::VariateType::Vec2:
			return "vec2";
		case Ast::VariateType::Vec3:
			return "vec3";
		case Ast::VariateType::Vec4:
			return "vec4";
		case Ast::VariateType::IVec2:
			return "ivec2";
		case Ast::VariateType::IVec3:
			return "ivec3";
		case Ast::VariateType::IVec4:
			return "ivec4";
		case Ast::VariateType::UVec2:
			return "uvec2";
		case Ast::VariateType::UVec3:
			return "uvec3";
		case Ast::VariateType::UVec4:
			return "uvec4";
		case Ast::VariateType::DVec2:
			return "dvec2";
		case Ast::VariateType::DVec3:
			return "dvec3";
		case Ast::VariateType::DVec4:
			return "dvec4";
		case Ast::VariateType::BVec2:
			return "bvec2";
		case Ast::VariateType::BVec3:
			return "bvec3";
		case Ast::VariateType::BVec4:
			return "bvec4";
		case Ast::VariateType::Mat2:
			return "mat2";
		case Ast::VariateType::Mat3:
			return "mat3";
		case Ast::VariateType::Mat4:
			return "mat4";
		case Ast::VariateType::Mat2x3:
			return "mat2x3";
		case Ast::VariateType::Mat2x4:
			return "mat2x4";
		case Ast::VariateType::Mat3x2:
			return "mat3x2";
		case Ast::VariateType::Mat3x4:
			return "mat3x4";
		case Ast::VariateType::Mat4x2:
			return "mat4x2";
		case Ast::VariateType::Mat4x3:
			return "mat4x3";
		default:break;
	}
	return "Undefined";
}
