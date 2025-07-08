#pragma once
#include <Codegen/Generator/ShaderGenerator.hpp>
//#include <stdfloat>

namespace EmbeddedShader::Generator
{
	//后续把BaseShaderGenerator移除

	class SlangGenerator final
	{
		template<typename T>
		static constexpr std::string_view variateTypeNameMap = "unknown";

	public:
		std::string getShaderOutput(const Ast::EmbeddedShaderStructure& structure);
		std::string getVariateTypeName(Ast::VariateType variateType);

//		std::string getVariateTypeName

		std::string getParseOutput(const Ast::DefineLocalVariate* node);
		std::string getParseOutput(const Ast::DefineInputVariate* node);
		std::string getParseOutput(const Ast::Assign* node);
		std::string getParseOutput(const Ast::BinaryOperator* node);
		std::string getParseOutput(const Ast::MemberAccess* node);
		std::string getParseOutput(const Ast::DefineOutputVariate* node);
		std::string getParseOutput(const Ast::IfStatement* node);

		std::shared_ptr<Ast::Variate> getPositionOutput();
	};

#define DEFINE_VARIATE_TYPE_NAME_MAP(type, name) \
	template<> constexpr std::string_view SlangGenerator::variateTypeNameMap<type> = #name

	DEFINE_VARIATE_TYPE_NAME_MAP(int8_t, int8_t);
	DEFINE_VARIATE_TYPE_NAME_MAP(int16_t, int16_t);
	DEFINE_VARIATE_TYPE_NAME_MAP(int, int);
	DEFINE_VARIATE_TYPE_NAME_MAP(int64_t, int64_t);
	DEFINE_VARIATE_TYPE_NAME_MAP(uint8_t, uint8_t);
	DEFINE_VARIATE_TYPE_NAME_MAP(uint16_t, uint16_t);
	DEFINE_VARIATE_TYPE_NAME_MAP(uint32_t, uint);
	DEFINE_VARIATE_TYPE_NAME_MAP(uint64_t, uint64_t);
	DEFINE_VARIATE_TYPE_NAME_MAP(float, float);
	DEFINE_VARIATE_TYPE_NAME_MAP(double, double);
	//DEFINE_VARIATE_TYPE_NAME_MAP(std::float16_t, half);

#undef DEFINE_VARIATE_TYPE_NAME_MAP
}
