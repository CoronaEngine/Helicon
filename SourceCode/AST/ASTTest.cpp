#include <AST/AST.hpp>

int main()
{
	using namespace EmbeddedShader::AST;

	auto shaderCode = []()
	{
		Node::localVariate(42);
		Node::localVariate(1232.f);
	};

	puts(Parser::parse(shaderCode).c_str());
}