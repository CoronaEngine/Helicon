#include <iostream>

#include "ShaderEmbededCodegen/ControlFlows.h"

#include "ShaderEmbededCodegen/CustomLibrary.h"


#include <boost/pfr.hpp>
#include <boost/preprocessor.hpp>




#define PFR_REFLECTABLE_MEMBER_FUNCTION_ONE(r, CLASSNAME, i, MemberFunction) \
    decltype(std::mem_fn(&CLASSNAME::MemberFunction))                        \
        BOOST_PP_CAT(MemberFunction, _ptr) = std::mem_fn(&CLASSNAME::MemberFunction);

#define PFR_REFLECTABLE_MEMBER_FUNCTION(CLASSNAME, ...) \
    BOOST_PP_SEQ_FOR_EACH_I(PFR_REFLECTABLE_MEMBER_FUNCTION_ONE, CLASSNAME, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))


struct Actor
{
	int index;

	int get_index() { return 0; }
	void set_index(const int& val){}
	void say(){}

	//PFR_REFLECTABLE_MEMBER_FUNCTION_ONE(Actor,get_index);
	//PFR_REFLECTABLE_MEMBER_FUNCTION_ONE(Actor,set_index);
	//PFR_REFLECTABLE_MEMBER_FUNCTION_ONE(Actor,say);
	PFR_REFLECTABLE_MEMBER_FUNCTION(Actor, get_index, set_index, say);
};

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

	Actor test;

	auto lammdaReflect = [&](auto&& structMember, auto name) {
		// name.c_str() 可以获取成员名称的 C 风格字符串
		std::cout << "Member Name: "
			<< ", Member Value Type: " << typeid(structMember).name()
			<< ", Member Value: " << structMember // 打印成员的实际值
			<< std::endl;
		};

	boost::pfr::for_each_field_with_name(test, lammdaReflect);


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