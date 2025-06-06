#include <AST/AST.hpp>

int main()
{
	using namespace EmbeddedShader::AST;

	auto shaderCode = []()
	{
		auto vertexInput = AST::defineInputVariate<int>();
		auto var = AST::defineLocalVariate(42);
		auto var2 = AST::defineLocalVariate(var->type,
			AST::binaryOperator(AST::binaryOperator(var,114, "+"),var, "+"));
		AST::assign(var2,vertexInput);
	};

	puts(Parser::parse(shaderCode).c_str());
}