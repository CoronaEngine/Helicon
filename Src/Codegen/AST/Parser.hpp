#pragma once
#include <functional>
#include <memory>
#include <stack>
#include <string>
#include "Struct.hpp"

namespace EmbeddedShader::Ast
{
	struct Variate;
	struct Statement;

	struct ParseParameter
	{
		const std::function<void()>& shaderCode;
		ShaderStage stage;
	};

	struct ParseOutput
	{
		std::string output;
		ShaderStage stage;
	};

	class Parser
	{
		friend class AST;
	public:
		static std::vector<ParseOutput> parse(const std::vector<ParseParameter>& parameters);
		static void beginShaderParse(ShaderStage stage);
		static std::vector<ParseOutput> endPipelineParse();
	private:
		static std::string parse(const std::function<void()>& shaderCode, ShaderStage stage);
		Parser() = default;

		void reset();

		EmbeddedShaderStructure structure;
		std::stack<std::vector<std::shared_ptr<Statement>>*> localStatementStack;

		size_t currentVariateIndex = 0;
		size_t currentGlobalVariateIndex = 0;
		size_t currentAggregateTypeIndex = 0;

		std::shared_ptr<Variate> positionOutput;

		std::vector<ParseOutput> parseOutputs;

		bool isInShaderParse = false;

		static thread_local std::unique_ptr<Parser> currentParser;
	public:
		static std::string getUniqueVariateName();
		static std::string getUniqueAggregateTypeName();
		static std::string getUniqueGlobalVariateName();
	};
}
