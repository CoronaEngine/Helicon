#pragma once
#include <memory>
#include <string>
#include <AST/AST.hpp>
#include <AST/Enum.hpp>

namespace EmbeddedShader::ShaderGenerator
{
	class BaseShaderGenerator
	{
	public:
		virtual ~BaseShaderGenerator() = default;
		virtual std::string getVariateTypeName(Ast::VariateType variateType) = 0;
	};
}
