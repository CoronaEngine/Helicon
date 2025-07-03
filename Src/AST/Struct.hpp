#pragma once
#include <memory>
#include <vector>

namespace EmbeddedShader::Ast
{
	struct Statement;

	struct EmbeddedShaderStructure
	{
		std::vector<std::shared_ptr<Statement>> globalStatements;
		std::vector<std::shared_ptr<Statement>> statements;
	};
}
