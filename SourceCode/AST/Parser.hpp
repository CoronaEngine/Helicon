#pragma once
#include <functional>
#include <memory>
#include <string>

namespace EmbeddedShader::AST
{
	struct Statement;
	class Parser
	{
		friend class Node;
	public:
		static std::string parse(const std::function<void()>& shaderCode);
	private:
		Parser() = default;
		[[nodiscard]] std::string getOutput() const;

		std::vector<std::shared_ptr<Statement>> nodes;

		size_t currentVariateIndex = 0;

		static inline thread_local Parser* currentParser = nullptr;
	public:
		static std::string getUniqueVariateName();
	};
}
