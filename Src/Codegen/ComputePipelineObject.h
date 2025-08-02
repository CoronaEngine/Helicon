#pragma once
#include <functional>
#include <string>
#include <Codegen/ParseHelper.h>
#include <Codegen/AST/AST.hpp>
#include <Codegen/AST/Parser.hpp>

namespace EmbeddedShader
{
	class ComputePipelineObject
	{
	public:
		static ComputePipelineObject compile(auto computeShaderCode, ktm::uvec3 numthreads = ktm::uvec3(1),std::source_location sourceLocation = std::source_location::current());
		[[nodiscard]] ShaderCodeModule getComputeShaderCode(ShaderLanguage language) const;
	private:
		std::unique_ptr<ShaderCodeCompiler> computeCompiler;
	};

	inline ShaderCodeModule ComputePipelineObject::getComputeShaderCode(ShaderLanguage language) const {
		return computeCompiler->getShaderCode(language);
	}

	ComputePipelineObject ComputePipelineObject::compile(auto computeShaderCode, ktm::uvec3 numthreads,std::source_location sourceLocation)
	{
		Generator::SlangGenerator::numthreads = numthreads;
		auto csFunc = std::function(computeShaderCode);

		Ast::Parser::beginShaderParse(Ast::ShaderStage::Compute);
		auto csParams = ParseHelper::createParamTuple(csFunc);
		ParseHelper::callLambda(csFunc,std::move(csParams));
		if constexpr (!ParseHelper::hasReturnValue(csFunc))
			ParseHelper::callLambda(csFunc,std::move(csParams));
		else
		{
			auto csOutput = ParseHelper::callLambda(csFunc,std::move(csParams));
			static_assert(ParseHelper::isReturnVariateProxy(csFunc), "The output of the shader must be a proxy!");
			auto outputVar = Ast::AST::defineOutputVariate(reinterpret_cast<Ast::Variate*>(csOutput.node.get())->type,0);
			Ast::AST::assign(outputVar,csOutput.node);
		}

		ComputePipelineObject result;
		auto outputs = Ast::Parser::endPipelineParse();
		result.computeCompiler = std::make_unique<ShaderCodeCompiler>(outputs[0].output, ShaderStage::ComputeShader, ShaderLanguage::Slang,sourceLocation);
		return result;
	}
}
