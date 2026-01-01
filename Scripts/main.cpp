#include <iostream>
#include <Compiler/ShaderCodeCompiler.h>
#include <Compiler/ShaderLanguageConverter.h>
#include <Scripts/Lexer.hpp>
using namespace EmbeddedShader;

int main()
{
	std::string code = R"(
	int3 merge(int a, int b,int c)
	{
		return int3(a,b,c);
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
	for (auto& irReflection: irReflections)
	{
		if (irReflection.type == IRReflection::Type::FunctionSignature)
		{
			auto& signature = std::get<FunctionSignature>(irReflection.info);
			std::cout << "Function:" << signature.name.substr(0, signature.name.find('(')) << "\n";
			std::cout << "Return Type:" << signature.returnTypeName << "\n";
			std::cout << "Parameter List:\n";
			for (auto& parameter: signature.parameters)
			{
				std::cout << "\t""Name:" << parameter.name << "\n";
				std::cout << "\t""Type:" << parameter.typeName << "\n\n";
			}
		}

		if (irReflection.type == IRReflection::Type::Struct)
		{
			auto& structInfo = std::get<StructInfo>(irReflection.info);
			std::cout << "Struct: " << structInfo.name << "\n";
			std::cout << "Members:\n";
			for (auto& member: structInfo.members)
			{
				std::cout << "\t""Name:" << member.name << "\n";
				std::cout << "\t""Type:" << member.typeName << "\n\n";
			}
		}
	}

	std::cout << "Shader Compile Scripts";
	return 0;
}
