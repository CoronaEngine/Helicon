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
		std::string computeGeneration;
		static ComputePipelineObject parse(auto computeShaderCode);
	};

	ComputePipelineObject ComputePipelineObject::parse(auto computeShaderCode)
	{
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
		result.computeGeneration = outputs[0].output;
		return result;
	}
}
