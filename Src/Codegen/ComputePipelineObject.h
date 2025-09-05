#pragma once
#include <functional>
#include <Codegen/ParseHelper.h>
#include <Codegen/AST/AST.hpp>
#include <Codegen/AST/Parser.hpp>
#include <Compiler/ShaderCodeCompiler.h>

namespace EmbeddedShader
{
	class ComputePipelineObject
	{
	public:
		static ComputePipelineObject compile(auto&& computeShaderCode, ktm::uvec3 numthreads = ktm::uvec3(1), CompilerOption compilerOption = {}, std::source_location sourceLocation = std::source_location::current());
		std::unique_ptr<ShaderCodeCompiler> compute;
	private:
		static std::vector<Ast::ParseOutput> parse(auto&& computeShaderCode);
	};

	ComputePipelineObject ComputePipelineObject::compile(auto&& computeShaderCode, ktm::uvec3 numthreads,CompilerOption compilerOption,std::source_location sourceLocation)
	{
		Generator::SlangGenerator::numthreads = numthreads;
		Ast::Parser::setBindless(false);
		auto outputs = parse(computeShaderCode);
		ComputePipelineObject result;
		result.compute = std::make_unique<ShaderCodeCompiler>(outputs[0].output, ShaderStage::ComputeShader, ShaderLanguage::Slang,compilerOption,sourceLocation);

		if (compilerOption.enableBindless)
		{
			Ast::Parser::setBindless(true);
			outputs = parse(std::forward<decltype(computeShaderCode)>(computeShaderCode));
			result.compute->compile(outputs[0].output, ShaderStage::ComputeShader, ShaderLanguage::Slang,compilerOption);
		}
		return result;
	}

	std::vector<Ast::ParseOutput> ComputePipelineObject::parse(auto&& computeShaderCode)
	{
		auto csFunc = std::function(std::forward<decltype(computeShaderCode)>(computeShaderCode));

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
		return Ast::Parser::endPipelineParse();
	}
}
