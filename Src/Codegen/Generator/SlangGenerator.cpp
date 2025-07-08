#include <Codegen/Generator/SlangGenerator.hpp>
std::string EmbeddedShader::Generator::SlangGenerator::getShaderOutput(const Ast::EmbeddedShaderStructure& structure)
{
	std::string output;

	for (auto& statement: structure.globalStatements)
	{
		output += statement->parse() + '\n';
	}

	for (auto& statement: structure.shaderOnlyStatements)
	{
		output += statement->parse() + '\n';
	}

	std::string mainContent;
	for (auto& statement: structure.localStatements)
	{
		mainContent += statement->parse() + '\n';
	}

	// std::string entrypoint;
	// std::string outputStruct;
	// std::string outputStructName;
	// {
	// 	std::string stageType = "unknown";
	// 	switch (structure.stage)
	// 	{
	// 		case Ast::ShaderStage::Vertex:
	// 			stageType = "vertex";
	// 			break;
	// 		case Ast::ShaderStage::Fragment:
	// 			stageType = "fragment";
	// 			break;
	// 	}
	//
	// 	outputStructName = stageType + "_output";
	//
	// 	entrypoint = "[shader(\"" + stageType + "\")]\n";
	// 	entrypoint += outputStructName + " main(";
	// }

	return output;
}

std::string EmbeddedShader::Generator::SlangGenerator::getVariateTypeName(Ast::VariateType variateType)
{
	switch (variateType)
	{
		case Ast::VariateType::Undefined:
			break;
		case Ast::VariateType::Int8:
			return "int8_t";
		case Ast::VariateType::Int16:
			return "int16_t";
		case Ast::VariateType::Int:
			return "int";
		case Ast::VariateType::Int64:
			return "int64_t";
		case Ast::VariateType::Uint8:
			return "uint8_t";
		case Ast::VariateType::Uint16:
			return "uint16_t";
		case Ast::VariateType::Uint:
			return "uint";
		case Ast::VariateType::Uint64:
			return "uint64_t";
		case Ast::VariateType::Float:
			return "float";
		case Ast::VariateType::Double:
			return "double";
		case Ast::VariateType::Half:
			return "half";
		case Ast::VariateType::Bool:
			return "bool";
		case Ast::VariateType::Vec2:
			return "float2";
		case Ast::VariateType::Vec3:
			return "float3";
		case Ast::VariateType::Vec4:
			return "float4";
		case Ast::VariateType::IVec2:
			return "int2";
		case Ast::VariateType::IVec3:
			return "int3";
		case Ast::VariateType::IVec4:
			return "int4";
		case Ast::VariateType::UVec2:
			return "uint2";
		case Ast::VariateType::UVec3:
			return "uint3";
		case Ast::VariateType::UVec4:
			return "uint4";
		case Ast::VariateType::DVec2:
			return "double2";
		case Ast::VariateType::DVec3:
			return "double3";
		case Ast::VariateType::DVec4:
			return "double4";
		case Ast::VariateType::BVec2:
			return "bool2";
		case Ast::VariateType::BVec3:
			return "bool3";
		case Ast::VariateType::BVec4:
			return "bool4";
		case Ast::VariateType::Mat2:
			return "float2x2";
		case Ast::VariateType::Mat3:
			return "float3x3";
		case Ast::VariateType::Mat4:
			return "float4x4";
		case Ast::VariateType::Mat2x3:
			return "float2x3";
		case Ast::VariateType::Mat2x4:
			return "float2x4";
		case Ast::VariateType::Mat3x2:
			return "float3x2";
		case Ast::VariateType::Mat3x4:
			return "float3x4";
		case Ast::VariateType::Mat4x2:
			return "float4x2";
		case Ast::VariateType::Mat4x3:
			return "float4x3";
		default:break;
	}
	return "Undefined";
}
