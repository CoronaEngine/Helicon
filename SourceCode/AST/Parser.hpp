#pragma once
#include <functional>
#include <memory>
#include <string>

namespace EmbeddedShader::AST
{
	struct Variate;
	struct Statement;
	class Parser
	{
		friend class AST;
	public:
		static std::string parse(const std::function<void()>& shaderCode);
	private:
		Parser() = default;
		[[nodiscard]] std::string getOutput() const;

		std::vector<std::shared_ptr<Statement>> statements;
		std::vector<std::shared_ptr<Statement>> globalStatements;

		size_t currentVariateIndex = 0;
		size_t currentInputVariateIndex = 0;

		std::shared_ptr<Variate> positionOutput;

		static inline thread_local Parser* currentParser = nullptr;
	public:
		static std::string getUniqueVariateName();
	};
}
