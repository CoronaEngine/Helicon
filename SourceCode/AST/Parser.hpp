#pragma once
#include <functional>
#include <memory>
#include <string>

namespace EmbeddedShader::AST
{
	class Parser
	{
		friend class Node;
	public:
		static std::string parse(const std::function<void()>& shaderCode);
	private:
		Parser() = default;
		std::string getOutput();

		std::vector<std::shared_ptr<Node>> nodes;

		static inline thread_local Parser* currentParser = nullptr;
	};
}
