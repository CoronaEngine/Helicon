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
)";
	// CompilerOption compilerOption;
	// compilerOption.compileSpirV = true;
	// compilerOption.compileHLSL = false;
	// compilerOption.compileDXIL = false;
	// compilerOption.compileDXBC = false;
	// compilerOption.compileGLSL = false;
	// compilerOption.enableBindless = false;
	auto spirv = ShaderLanguageConverter::glslangSpirvCompiler(code,ShaderLanguage::HLSL,ShaderStage::VertexShader,false);

	auto signatures = ShaderLanguageConverter::spirvCrossGetFunctionSignatures(spirv);
	for (auto& signature: signatures)
	{

		std::cout << "Function:" << signature.name.substr(0,signature.name.find('(')) << "\n";
		std::cout << "Return Type:" << signature.returnTypeName << "\n";
		std::cout << "Parameter List:\n";
		for (auto& parameter: signature.parameters)
		{
			std::cout << "\t""Name:" << parameter.name << "\n";
			std::cout << "\t""Type:" << parameter.typeName << "\n\n";
		}
	}

	std::cout << "Shader Compile Scripts";
	return 0;
}
