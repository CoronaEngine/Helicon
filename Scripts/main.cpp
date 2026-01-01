#include <iostream>
#include <Compiler/ShaderCodeCompiler.h>
#include <Compiler/ShaderLanguageConverter.h>
#include <Scripts/Lexer.hpp>
#include <sstream>
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
	if (typeName == "int2") return "ktm::svec2";
	if (typeName == "int3") return "ktm::svec3";
	if (typeName == "int4") return "ktm::svec4";

	if (typeName == "float2") return "ktm::svec2";
	if (typeName == "float3") return "ktm::svec3";
	if (typeName == "float4") return "ktm::svec4";
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
	out << "FunctionProxy<";
	if (signature.returnTypeName == "void")
	{
		out << "void";
		buildFunctionParameter(signature,out);
	}
	else
	{
		out << "VariateProxy<" << typeNameToCpp(signature.returnTypeName);
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

int main()
{
	std::string code = R"(
	int3 merge(int a, int b,int c)
	{
		return int3(a,b,c);
	}

	void func()
	{

	}
	struct B
	{
		float value;
	};
	struct A
	{
		int a;
		B b;
	};
	void func(A a) {}
)";
	// CompilerOption compilerOption;
	// compilerOption.compileSpirV = true;
	// compilerOption.compileHLSL = false;
	// compilerOption.compileDXIL = false;
	// compilerOption.compileDXBC = false;
	// compilerOption.compileGLSL = false;
	// compilerOption.enableBindless = false;
	auto spirv = ShaderLanguageConverter::glslangSpirvCompiler(code,ShaderLanguage::HLSL,ShaderStage::VertexShader,false);

	auto irReflections = ShaderLanguageConverter::spirvCrossGetIRReflection(spirv);
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

	std::cout << "Shader Compile Scripts\n";

	std::stringstream out;
	for (auto& irReflection : irReflections)
	{
		if (irReflection.type == IRReflection::Type::FunctionSignature)
		{
			auto& signature = std::get<FunctionSignature>(irReflection.info);
			if (signature.isEntryPoint) continue;
			buildFunctionSignature(signature,out);
			out << "\n";
		}
	}

	std::cout << out.str();

	return 0;
}
