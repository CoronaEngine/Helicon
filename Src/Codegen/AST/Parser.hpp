#pragma once
#include <functional>
#include <memory>
#include <stack>
#include <string>
#include "Struct.hpp"
#include "../Generator/ShaderGenerator.hpp"

namespace EmbeddedShader::Ast
{
	struct Variate;
	struct Statement;

	class Parser
	{
		friend class AST;
	public:
		static std::string parse(const std::function<void()>& shaderCode, ShaderStage stage);
	private:
		Parser() = default;

		void reset();

		EmbeddedShaderStructure structure;
		std::stack<std::vector<std::shared_ptr<Statement>>*> localStatementStack;

		size_t currentVariateIndex = 0;
		size_t currentGlobalVariateIndex = 0;

		std::shared_ptr<Variate> positionOutput;

		static inline thread_local std::unique_ptr<Generator::BaseShaderGenerator> shaderGenerator;
		static thread_local std::unique_ptr<Parser> currentParser;
	public:
		static std::string getUniqueVariateName();
		static std::string getUniqueGlobalVariateName();
		static void setShaderGenerator(std::unique_ptr<Generator::BaseShaderGenerator> generator);
		static const std::unique_ptr<Generator::BaseShaderGenerator>& getShaderGenerator();
	};
}
