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
		std::vector<std::shared_ptr<Statement>> shaderOnlyStatements;
		std::vector<std::shared_ptr<Statement>> localStatements;
	};
}
