#include <iostream>
#include <ppltasks.h>

#include "Codegen/ControlFlows.h"

#include "Codegen/CustomLibrary.h"

#include"Compiler/ShaderCodeCompiler.h"

#include <Codegen/AST/Parser.hpp>
#include <ktm/type/vec.h>
#include <Codegen/Generator/OpenGL/ShaderGenerator.hpp>

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
	auto lammdaReflect = [&](std::string_view name, auto&& structMember, std::size_t i) {
		std::cout << "Member index: " << i
			<< ", Member Value Type: " << typeid(structMember).name()
			<< ", Member Name: " << name
			<< std::endl;
	};
	boost::pfr::for_each_field_with_name(MyStruct2{}, lammdaReflect);


	using namespace EmbeddedShader::Ast;
	using namespace ktm;

	Parser::setShaderGenerator(std::make_unique<ShaderGenerator::OpenGL::ShaderGenerator>());

	auto vertShaderCode = [&]()
	{
		auto aPos = AST::defineInputVariate<fvec3>(0);
		AST::assign(AST::getPositionOutput(),AST::createVecValue<fvec4>(aPos,1.f));
		AST::assign(AST::access(AST::getPositionOutput(), "x"),114.f);
	};

	auto fragShaderCode = [&]()
	{
		auto fragColor = AST::defineOutputVariate<fvec4>(0);
		auto outColor = AST::defineUniformVariate<fvec4>(0);
		AST::beginIf(AST::binaryOperator(AST::access(outColor,"r"),0.f,"!="));
		AST::assign(fragColor,outColor);
		AST::beginIf(AST::binaryOperator(AST::access(outColor,"r"),0.f,"!="));
		AST::assign(fragColor,outColor);
		AST::endIf();
		AST::endIf();
	};

	puts(Parser::parse(vertShaderCode).c_str());
	puts(Parser::parse(fragShaderCode).c_str());

	ShaderCodeCompiler vertxShader(Parser::parse(vertShaderCode), ShaderStage::VertexShader);
	ShaderCodeCompiler fragShader(Parser::parse(fragShaderCode), ShaderStage::FragmentShader);



	//////////////////////////////////// A demo using the EDSL ////////////////////////////////////

	VariateProxy<ktm::fvec3> vertexInput1 = ktm::fvec3(1, 2, 3);

	VariateProxy<ktm::fvec3> vertexOutput1 = ktm::fvec3(1, 2, 3);

	VariateProxy<ktm::fmat4x4> vertexOutput2 = ktm::fmat4x4::from_eye();
	VariateProxy<VariateProxy<int>> vertexOutput3 = { 1, 2 ,8, 1, 72, 11, 48416 };
	VariateProxy<VariateProxy<VariateProxy<int>>> vertexOutput4 = { { 1, 2 ,8, 1}, {72, 11, 48416 } };


	Image2D<ktm::fvec3> image0 = { { ktm::fvec3(1, 2, 3)}, { ktm::fvec3(1, 2, 3) } };
	Buffer<ktm::fvec3> buffer0 = { ktm::fvec3(1, 2, 3),  ktm::fvec3(1, 2, 3) };

	VariateProxy<MyStruct1> buffer1;//ubo or ssbo
	VariateProxy<MyStruct2> buffer2;//ubo or ssbo
	VariateProxy<MyStruct3> buffer3;//ubo or ssbo

	auto vertexShaderDemo =
		[&]{
			//uint32_t vertexIndex = 0; //globle vertex index
			//auto vertex = buffer0[vertexIndex];

			vertexInput1;
			//vertexOutput1 = ktm::fvec3(1, 2, 3);
			vertexOutput2 = ktm::fmat4x4::from_eye();
			vertexOutput3 = { 1, 2 ,8, 1, 72, 11, 48416 };

			buffer1->int_A = 1;

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

			$IF(fvec3_A)
			{
				$IF(fvec3_A)
				{
				}
			}

			// $FOR(VariateProxy i = 0; true; ++i)
			// {
			// }

			$DO
			{

				$WHILE(fvec3_A)
				{
				}

				$WHILE(fvec3_A)
				{
				}
			}
			$WHILE(fvec3_A);
	};

	auto fragShaderDemo =
		[&] {
			VariateProxy<ktm::fmat4x4> fragInput = vertexOutput2;
			//outputColor = fvec4(1, 0, 0, 1); //globle output color
		};

	auto fragShaderDemo2 =
		[&] {
		VariateProxy<ktm::fmat4x4> fragInput = vertexOutput2;
		//outputColor = fvec4(1, 0, 0, 1); //globle output color
		};

	auto computeShaderDemo =
		[&] {
			buffer2->int_A;
		};
	//////////////////////////////////// A demo using the EDSL ////////////////////////////////////

}