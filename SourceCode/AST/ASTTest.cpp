#include <AST/AST.hpp>

int main()
{
	using namespace EmbeddedShader::AST;

	auto shaderCode = []()
	{
		Node::localVariate(42);
	};

	puts(Parser::parse(shaderCode).c_str());
}