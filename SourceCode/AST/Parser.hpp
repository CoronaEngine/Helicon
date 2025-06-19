#pragma once
#include <functional>
#include <memory>
#include <string>
#include <AST/Struct.hpp>
#include <ShaderGenerator/ShaderGenerator.hpp>

namespace EmbeddedShader::Ast
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

		EmbeddedShaderStructure structure;

		size_t currentVariateIndex = 0;
		size_t currentInputVariateIndex = 0;
		size_t currentOutputVariateIndex = 0;
		size_t currentUniformVariateIndex = 0;

		std::shared_ptr<Variate> positionOutput;

		static inline thread_local std::unique_ptr<ShaderGenerator::BaseShaderGenerator> shaderGenerator;
		static inline thread_local std::unique_ptr<Parser> currentParser;
	public:
		static std::string getUniqueVariateName();
		static void setShaderGenerator(std::unique_ptr<ShaderGenerator::BaseShaderGenerator> generator);
		static const std::unique_ptr<ShaderGenerator::BaseShaderGenerator>& getShaderGenerator();
	};
}
