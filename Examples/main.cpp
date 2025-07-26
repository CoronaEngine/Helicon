#include <iostream>

#include "Codegen/ControlFlows.h"

#include "Codegen/CustomLibrary.h"

#include"Compiler/ShaderCodeCompiler.h"

#include <Codegen/AST/Parser.hpp>
#include <Codegen/AST/AST.hpp>
#include <Codegen/Generator/SlangGenerator.hpp>
#include <utility>
#include <ktm/type/vec.h>

#include <Codegen/RasterizedPipelineObject.h>
#include <Codegen/BuiltinVariate.h>
#include <Codegen/TypeAlias.h>

using namespace EmbeddedShader;

struct VertexInput
{
	Float3 inPosition;
	Float3 inNormal;
	Float2 inTexCoord;
	Float3 inColor;
};

struct VertexOutput
{
	Float3 fragPos;
	Float3 fragNormal;
	Float2 fragTexCoord;
	Float3 fragColor;
};

int main(int argc, char* argv[])
{
	using namespace EmbeddedShader::Ast;
	using namespace ktm;

	Float4x4 model;
	Float4x4 view;
	Float4x4 proj;
	Float3 viewPos;
	Float3 lightColor;
	Float3 lightPos;
	auto vertex = [&](Aggregate<VertexInput> input)
	{
		Aggregate<VertexOutput> output;
		position() = mul(mul(mul(proj,view),model),Float4(input->inPosition,1.0));
	};

	auto fragment = [&]()
	{

	};

	Parser::setBindless(true);
	auto pipeline = RasterizedPipelineObject::parse(vertex, fragment);
	puts(pipeline.vertexGeneration.c_str());
	puts(pipeline.fragmentGeneration.c_str());

    ShaderCodeCompiler vertxShader(pipeline.vertexGeneration, ::ShaderStage::VertexShader,ShaderLanguage::Slang);
    ShaderCodeCompiler fragShader(pipeline.fragmentGeneration, ::ShaderStage::FragmentShader,ShaderLanguage::Slang);
}
