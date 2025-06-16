#include <ShaderGenerator/OpenGL/ShaderGenerator.hpp>

std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getShaderOutput(
	const Ast::EmbeddedShaderStructure& structure)
{
	std::string output;
	output += "#version 330 core\n";

	//global statements
	for (auto& node: structure.globalStatements)
	{
		output += node->parse() + '\n';
	}

	output += "void main() {\n";
	for (auto& node: structure.statements)
	{
		output += '\t' + node->parse() + '\n';
	}
	output += "}\n";
	return output;
}

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

std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(int32_t value)
{
	return std::to_string(value);
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(uint32_t value)
{
	return std::to_string(value);
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(float value)
{
	return std::to_string(value);
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(double value)
{
	return std::to_string(value);
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(bool value)
{
	return value ? "true" : "false";
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(const ktm::fvec2& value)
{
	return "vec2(" + std::to_string(value.x) + "," + std::to_string(value.y) + ")";
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(const ktm::fvec3& value)
{
	return "vec3(" + std::to_string(value.x) + "," + std::to_string(value.y) + "," + std::to_string(value.z) + ")";
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(const ktm::fvec4& value)
{
	return "vec4(" + std::to_string(value.x) + "," + std::to_string(value.y) + "," + std::to_string(value.z) + "," + std::to_string(value.w) + ")";
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(const ktm::svec2& value)
{
	return "ivec2(" + std::to_string(value.x) + "," + std::to_string(value.y) + ")";
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(const ktm::svec3& value)
{
	return "ivec3(" + std::to_string(value.x) + "," + std::to_string(value.y) + "," + std::to_string(value.z) + ")";
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(const ktm::svec4& value)
{
	return "ivec4(" + std::to_string(value.x) + "," + std::to_string(value.y) + "," + std::to_string(value.z) + "," + std::to_string(value.w) + ")";
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(const ktm::uvec2& value)
{
	return "uvec2(" + std::to_string(value.x) + "," + std::to_string(value.y) + ")";
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(const ktm::uvec3& value)
{
	return "uvec3(" + std::to_string(value.x) + "," + std::to_string(value.y) + "," + std::to_string(value.z) + ")";
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(const ktm::uvec4& value)
{
	return "uvec4(" + std::to_string(value.x) + "," + std::to_string(value.y) + "," + std::to_string(value.z) + "," + std::to_string(value.w) + ")";
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(const ktm::dvec2& value)
{
	return "dvec2(" + std::to_string(value.x) + "," + std::to_string(value.y) + ")";
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(const ktm::dvec3& value)
{
	return "dvec3(" + std::to_string(value.x) + "," + std::to_string(value.y) + "," + std::to_string(value.z) + ")";
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(const ktm::dvec4& value)
{
	return "dvec4(" + std::to_string(value.x) + "," + std::to_string(value.y) + "," + std::to_string(value.z) + "," + std::to_string(value.w) + ")";
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(const ktm::vec<2, bool>& value)
{
	return "bvec2(" + std::to_string(value.x) + "," + std::to_string(value.y) + ")";
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(const ktm::vec<3, bool>& value)
{
	return "bvec3(" + std::to_string(value.x) + "," + std::to_string(value.y) + "," + std::to_string(value.z) + ")";
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(const ktm::vec<4, bool>& value)
{
	return "bvec4(" + std::to_string(value.x) + "," + std::to_string(value.y) + "," + std::to_string(value.z) + "," + std::to_string(value.w) + ")";
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(const ktm::fmat2x2& value)
{
	std::array array = value.to_array();
	return "mat2(" + std::to_string(array[0][0]) + "," + std::to_string(array[0][1]) + "," +
		std::to_string(array[1][0]) + "," + std::to_string(array[1][1]) + ")";
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(const ktm::fmat3x3& value)
{
	std::array array = value.to_array();
	return "mat3(" + std::to_string(array[0][0]) + "," + std::to_string(array[0][1]) + "," + std::to_string(array[0][2]) + "," +
		std::to_string(array[1][0]) + "," + std::to_string(array[1][1]) + "," + std::to_string(array[1][2]) + "," +
		std::to_string(array[2][0]) + "," + std::to_string(array[2][1]) + "," + std::to_string(array[2][2]) + ")";
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(const ktm::fmat4x4& value)
{
	std::array array = value.to_array();
	return "mat4(" + std::to_string(array[0][0]) + "," + std::to_string(array[0][1]) + "," + std::to_string(array[0][2]) + "," + std::to_string(array[0][3]) + "," +
		std::to_string(array[1][0]) + "," + std::to_string(array[1][1]) + "," + std::to_string(array[1][2]) + "," + std::to_string(array[1][3]) + "," +
		std::to_string(array[2][0]) + "," + std::to_string(array[2][1]) + "," + std::to_string(array[2][2]) + "," + std::to_string(array[2][3]) + "," +
		std::to_string(array[3][0]) + "," + std::to_string(array[3][1]) + "," + std::to_string(array[3][2]) + "," + std::to_string(array[3][3]) + ")";
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(const ktm::fmat2x3& value)
{
	std::array array = value.to_array();
	return "mat2x3(" + std::to_string(array[0][0]) + "," + std::to_string(array[0][1]) + "," + std::to_string(array[0][2]) + "," +
		std::to_string(array[1][0]) + "," + std::to_string(array[1][1]) + "," + std::to_string(array[1][2]) + ")";
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(const ktm::fmat2x4& value)
{
	std::array array = value.to_array();
	return "mat2x4(" + std::to_string(array[0][0]) + "," + std::to_string(array[0][1]) + "," + std::to_string(array[0][2]) + "," + std::to_string(array[0][3]) + "," +
		std::to_string(array[1][0]) + "," + std::to_string(array[1][1]) + "," + std::to_string(array[1][2]) + "," + std::to_string(array[1][3]) + ")";
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(const ktm::fmat3x2& value)
{
	std::array array = value.to_array();
	return "mat3x2(" + std::to_string(array[0][0]) + "," + std::to_string(array[0][1]) + "," +
		std::to_string(array[1][0]) + "," + std::to_string(array[1][1]) + "," +
		std::to_string(array[2][0]) + "," + std::to_string(array[2][1]) + ")";
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(const ktm::fmat3x4& value)
{
	std::array array = value.to_array();
	return "mat3x4(" + std::to_string(array[0][0]) + "," + std::to_string(array[0][1]) + "," + std::to_string(array[0][2]) + "," + std::to_string(array[0][3]) + "," +
		std::to_string(array[1][0]) + "," + std::to_string(array[1][1]) + "," + std::to_string(array[1][2]) + "," + std::to_string(array[1][3]) + "," +
		std::to_string(array[2][0]) + "," + std::to_string(array[2][1]) + "," + std::to_string(array[2][2]) + "," + std::to_string(array[2][3]) + ")";
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(const ktm::fmat4x2& value)
{
	std::array array = value.to_array();
	return "mat4x2(" + std::to_string(array[0][0]) + "," + std::to_string(array[0][1]) + "," +
		std::to_string(array[1][0]) + "," + std::to_string(array[1][1]) + "," +
		std::to_string(array[2][0]) + "," + std::to_string(array[2][1]) + "," +
		std::to_string(array[3][0]) + "," + std::to_string(array[3][1]) + ")";
}
std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getValueOutput(const ktm::fmat4x3& value)
{
	std::array array = value.to_array();
	return "mat4x3(" + std::to_string(array[0][0]) + "," + std::to_string(array[0][1]) + "," + std::to_string(array[0][2]) + "," +
		std::to_string(array[1][0]) + "," + std::to_string(array[1][1]) + "," + std::to_string(array[1][2]) + "," +
		std::to_string(array[2][0]) + "," + std::to_string(array[2][1]) + "," + std::to_string(array[2][2]) + "," +
		std::to_string(array[3][0]) + "," + std::to_string(array[3][1]) + "," + std::to_string(array[3][2]) + ")";
}

std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getParseOutput(
	const Ast::DefineLocalVariate* node)
{
	auto result = node->localVariate->type->parse() + " " + node->localVariate->name;
	if (node->value)
		result += " = " + node->value->parse();
	result += ";";
	return result;
}

std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getParseOutput(
	const Ast::DefineInputVariate* node)
{
	return "layout(location = " + std::to_string(node->variate->index) + ") in " + node->variate->type->parse() + " " + node->variate->name + ";";
}

std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getParseOutput(
	const Ast::Assign* node)
{
	return node->leftValue->parse() + " = " + node->rightValue->parse() + ";";
}

std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getParseOutput(const Ast::BinaryOperator* node)
{
	return "(" + node->value1->parse() + " " + std::string(node->type) + " " + node->value2->parse() + ")";
}

std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getParseOutput(const Ast::MemberAccess* node)
{
	return node->value->parse() + "." + node->memberName;
}

std::string EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getParseOutput(
	const Ast::DefineOutputVariate* node)
{
	return "out " + node->variate->type->parse() + " " + node->variate->name + ";";
}

std::shared_ptr<EmbeddedShader::Ast::Variate> EmbeddedShader::ShaderGenerator::OpenGL::ShaderGenerator::getPositionOutput()
{
	auto posOutput = std::make_shared<Ast::Variate>();
	posOutput->name = "gl_Position";
	posOutput->type = Ast::VecType::createVecType(Ast::VariateType::Vec4);
	return posOutput;
}
