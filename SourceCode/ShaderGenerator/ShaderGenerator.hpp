#pragma once
#include <memory>
#include <string>
#include <AST/AST.hpp>

namespace EmbeddedShader::ShaderGenerator
{
	class ShaderGenerator
	{
	public:
		virtual ~ShaderGenerator() = default;
	};
}
