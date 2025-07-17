#pragma once
#include <memory>
#include <vector>
#include <Codegen/AST/Enum.hpp>

namespace EmbeddedShader::Ast
{
	struct Statement;

	struct EmbeddedShaderStructure
	{
		ShaderStage stage;
		std::vector<std::shared_ptr<Statement>> globalStatements;
		std::vector<std::shared_ptr<Statement>> inputStatements;
		std::vector<std::shared_ptr<Statement>> outputStatements;
		std::vector<std::shared_ptr<Statement>> localStatements;
	};
}
