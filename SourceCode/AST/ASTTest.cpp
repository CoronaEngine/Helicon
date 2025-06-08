#include <AST/AST.hpp>
#include <ktm/type/vec.h>

int main()
{
	using namespace EmbeddedShader::AST;
	using namespace ktm;

	auto shaderCode = []()
	{
		auto aPos = AST::defineInputVariate<fvec3>();
		AST::assign(AST::getPositionOutput(),AST::createVecValue<fvec4>(aPos,AST::createValue(1.f)));
	};

	puts(Parser::parse(shaderCode).c_str());
}
