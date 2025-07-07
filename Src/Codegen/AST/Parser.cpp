#include "Parser.hpp"
#include <utility>
#include "../Generator/ShaderGenerator.hpp"

thread_local std::unique_ptr<EmbeddedShader::Ast::Parser> EmbeddedShader::Ast::Parser::currentParser = std::unique_ptr<Parser>(new Parser);

std::string EmbeddedShader::Ast::Parser::parse(const std::function<void()>& shaderCode)
{
	currentParser->statementStack.push(&currentParser->structure.statements);
	shaderCode();
	std::string output = shaderGenerator->getShaderOutput(currentParser->structure);
	currentParser.reset(new Parser);
	return output;
}

std::string EmbeddedShader::Ast::Parser::getUniqueVariateName()
{
	return "var_" + std::to_string(currentParser->currentVariateIndex++);
}

void EmbeddedShader::Ast::Parser::setShaderGenerator(std::unique_ptr<Generator::BaseShaderGenerator> generator)
{
	shaderGenerator = std::move(generator);
}

const std::unique_ptr<EmbeddedShader::Generator::BaseShaderGenerator>& EmbeddedShader::Ast::Parser::getShaderGenerator()
{
	return shaderGenerator;
}
