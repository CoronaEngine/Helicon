#include <AST/AST.hpp>

int main()
{
	using namespace EmbeddedShader::AST;

	auto shaderCode = []()
	{
		auto var = AST::defineLocalVariate(42);
		AST::defineLocalVariate(1232.f);
	};

	puts(Parser::parse(shaderCode).c_str());
}