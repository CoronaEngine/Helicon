#include <iostream>

#include "ShaderEmbededCodegen/ControlFlows.h"

#include "ShaderEmbededCodegen/CustomLibrary.h"


#include <boost/pfr.hpp>


struct Proxy
{

};

struct TEST_GPU_FOR
{
	explicit TEST_GPU_FOR(const std::function<void()>& content)
	{
		content();
	}
};

struct TEST_GPU_FOR_CONDITION
{
	struct Proxy
	{
		Proxy()
		{
			puts("outter");
		}
	};

	void operator()() const
	{

    }
};

#define TEST_FOR(content) \
	if (TEST_GPU_FOR gpu_for([&] {content;});true)

void test_func()
{
	if (TEST_GPU_FOR gpu_for([&]
	{
		struct{
			struct Proxy
			{
				Proxy()
				{
					puts("inner");
				}
			};

			void operator()() const
			{
				Proxy a;
			}
		} gpu_for_condition;
		gpu_for_condition();
	});
	true)
	{
	}
}



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
	test_func();

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