#pragma once
#include <string>
#include <Codegen/ParseHelper.h>
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
		//note:创建tuple时要注意设置Input Flag
		auto vsParams = ParseHelper::createParamTuple(vsFunc);
		if constexpr (ParseHelper::hasReturnValue(vsFunc))
		{
			//记得设置in-lambda标记
			auto vsOutput = std::apply(vsFunc,vsParams);
			Ast::Parser::beginShaderParse(Ast::ShaderStage::Fragment); //记得处理Fragment的返回值
			// if constexpr (ParseHelper::hasReturnValue(fsFunc))
			// {
			// 	//1.Proxy
			// 	if constexpr (ParseHelper::isReturnProxy(fsFunc))
			// 	{
			// 		auto fsOutput = fsFunc(vsOutput);
			// 		auto outputVar = Ast::AST::defineOutputVariate(fsOutput.node->type,0);
			// 		Ast::AST::assign(outputVar,fsOutput.node->value);
			// 	}
			// 	//2.Struct
			// 	else
			// 	{
			//
			// 	}
			// }
			// else
				fsFunc(vsOutput);
		}
		else
		{
			std::apply(vsFunc,vsParams);
			Ast::Parser::beginShaderParse(Ast::ShaderStage::Fragment);
			fsFunc();
		}
		RasterizedPipelineObject result;
		auto outputs = Ast::Parser::endPipelineParse();
		result.vertexGeneration = outputs[0].output;
		result.fragmentGeneration = outputs[1].output;
		return result;
	}
}
