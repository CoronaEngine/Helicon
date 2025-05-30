#pragma once
#include <functional>

namespace EmbeddedShader::AST
{
	class Parser
	{
	public:
		explicit Parser(std::function<void()> shaderCode);
	private:
		std::function<void()> shaderCode;
	};
}
