#include "Parser.hpp"
#include <utility>
#include <Codegen/Generator/SlangGenerator.hpp>

thread_local std::unique_ptr<EmbeddedShader::Ast::Parser> EmbeddedShader::Ast::Parser::currentParser = std::unique_ptr<Parser>(new Parser);

std::string EmbeddedShader::Ast::Parser::parse(const std::function<void()>& shaderCode, ShaderStage stage)
{
	currentParser->structure.stage = stage;
	currentParser->localStatementStack.push(&currentParser->structure.localStatements);
	shaderCode();
	std::string output = Generator::SlangGenerator::getShaderOutput(currentParser->structure);
	currentParser->reset();
	return output;
}

void EmbeddedShader::Ast::Parser::reset()
{
	for (const auto& global: structure.globalStatements)
		global->resetAccessPermissions();
	structure.localStatements.clear();
	structure.inputStatements.clear();
	structure.outputStatements.clear();
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
