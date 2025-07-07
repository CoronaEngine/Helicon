#include <Codegen/AST/AST.hpp>
#include <Codegen/Generator/ShaderGenerator.hpp>

std::string EmbeddedShader::Generator::BaseShaderGenerator::getCodeIndentation()
{
	//ide可能会误报warning
	return std::string(nestHierarchy, '\t');
}