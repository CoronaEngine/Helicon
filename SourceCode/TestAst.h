#include "ShaderEmbededCodegen/AbstractSyntaxTree.h"
#include "ShaderEmbededCodegen/ControlFlows.h"
#include <iostream>
#include "ShaderEmbededCodegen/CustomLibrary.h"

/*struct PushConsts
{
	uint uniformBufferIndex;
	uint outputImageIndex;
} pushConsts;


vec3 acesFilmicToneMapCurve(vec3 x)
{
	float a = 2.51f;
	float b = 0.03f;
	float c = 2.43f;
	float d = 0.59f;
	float e = 0.14f;

	return clamp((x * (a * x + b)) / (x * (c * x + d) + e), 0.0, 1.0);
}


vec3 acesFilmicToneMapInverse(vec3 x)
{
	vec3 a = -0.59 * x + 0.03;
	vec3 b = sqrt(-1.0127 * x * x + 1.3702 * x + 0.0009);
	vec3 c = 2 * (2.43 * x - 2.51);
	return ((a - b) / c);
}

vec3 gammaCorrection(vec3 x)
{
	return pow(x, vec3(1.0 / 2.2));
}
void main()
{
	vec3 final;
}
*/





struct MyStruct1
{
	VariateProxy<int> int_A = 85244;
	VariateProxy<VariateProxy<int>> arr = { 1, 2 };
};

/*
struct MyStruct2
{
	VariateProxy<int> int_A = 85244;
	VariateProxy<VariateProxy<int>> arr = { 1, 2 };
};

struct MyStruct3
{
	VariateProxy<MyStruct2> int_A;
	VariateProxy<VariateProxy<int>> arr = { 1, 2 ,8, 1, 72, 11, 48416 };
};
*/

inline void TestAst()
{
	auto lambda = [&]()
	{

		VariateProxy<MyStruct1> myStruct;

		myStruct->int_A = 1;

		//VariateProxy<ktm::uvec3> uvec3_A({ 1, 2, 3 });

		//VariateProxy<ktm::uvec3> uvec3_L({ 1, 1, 1 });

		//VariateProxy<ktm::uvec3> uvec3_H({ 2, 2, 2 });


		//VariateProxy<ktm::uvec3> uvec3_B = clamp(uvec3_A, uvec3_L, uvec3_H);

		//uvec3_A = MathFunc::clamp(uvec3_A, uvec3_L, uvec3_H);

		VariateProxy<ktm::fvec3> fvec3_A = ktm::fvec3(1, 2, 3);
		VariateProxy<ktm::fvec3> fvec3_B = ktm::fvec3(1, 2, 3);

		fvec3_B = MathFunc::sqrt(fvec3_A);

		//fvec3_B[0] = MathFunc::pow(fvec3_B[1], fvec3_B[2]);

		//fvec3_B = pow(fvec3_A, fvec3_B);

		//uvec3_B = pow(uvec3_A, uvec3_B);

		//VariateProxy<int> int_A = 1; // var_0 = 1;

		//VariateProxy<int> int_B = int_A; // var_2 = var_0;

		//int_A = int_A * 2;

		/*
		struct MyStruct1
		{
			VariateProxy<int> int_A = 85244;
		};

		VariateProxy<MyStruct1> Struct_D1;
		Struct_D1->int_A = 3;

		VariateProxy<VariateProxy<int>> arrayInt = { 1,2,3,4,5 };

		VariateProxy<VariateProxy<ktm::uvec4>> arrayRGBA = { ktm::uvec4(),ktm::uvec4(),ktm::uvec4(),ktm::uvec4() };//GPU image


		VariateProxy<VariateProxy<MyStruct1>> arrayStruct = { Struct_D1 ,Struct_D1 ,Struct_D1 };//array of struct (GPU buffer)


		VariateProxy<VariateProxy<VariateProxy<int>>> arrayArrayInt = { arrayInt,arrayInt,arrayInt,arrayInt,arrayInt };
		*/

		//VariateProxy<MyStruct1> Struct_D2;
		//Struct_D2->int_A = 4;

		//int_B = -int_B;
		/*

		ktm::fmat4x4 testMat = { {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4} };
		VariateProxy<ktm::fmat4x4> testMat_Proxy = testMat; // => Mat4 var_1 = Mat4();
		VariateProxy<ktm::fmat4x4> testMat_Prox_2 = ktm::fmat4x4({ {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4}, {1, 2, 3, 4} }); // => Mat4 var_1 = Mat4();

		
		VariateProxy<int> int_B = int_A; // var_2 = var_0;

		
		VariateProxy<VariateProxy<int>> testArray_Var = { int_A };

		int arr[] = { 1, 2, 3 };
		VariateProxy<VariateProxy<int>> testArray_Liter = { 451, 2, 3 };// => int arr[3] = {x, x, x};

		//VariateProxy<VariateProxy<int>> testArray_cp = arr;

		VariateProxy<VariateProxy<int>> testArray_Var_1 = { int_A, 1 };

		VariateProxy<VariateProxy<VariateProxy<int>>> testArray_Var_2 = { {int_A}, {1} };
		*/

		//VariateProxy<MyStruct1> Struct_D1;

		/*

		VariateProxy<MyStruct2> Struct_D2;

		VariateProxy<MyStruct3> Struct_D3;
		*/
	};

	std::string parseRes = abstractSyntaxTree.parse(lambda);
	std::cout << parseRes;
	/*
	int* testPoint =(int*) malloc(20*sizeof(int));
	testPoint[10] = 0;

	

	int_A = int_A + int_A;

	
	VariateProxy<VariateProxy<int>>*  dataARR = &Struct_D2->arr;
	VariateProxy<int>* dataINT = &Struct_D2->int_A;

	VariateProxy<MyStruct1> Struct_A;
	VariateProxy<MyStruct3> Struct_B;
	VariateProxy<MyStruct2> Struct_E;
	VariateProxy<MyStruct1> Struct_C;
	VariateProxy<MyStruct3> Struct_F;

	VariateProxy<MyStruct3> Struct_S = Struct_F;

	MyStruct3 test;
	VariateProxy<MyStruct3> Struct_T = test;

	

	

	VariateProxy<VariateProxy<MyStruct3>> testArrayOfStruct = { Struct_F, Struct_F, Struct_F };

	VariateProxy<VariateProxy<int>> testArrayArray = { {678, 2, 3} ,{1, 2, 3} };

	auto lambda = [&]()
		{
			VariateProxy<float> f_A = 1.0;

			VariateProxy<int> int_A = 1;
			VariateProxy<int> uint_B = 2;
			int_A = int_A + int_A;
			int_A = int_A + 2 + 3;
			int_A = int_A + uint_B;

			
			arr[3] = 4;

			int_A = int_A + arr[3];



			//$IF(&int_A)
			//{
			//	int_A = int_A + uint_B;
			//	int_A = int_A + 22;
			//}
			//$ELIF(&int_A)
			//{
			//	VariateProxy<int> int_A = 1;
			//}
			//$ELSE
			//{
			//	VariateProxy<int> int_A = 1;
			//};
		};

	std::string res = runDslParse(lambda);

	return 0;
	*/
}
