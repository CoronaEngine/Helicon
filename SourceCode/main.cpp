#include <iostream>

#include "ShaderEmbededCodegen/ControlFlows.h"

#include "ShaderEmbededCodegen/CustomLibrary.h"


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

#include <AST.hpp>

int main(int argc, char* argv[])
{
	ast_test_main();
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