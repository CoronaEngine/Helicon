#pragma once
#include <string>
#include <Codegen/ParseHelper.h>
#include <Codegen/AST/AST.hpp>
#include <Codegen/AST/Parser.hpp>

namespace EmbeddedShader
{
	class RasterizedPipelineObject final
	{
		RasterizedPipelineObject() = default;
	public:
		static RasterizedPipelineObject compile(auto&& vertexShaderCode, auto&& fragmentShaderCode,std::source_location sourceLocation = std::source_location::current());
		std::unique_ptr<ShaderCodeCompiler> vertex;
		std::unique_ptr<ShaderCodeCompiler> fragment;
	private:
		static std::vector<Ast::ParseOutput> parse(auto&& vertexShaderCode, auto&& fragmentShaderCode);
	};

	RasterizedPipelineObject RasterizedPipelineObject::compile(auto&& vertexShaderCode, auto&& fragmentShaderCode,std::source_location sourceLocation)
	{
		Ast::Parser::setBindless(false);
		auto outputs = parse(vertexShaderCode,fragmentShaderCode);
		RasterizedPipelineObject result;
		result.vertex = std::make_unique<ShaderCodeCompiler>(outputs[0].output,ShaderStage::VertexShader, ShaderLanguage::Slang, sourceLocation);
		result.fragment = std::make_unique<ShaderCodeCompiler>(outputs[1].output,ShaderStage::FragmentShader, ShaderLanguage::Slang, sourceLocation);

		Ast::Parser::setBindless(true);
		outputs = parse(std::forward<decltype(vertexShaderCode)>(vertexShaderCode),
			std::forward<decltype(fragmentShaderCode)>(fragmentShaderCode));
		result.vertex->compile(outputs[0].output,ShaderStage::VertexShader, ShaderLanguage::Slang);
		result.fragment->compile(outputs[1].output,ShaderStage::FragmentShader, ShaderLanguage::Slang);
		return result;
	}

	std::vector<Ast::ParseOutput> RasterizedPipelineObject::parse(auto&& vertexShaderCode, auto&& fragmentShaderCode)
	{
		auto vsFunc = std::function(std::forward<decltype(vertexShaderCode)>(vertexShaderCode));
		auto fsFunc = std::function(std::forward<decltype(fragmentShaderCode)>(fragmentShaderCode));

		static_assert(ParseHelper::isMatchInputAndOutput(vsFunc,fsFunc), "The output of the vertex shader and the input of the fragment shader must match!");

		Ast::Parser::beginShaderParse(Ast::ShaderStage::Vertex);
		auto vsParams = ParseHelper::createParamTuple(vsFunc);
		if constexpr (ParseHelper::hasReturnValue(vsFunc))
		{
			auto vsOutput = ParseHelper::callLambda(vsFunc,std::move(vsParams));

			static_assert(ParseHelper::isReturnVariateProxy(vsFunc), "The output of the shader must be a proxy!");
			auto outputVar = Ast::AST::defineOutputVariate(reinterpret_cast<Ast::Variate*>(vsOutput.node.get())->type,0);
			Ast::AST::assign(outputVar,vsOutput.node);

			Ast::Parser::beginShaderParse(Ast::ShaderStage::Fragment); //记得处理Fragment的返回值
			auto fsParam = ParseHelper::createParam(fsFunc);
			if constexpr (!ParseHelper::hasReturnValue(fsFunc))
				ParseHelper::callLambda(fsFunc, std::move(fsParam));
			else
			{
				auto fsOutput = ParseHelper::callLambda(fsFunc, std::move(fsParam));
				static_assert(ParseHelper::isReturnVariateProxy(fsFunc) /*or struct*/, "The output of the shader must be a proxy!");
				//1.proxy
				if constexpr (ParseHelper::isReturnVariateProxy(fsFunc))
				{
					auto fsOutputVar = Ast::AST::defineOutputVariate(
						reinterpret_cast<Ast::Variate*>(fsOutput.node.get())->type, 0);
					Ast::AST::assign(fsOutputVar, fsOutput.node);
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
				static_assert(ParseHelper::isReturnVariateProxy(fsFunc), "The output of the shader must be a proxy!");
				auto outputVar = Ast::AST::defineOutputVariate(reinterpret_cast<Ast::Variate*>(fsOutput.node.get())->type,0);
				Ast::AST::assign(outputVar,fsOutput.node);
			}
		}
		return Ast::Parser::endPipelineParse();
	}
}
