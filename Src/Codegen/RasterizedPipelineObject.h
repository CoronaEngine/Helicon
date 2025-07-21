#pragma once
#include <string>
#include <Codegen/ParseHelper.h>
#include <Codegen/ParseHelperImpl.h>
#include <Codegen/AST/AST.hpp>
#include <Codegen/AST/Parser.hpp>

namespace EmbeddedShader
{
	struct RasterizedPipelineObject final
	{
		std::string vertexGeneration;
		std::string fragmentGeneration;
		static RasterizedPipelineObject parse(auto vertexShaderCode, auto fragmentShaderCode);
	};

	RasterizedPipelineObject RasterizedPipelineObject::parse(auto vertexShaderCode, auto fragmentShaderCode)
	{
		auto vsFunc = std::function(vertexShaderCode);
		auto fsFunc = std::function(fragmentShaderCode);

		static_assert(ParseHelper::isMatchInputAndOutput(vsFunc,fsFunc), "The output of the vertex shader and the input of the fragment shader must match!");

		Ast::Parser::beginShaderParse(Ast::ShaderStage::Vertex);
		auto vsParams = ParseHelper::createParamTuple(vsFunc);
		if constexpr (ParseHelper::hasReturnValue(vsFunc))
		{
			auto vsOutput = ParseHelper::callLambda(vsFunc,std::move(vsParams));

			static_assert(ParseHelper::isReturnProxy(vsFunc), "The output of the shader must be a proxy!");
			auto outputVar = Ast::AST::defineOutputVariate(reinterpret_cast<Ast::Variate*>(vsOutput.node.get())->type,0);
			Ast::AST::assign(outputVar,vsOutput.node);

			Ast::Parser::beginShaderParse(Ast::ShaderStage::Fragment); //记得处理Fragment的返回值
			auto fsParam = ParseHelper::createParam(fsFunc);
			if constexpr (!ParseHelper::hasReturnValue(fsFunc))
				ParseHelper::callLambda(fsFunc, std::move(fsParam));
			else
			{
				auto fsOutput = ParseHelper::callLambda(fsFunc, std::move(fsParam));
				static_assert(ParseHelper::isReturnProxy(fsFunc) /*or struct*/, "The output of the shader must be a proxy!");
				//1.proxy
				if constexpr (ParseHelper::isReturnProxy(fsFunc))
				{
					auto outputVar = Ast::AST::defineOutputVariate(reinterpret_cast<Ast::Variate*>(fsOutput.node.get())->type,0);
					Ast::AST::assign(outputVar,fsOutput.node);
				}
			}
		}
		else
		{
			ParseHelper::callLambda(vsFunc,std::move(vsParams));
			Ast::Parser::beginShaderParse(Ast::ShaderStage::Fragment);
			if constexpr (!ParseHelper::hasReturnValue(fsFunc))
				ParseHelper::callLambda(fsFunc);
			else
			{
				auto fsOutput = ParseHelper::callLambda(fsFunc);
				static_assert(ParseHelper::isReturnProxy(fsFunc), "The output of the shader must be a proxy!");
				auto outputVar = Ast::AST::defineOutputVariate(reinterpret_cast<Ast::Variate*>(fsOutput.node.get())->type,0);
				Ast::AST::assign(outputVar,fsOutput.node);
			}
		}
		RasterizedPipelineObject result;
		auto outputs = Ast::Parser::endPipelineParse();
		result.vertexGeneration = outputs[0].output;
		result.fragmentGeneration = outputs[1].output;
		return result;
	}
}
