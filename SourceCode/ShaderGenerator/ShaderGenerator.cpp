#include <AST/AST.hpp>
#include <ShaderGenerator/ShaderGenerator.hpp>

std::string EmbeddedShader::ShaderGenerator::BaseShaderGenerator::getCodeIndentation()
{
	//ide可能会误报warning
	return std::string(nestHierarchy, '\t');
}