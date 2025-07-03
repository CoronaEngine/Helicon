#include "Parser.hpp"
#include <utility>
#include "../Generator/ShaderGenerator.hpp"

std::string EmbeddedShader::Ast::Parser::parse(const std::function<void()>& shaderCode)
{
	currentParser = std::unique_ptr<Parser>(new Parser);
	currentParser->statementStack.push(&currentParser->structure.statements);
	shaderCode();
	std::string output = shaderGenerator->getShaderOutput(currentParser->structure);
	currentParser.reset();
	return output;
}

std::string EmbeddedShader::Ast::Parser::getUniqueVariateName()
{
	return "var_" + std::to_string(currentParser->currentVariateIndex++);
}

void EmbeddedShader::Ast::Parser::setShaderGenerator(std::unique_ptr<ShaderGenerator::BaseShaderGenerator> generator)
{
	shaderGenerator = std::move(generator);
}

const std::unique_ptr<EmbeddedShader::ShaderGenerator::BaseShaderGenerator>& EmbeddedShader::Ast::Parser::getShaderGenerator()
{
	return shaderGenerator;
}
