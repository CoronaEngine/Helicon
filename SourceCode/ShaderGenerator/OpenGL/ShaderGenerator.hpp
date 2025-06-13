#pragma once
#include <memory>
#include <string>
#include <AST/AST.hpp>
#include <AST/Enum.hpp>
#include <ShaderGenerator/ShaderGenerator.hpp>

namespace EmbeddedShader::ShaderGenerator::OpenGL
{
	class ShaderGenerator : public BaseShaderGenerator
	{
	public:
		std::string getVariateTypeName(Ast::VariateType variateType) override;
	};
}
