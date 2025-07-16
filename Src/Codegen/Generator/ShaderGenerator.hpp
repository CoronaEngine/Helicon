#pragma once
#include <memory>
#include <string>
#include <Codegen/AST/Enum.hpp>
#include <Codegen/AST/Node.hpp>
#include <Codegen/AST/Struct.hpp>

namespace EmbeddedShader::Generator
{
	class BaseShaderGenerator
	{
	public:
		virtual ~BaseShaderGenerator() = default;
		virtual std::string getShaderOutput(const Ast::EmbeddedShaderStructure& structure) = 0;

		virtual std::string getVariateTypeName(Ast::VariateType variateType) = 0;

		virtual std::string getValueOutput(int32_t value) = 0;
		virtual std::string getValueOutput(uint32_t value) = 0;
		virtual std::string getValueOutput(float value) = 0;
		virtual std::string getValueOutput(double value) = 0;
		virtual std::string getValueOutput(bool value) = 0;
		virtual std::string getValueOutput(const ktm::fvec2& value) = 0;
		virtual std::string getValueOutput(const ktm::fvec3& value) = 0;
		virtual std::string getValueOutput(const ktm::fvec4& value) = 0;
		virtual std::string getValueOutput(const ktm::svec2& value) = 0;
		virtual std::string getValueOutput(const ktm::svec3& value) = 0;
		virtual std::string getValueOutput(const ktm::svec4& value) = 0;
		virtual std::string getValueOutput(const ktm::uvec2& value) = 0;
		virtual std::string getValueOutput(const ktm::uvec3& value) = 0;
		virtual std::string getValueOutput(const ktm::uvec4& value) = 0;
		virtual std::string getValueOutput(const ktm::dvec2& value) = 0;
		virtual std::string getValueOutput(const ktm::dvec3& value) = 0;
		virtual std::string getValueOutput(const ktm::dvec4& value) = 0;
		virtual std::string getValueOutput(const ktm::vec<2, bool>& value) = 0;
		virtual std::string getValueOutput(const ktm::vec<3, bool>& value) = 0;
		virtual std::string getValueOutput(const ktm::vec<4, bool>& value) = 0;
		virtual std::string getValueOutput(const ktm::fmat2x2& value) = 0;
		virtual std::string getValueOutput(const ktm::fmat3x3& value) = 0;
		virtual std::string getValueOutput(const ktm::fmat4x4& value) = 0;
		virtual std::string getValueOutput(const ktm::fmat2x3& value) = 0;
		virtual std::string getValueOutput(const ktm::fmat2x4& value) = 0;
		virtual std::string getValueOutput(const ktm::fmat3x2& value) = 0;
		virtual std::string getValueOutput(const ktm::fmat3x4& value) = 0;
		virtual std::string getValueOutput(const ktm::fmat4x2& value) = 0;
		virtual std::string getValueOutput(const ktm::fmat4x3& value) = 0;

		virtual std::string getParseOutput(const Ast::DefineLocalVariate* node) = 0;
		virtual std::string getParseOutput(const Ast::DefineInputVariate* node) = 0;
		virtual std::string getParseOutput(const Ast::Assign* node) = 0;
		virtual std::string getParseOutput(const Ast::BinaryOperator* node) = 0;
		virtual std::string getParseOutput(const Ast::MemberAccess* node) = 0;
		virtual std::string getParseOutput(const Ast::DefineOutputVariate* node) = 0;
		virtual std::string getParseOutput(const Ast::UniformVariate* node) = 0;
		virtual std::string getParseOutput(const Ast::DefineUniformVariate* node) = 0;
		virtual std::string getParseOutput(const Ast::IfStatement* node) = 0;

		virtual std::shared_ptr<Ast::Variate> getPositionOutput() = 0;
	protected:
		static thread_local inline size_t nestHierarchy = 1;
		static std::string getCodeIndentation();
	};
}
