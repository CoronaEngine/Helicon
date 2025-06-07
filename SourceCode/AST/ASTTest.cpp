#include <AST/AST.hpp>
#include <ktm/type/vec.h>

int main()
{
	using namespace EmbeddedShader::AST;
	using namespace ktm;

	auto shaderCode = []()
	{
		//auto vec = AST::defineLocalVariate(fvec2{2.f,3.f});
		auto vertexInput = AST::defineInputVariate<int>();
		auto var = AST::defineLocalVariate(42);
		auto var2 = AST::defineLocalVariate(var->type,
			AST::binaryOperator(AST::binaryOperator(var,114, "+"),var, "+"));
		AST::assign(var2,vertexInput);
	};

	puts(Parser::parse(shaderCode).c_str());
}
