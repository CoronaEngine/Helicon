#include <iostream>

#include "Codegen/ControlFlows.h"

#include "Codegen/CustomLibrary.h"

#include"Compiler/ShaderCodeCompiler.h"

#include <Codegen/AST/Parser.hpp>
#include <Codegen/AST/AST.hpp>
#include <Codegen/Generator/SlangGenerator.hpp>
#include <utility>
#include <ktm/type/vec.h>

#include <Codegen/RasterizedPipelineObject.h>

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

//
//void test(float fov)//45.0
//{
//	VariateProxy<float> fov = ...;
//
//	auto vertShaderCode = [&]()
//		{
//			fov;
//		};
//
//	auto fragShaderCode = [&]()
//		{
//			fov;
//		};
//}


template<typename Type>
using Image2D = VariateProxy<VariateProxy<VariateProxy<Type>>>;

template<typename Type>
using Buffer = VariateProxy<VariateProxy<Type>>;

int main(int argc, char* argv[])
{
	// auto lammdaReflect = [&](std::string_view name, auto&& structMember, std::size_t i) {
	// 	std::cout << "Member index: " << i
	// 		<< ", Member Value Type: " << typeid(structMember).name()
	// 		<< ", Member Name: " << name
	// 		<< std::endl;
	// };
	// boost::pfr::for_each_field_with_name(MyStruct2{}, lammdaReflect);


	using namespace EmbeddedShader::Ast;
	using namespace ktm;


	auto vertShaderCode = [&]()
	{
		auto aPos = AST::defineInputVariate<fvec3>(0);
		AST::assign(AST::getPositionOutput(),AST::createVecValue<fvec4>(aPos,1.f));

		//AST::assign(AST::access(color, "r"), 1.f);
	};

	auto color = AST::defineUniformVariate<fvec4>();
	auto fragShaderCode = [&]()
	{
		auto fragColor = AST::defineOutputVariate<fvec4>(0);
		AST::assign(fragColor,color);
	};

	auto parseOutput = Parser::parse({{vertShaderCode,Ast::ShaderStage::Vertex},{fragShaderCode, Ast::ShaderStage::Fragment}});
	puts(parseOutput[0].output.c_str());
	puts(parseOutput[1].output.c_str());

	//std::cout << "color permissions:" << color->permissions << "\n";

	// ShaderCodeCompiler vertxShader(parseOutput[0].output, ::ShaderStage::VertexShader,ShaderLanguage::Slang);
	// ShaderCodeCompiler fragShader(parseOutput[1].output, ::ShaderStage::FragmentShader,ShaderLanguage::Slang);

	puts("------------------- Front-End Test -------------------");
	auto vertex = [&](VariateProxy<float> input)
	{
		VariateProxy<int> a;
	};

	auto fragment = [&]
	{
		VariateProxy<int> b;
	};

	auto pipeline = RasterizedPipelineObject::parse(vertex, fragment);
	puts(pipeline.vertexGeneration.c_str());
	puts(pipeline.fragmentGeneration.c_str());

	//////////////////////////////////// A demo using the EDSL ////////////////////////////////////

	// VariateProxy<ktm::fvec3> vertexInput1 = ktm::fvec3(1, 2, 3);
	//
	// VariateProxy<ktm::fvec3> vertexOutput1 = ktm::fvec3(1, 2, 3);
	//
	// VariateProxy<ktm::fmat4x4> vertexOutput2 = ktm::fmat4x4::from_eye();
	// VariateProxy<VariateProxy<int>> vertexOutput3 = { 1, 2 ,8, 1, 72, 11, 48416 };
	// VariateProxy<VariateProxy<VariateProxy<int>>> vertexOutput4 = { { 1, 2 ,8, 1}, {72, 11, 48416 } };
	//
	//
	// Image2D<ktm::fvec3> image0 = { { ktm::fvec3(1, 2, 3)}, { ktm::fvec3(1, 2, 3) } };
	// Buffer<ktm::fvec3> buffer0 = { ktm::fvec3(1, 2, 3),  ktm::fvec3(1, 2, 3) };
	//
	// VariateProxy<MyStruct1> buffer1;//ubo or ssbo
	// VariateProxy<MyStruct2> buffer2;//ubo or ssbo
	// VariateProxy<MyStruct3> buffer3;//ubo or ssbo
	//
	// auto vertexShaderDemo =
	// 	[&]{
	// 		//uint32_t vertexIndex = 0; //globle vertex index
	// 		//auto vertex = buffer0[vertexIndex];
	//
	// 		vertexInput1;
	// 		//vertexOutput1 = ktm::fvec3(1, 2, 3);
	// 		vertexOutput2 = ktm::fmat4x4::from_eye();
	// 		vertexOutput3 = { 1, 2 ,8, 1, 72, 11, 48416 };
	//
	// 		buffer1->int_A = 1;
	//
	// 		VariateProxy<ktm::fvec3> fvec3_A = ktm::fvec3(1, 2, 3);
	// 		VariateProxy<ktm::fvec3> fvec3_B = ktm::fvec3(1, 2, 3);
	//
	// 		fvec3_B = max(fvec3_A, fvec3_B);
	// 		fvec3_B = min(fvec3_A, fvec3_B);
	//
	//
	// 		$IF(fvec3_A)
	// 		{
	// 		}
	// 		$ELIF(fvec3_B)
	// 		{
	// 		}
	// 		$ELSE
	// 		{
	// 		}
	//
	// 		$WHILE(fvec3_A)
	// 		{
	//
	// 		}
	//
	// 		$IF(fvec3_A)
	// 		{
	// 			$IF(fvec3_A)
	// 			{
	// 			}
	// 		}
	//
	// 		// $FOR(VariateProxy i = 0; true; ++i)
	// 		// {
	// 		// }
	//
	// 		$DO
	// 		{
	//
	// 			$WHILE(fvec3_A)
	// 			{
	// 			}
	//
	// 			$WHILE(fvec3_A)
	// 			{
	// 			}
	// 		}
	// 		$WHILE(fvec3_A);
	// };
	//
	// auto fragShaderDemo =
	// 	[&] {
	// 		VariateProxy<ktm::fmat4x4> fragInput = vertexOutput2;
	// 		//outputColor = fvec4(1, 0, 0, 1); //globle output color
	// 	};
	//
	// auto fragShaderDemo2 =
	// 	[&] {
	// 	VariateProxy<ktm::fmat4x4> fragInput = vertexOutput2;
	// 	//outputColor = fvec4(1, 0, 0, 1); //globle output color
	// 	};
	//
	// auto computeShaderDemo =
	// 	[&] {
	// 		buffer2->int_A;
	// 	};
	// //////////////////////////////////// A demo using the EDSL ////////////////////////////////////
	//
	//
	// //////////////////////////////////// A NEW demo using the EDSL ////////////////////////////////////
	//
	// VariateProxy<MyStruct1> uniform; //UBO
	// Buffer<MyStruct1> arrayProxy = {{}}; //RWStructuredBuffer/StructuredBuffer
	// auto newVert = [&](VariateProxy<fvec2> pos) //Vertex Input
	// {
	// 	//xxx
	// 	//return //Output
	// };

	//////////////////////////////////// A NEW demo using the EDSL ////////////////////////////////////
}
