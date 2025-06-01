#include <AST/AST.hpp>

int main()
{
	using namespace EmbeddedShader::AST;

	auto shaderCode = []()
	{
		auto var = AST::defineLocalVariate(42);
		AST::defineLocalVariate(var->type, AST::binaryOperator(AST::binaryOperator(var,114, "+"),var, "+"));
	};

	puts(Parser::parse(shaderCode).c_str());
}