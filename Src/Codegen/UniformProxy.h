#pragma once
#include <Codegen/AST/AST.hpp>

namespace EmbeddedShader
{
	template<typename T>
	class UniformProxy
	{
	public:
	private:
		std::shared_ptr<Ast::UniformVariate> uniform;
	};
}