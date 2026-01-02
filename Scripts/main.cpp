#include <filesystem>
#include <iostream>
#include <Compiler/ShaderCodeCompiler.h>
#include <Compiler/ShaderLanguageConverter.h>
#include <Scripts/Lexer.hpp>
#include <sstream>
#include <fstream>
using namespace EmbeddedShader;

std::string typeNameToSlang(std::string_view typeName)
{
	if (typeName == "ivec2") return "int2";
	if (typeName == "ivec3") return "int3";
	if (typeName == "ivec4") return "int4";

	if (typeName == "vec2") return "float2";
	if (typeName == "vec3") return "float3";
	if (typeName == "vec4") return "float4";
	return std::string(typeName);
}

std::string typeNameToCpp(std::string_view typeName)
{
	if (typeName == "int2") return "::ktm::svec2";
	if (typeName == "int3") return "::ktm::svec3";
	if (typeName == "int4") return "::ktm::svec4";

	if (typeName == "float2") return "::ktm::svec2";
	if (typeName == "float3") return "::ktm::svec3";
	if (typeName == "float4") return "::ktm::svec4";
	return std::string(typeName);
}

void buildFunctionParameter(FunctionSignature& signature, std::stringstream& out)
{
	out << "(";
	if (!signature.parameters.empty())
	{
		auto& param0 = signature.parameters[0];
		out << typeNameToCpp(param0.typeName) << " " << param0.name;
		for (size_t i = 1; i < signature.parameters.size(); ++i)
		{
			auto& param = signature.parameters[i];
			out << ", " << typeNameToCpp(param.typeName) << " " << param.name;
		}
	}
	out << ")";
}

void buildFunctionSignature(FunctionSignature& signature, std::stringstream& out)
{
	// out << signature.returnTypeName << " " << signature.name << "(";
	// if (signature.parameters.empty())
	// {
	// 	out << ");";
	// }
	out << "::EmbeddedShader::FunctionProxy<";
	if (signature.returnTypeName == "void")
	{
		out << "void";
		buildFunctionParameter(signature,out);
	}
	else
	{
		out << "::EmbeddedShader::VariateProxy<" << typeNameToCpp(signature.returnTypeName);
		buildFunctionParameter(signature,out);
		out << ">";
	}
	out << "> " << signature.name << "{";
	out << "\""<< signature.name << "\",\""<< typeNameToSlang(signature.returnTypeName) << "\",{";
	for (auto element: signature.parameters)
	{
		out << "\"" << typeNameToSlang(element.typeName) << "\",";
	}
	out<< "}};";
}

void buildStruct(const StructInfo& structInfo, std::stringstream& out)
{
	out << "struct " << structInfo.name << "\n{\n";
	for (auto& member : structInfo.members)
	{
		out << "\t""::EmbeddedShader::VariateProxy<" << typeNameToCpp(member.typeName) << "> " << member.name << ";\n";
	}
	out << "};";
}

