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

struct VertexData
{
    Float4 pos;
    Float2 texCoord;
};

int main(int argc, char* argv[])
{
	using namespace EmbeddedShader::Ast;
	using namespace ktm;

	Texture2D<fvec4> texture2d;
	Sampler sampler;
	auto vertex = [&](Aggregate<VertexData> input)
	{
		position() = input->pos;
	    return texture2d.sample(sampler,input->texCoord);
	};

	auto fragment = [&](Float4 input)
	{
		return input;
	};

	Parser::setBindless(true);
	auto pipeline = RasterizedPipelineObject::parse(vertex, fragment);
	puts(pipeline.vertexGeneration.c_str());
	puts(pipeline.fragmentGeneration.c_str());

    ShaderCodeCompiler vertxShader(pipeline.vertexGeneration, ::ShaderStage::VertexShader,ShaderLanguage::Slang);
    ShaderCodeCompiler fragShader(pipeline.fragmentGeneration, ::ShaderStage::FragmentShader,ShaderLanguage::Slang);
}
