#include "Parser.hpp"
#include <utility>
#include <Codegen/Generator/SlangGenerator.hpp>

thread_local std::unique_ptr<EmbeddedShader::Ast::Parser> EmbeddedShader::Ast::Parser::currentParser = std::unique_ptr<Parser>(new Parser);

std::vector<EmbeddedShader::Ast::ParseOutput> EmbeddedShader::Ast::Parser::parse(const std::vector<ParseParameter>& parameters)
{
	std::vector<ParseOutput> outputs;
	for (const auto& parameter: parameters)
	{
		outputs.emplace_back(parse(parameter.shaderCode,parameter.stage),parameter.stage);
	}

	auto globalOutput = Generator::SlangGenerator::getGlobalOutput(currentParser->structure);
	for (auto& output: outputs)
		output.output = globalOutput + output.output;

	for (const auto& global: currentParser->structure.globalStatements)
		global->resetAccessPermissions();

	return outputs;
}

void EmbeddedShader::Ast::Parser::beginShaderParse(ShaderStage stage)
{
	if (currentParser->isInShaderParse)
	{
		currentParser->parseOutputs.emplace_back(Generator::SlangGenerator::getShaderOutput(currentParser->structure), currentParser->structure.stage);
		currentParser->reset();
		currentParser->isInShaderParse = false;
	}
	currentParser->structure.stage = stage;
	currentParser->localStatementStack.push(&currentParser->structure.localStatements);
	currentParser->isInShaderParse = true;
}

std::vector<EmbeddedShader::Ast::ParseOutput> EmbeddedShader::Ast::Parser::endPipelineParse()
{
	if (currentParser->isInShaderParse)
	{
		currentParser->parseOutputs.emplace_back(Generator::SlangGenerator::getShaderOutput(currentParser->structure), currentParser->structure.stage);
		currentParser->reset();
		currentParser->isInShaderParse = false;
	}

	auto globalOutput = Generator::SlangGenerator::getGlobalOutput(currentParser->structure);
	for (auto& output: currentParser->parseOutputs)
		output.output = globalOutput + output.output;

	for (const auto& global: currentParser->structure.globalStatements)
	{
        global->resetAccessPermissions();
	    global->resetUsedFlag();
	}

    std::vector<ParseOutput> result;
	currentParser->parseOutputs.swap(result);
	return result;
}

void EmbeddedShader::Ast::Parser::setBindless(bool bindless)
{
	currentParser->bindless = bindless;
}

bool EmbeddedShader::Ast::Parser::getBindless()
{
	return currentParser->bindless;
}

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
	structure.localStatements.clear();
	structure.inputStatements.clear();
	structure.outputStatements.clear();
	currentVariateIndex = 0;
	positionOutput.reset();
	dispatchThreadIDInput.reset();
}

std::string EmbeddedShader::Ast::Parser::getUniqueVariateName()
{
	return "var_" + std::to_string(currentParser->currentVariateIndex++);
}

std::string EmbeddedShader::Ast::Parser::getUniqueAggregateTypeName()
{
	return "aggregate_type_" + std::to_string(currentParser->currentAggregateTypeIndex++);
}

std::string EmbeddedShader::Ast::Parser::getUniqueGlobalVariateName()
{
	return "global_var_" + std::to_string(currentParser->currentGlobalVariateIndex++);
}
