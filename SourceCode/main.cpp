#include <iostream>

#include "ShaderEmbededCodegen/ControlFlows.h"

#include "ShaderEmbededCodegen/CustomLibrary.h"

#include <AST/Parser.hpp>
#include <ktm/type/vec.h>
#include <ShaderGenerator/OpenGL/ShaderGenerator.hpp>

using namespace EmbeddedShader;

struct MyStruct1
{
	VariateProxy<int> int_A = 85244;
	VariateProxy<VariateProxy<int>> arr = { 1, 2 };
};

struct MyStruct2
{
	VariateProxy<int> int_A = 85244;
	VariateProxy<VariateProxy<int>> arr = { 1, 2 };
};

struct MyStruct3
{
	VariateProxy<MyStruct2> int_A;
};

int main(int argc, char* argv[])
{
	using namespace EmbeddedShader::Ast;
	using namespace ktm;

	Parser::setShaderGenerator(std::make_unique<ShaderGenerator::OpenGL::ShaderGenerator>());

	auto vertShaderCode = [&]()
	{
		auto aPos = AST::defineInputVariate<fvec3>();
		AST::assign(AST::getPositionOutput(),AST::createVecValue<fvec4>(aPos,1.f));
		AST::assign(AST::access(AST::getPositionOutput(), "x"),114.f);
	};

	auto fragShaderCode = [&]()
	{
		auto fragColor = AST::defineOutputVariate<fvec4>();
		AST::assign(fragColor,AST::createVecValue<fvec4>(1.0f, 0.5f, 0.2f, 1.0f));
	};

	puts(Parser::parse(vertShaderCode).c_str());
	puts(Parser::parse(fragShaderCode).c_str());

	auto lambda =
		[&]{
			VariateProxy<VariateProxy<int>> arr = { 1, 2 ,8, 1, 72, 11, 48416 };

			VariateProxy<MyStruct1> myStruct1;
			VariateProxy<MyStruct2> myStruct2;
			VariateProxy<MyStruct3> myStruct3;

			myStruct1->int_A = 1;

			VariateProxy<ktm::fvec3> fvec3_A = ktm::fvec3(1, 2, 3);
			VariateProxy<ktm::fvec3> fvec3_B = ktm::fvec3(1, 2, 3);

			fvec3_B = max(fvec3_A, fvec3_B);
			fvec3_B = min(fvec3_A, fvec3_B);

			$IF(fvec3_A)
			{
			}
			$ELIF(fvec3_B)
			{
			}
			$ELSE
			{
			}

			$WHILE(fvec3_A)
			{

			}

			// $FOR(VariateProxy i = 0; i < 10; ++i)
			// {
			//
			// }
		};

	std::string parseRes = EmbeddedShader::shaderParse(lambda);
	std::cout << parseRes;
}