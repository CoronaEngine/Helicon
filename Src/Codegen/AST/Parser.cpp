#include "Parser.hpp"
#include <utility>
#include "../Generator/ShaderGenerator.hpp"

thread_local std::unique_ptr<EmbeddedShader::Ast::Parser> EmbeddedShader::Ast::Parser::currentParser = std::unique_ptr<Parser>(new Parser);

std::string EmbeddedShader::Ast::Parser::parse(const std::function<void()>& shaderCode)
{
	currentParser->statementStack.push(&currentParser->structure.localStatements);
	shaderCode();
	std::string output = shaderGenerator->getShaderOutput(currentParser->structure);
	currentParser->reset();
	return output;
}

void EmbeddedShader::Ast::Parser::reset()
{
	structure.localStatements.clear();
	structure.shaderOnlyStatements.clear();
	currentVariateIndex = 0;
	positionOutput.reset();
}

std::string EmbeddedShader::Ast::Parser::getUniqueVariateName()
{
	return "var_" + std::to_string(currentParser->currentVariateIndex++);
}

std::string EmbeddedShader::Ast::Parser::getUniqueGlobalVariateName()
{
	return "global_var_" + std::to_string(currentParser->currentGlobalVariateIndex++);
}

void EmbeddedShader::Ast::Parser::setShaderGenerator(std::unique_ptr<Generator::BaseShaderGenerator> generator)
{
	shaderGenerator = std::move(generator);
}

const std::unique_ptr<EmbeddedShader::Generator::BaseShaderGenerator>& EmbeddedShader::Ast::Parser::getShaderGenerator()
{
	return shaderGenerator;
}