int main(int argc, char** argv)
{
	std::cout << "Helicon Shader Compile Scripts\n";
	if (argc < 2)
	{
		std::cout << "NOTE:No input\n";
		return 1;
	}
	std::filesystem::path path = "";
	std::filesystem::path outPath = "";
	std::string ext  = ".h";
	ShaderLanguage inputLanguage = ShaderLanguage::GLSL;

	//main 参数解析
	for (int i = 1; i < argc;)
	{
		if (std::string arg = argv[i]; arg == "-s")
		{
			++i;
			path = argv[i];
		}
		else if (arg == "-o")
		{
			++i;
			outPath = argv[i];
		}
		else if (arg == "-l")
		{
			++i;
			arg = argv[i];
			if (arg == "glsl")
				inputLanguage = ShaderLanguage::GLSL;
			else if (arg == "hlsl")
				inputLanguage = ShaderLanguage::HLSL;
			else
			{
				std::cout << "ERROR:Unrecognized Shader Language.\n";
				return 1;
			}
		}
		else if (arg == "-output-file-extension")
		{
			++i;
			ext = argv[i];
		}
		else
		{
			std::cout << "ERROR:Unrecognized Parameter.\n";
			return 1;
		}
		++i;
	}

	if (path.empty())
	{
		std::cout << "ERROR:Cannot enter an empty source file path.\n";
		return 1;
	}

	std::fstream file(path,std::ios::in);
	if (!file.is_open())
	{
		std::cout << "ERROR:Cannot open the source file.\n";
		return 1;
	}

	if (outPath.empty())
	{
		std::cout << "NOTE:No output. Use the source file directory as the default output directory.\n";
		outPath = path.parent_path();
	}

	if (ext.empty())
	{
		std::cout << "NOTE:Invalid file extension. Use the default file extension (.h).\n";
		ext = ".h";
	}
	ext = ext[0] == '.' ? ext : "." + ext;

	std::string code = (std::stringstream{} << file.rdbuf()).str();
	file.close();
	auto spirv = ShaderLanguageConverter::glslangSpirvCompiler(code,inputLanguage,ShaderStage::VertexShader,{ path.parent_path() }, false);
	if (spirv.empty())
	{
		std::cout << "ERROR:Cannot compile SPIR-V.\n";
		return 1;
	}
	std::cout << "SUCCESS:SPIR-V compiled.\n";

	auto irReflections = ShaderLanguageConverter::spirvCrossGetIRReflection(spirv);
	std::cout << "SUCCESS:Obtain reflection information from SPIR-V IR through SPIRV-CROSS.\n";

	// for (auto& irReflection: irReflections)
	// {
	// 	if (irReflection.type == IRReflection::Type::FunctionSignature)
	// 	{
	// 		auto& signature = std::get<FunctionSignature>(irReflection.info);
	// 		std::cout << "Function:" << signature.name.substr(0, signature.name.find('(')) << "\n";
	// 		std::cout << "Return Type:" << signature.returnTypeName << "\n";
	// 		std::cout << "Parameter List:\n";
	// 		for (auto& parameter: signature.parameters)
	// 		{
	// 			std::cout << "\t""Name:" << parameter.name << "\n";
	// 			std::cout << "\t""Type:" << parameter.typeName << "\n\n";
	// 		}
	// 	}
	//
	// 	if (irReflection.type == IRReflection::Type::Struct)
	// 	{
	// 		auto& structInfo = std::get<StructInfo>(irReflection.info);
	// 		std::cout << "Struct: " << structInfo.name << "\n";
	// 		std::cout << "Members:\n";
	// 		for (auto& member: structInfo.members)
	// 		{
	// 			std::cout << "\t""Name:" << member.name << "\n";
	// 			std::cout << "\t""Type:" << member.typeName << "\n\n";
	// 		}
	// 	}
	// }

	std::cout << "INFO:Generate the final C++ shader...\n";
	std::stringstream out;
	out << "#pragma once\n#include <Codegen/VariateProxy.h>\n";
	for (auto& irReflection : irReflections)
	{
		if (irReflection.type == IRReflection::Type::FunctionSignature)
		{
			auto& signature = std::get<FunctionSignature>(irReflection.info);
			if (signature.isEntryPoint) continue;
			buildFunctionSignature(signature,out);
			out << "\n";
		}

		if (irReflection.type == IRReflection::Type::Struct)
		{
			auto& structInfo = std::get<StructInfo>(irReflection.info);
			buildStruct(structInfo,out);
			out << "\n";
		}
	}

	//std::cout << out.str();

	auto stem = path.stem();
	auto outFilePath = outPath / (stem.string() + ext);
	file.open(outFilePath,std::ios::out);
	file << out.str();
	file.close();

	std::cout << "SUCCESS:The C++ shader has been output to the following directory:\n\t" << outFilePath.string();

	return 0;
}
