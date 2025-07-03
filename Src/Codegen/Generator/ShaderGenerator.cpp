#include <Codegen/AST/AST.hpp>
#include <Codegen/Generator/ShaderGenerator.hpp>

std::string EmbeddedShader::ShaderGenerator::BaseShaderGenerator::getCodeIndentation()
{
	//ide可能会误报warning
	return std::string(nestHierarchy, '\t');
}