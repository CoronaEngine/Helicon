#pragma once
#include <memory>
#include <string>
#include <Codegen/AST/AST.hpp>
#include <Codegen/AST/Enum.hpp>
#include "../ShaderGenerator.hpp"

namespace EmbeddedShader::ShaderGenerator::OpenGL
{
	class ShaderGenerator final : public BaseShaderGenerator
	{
	public:
		std::string getShaderOutput(const Ast::EmbeddedShaderStructure& structure) override;
		std::string getVariateTypeName(Ast::VariateType variateType) override;
		std::string getValueOutput(int32_t value) override;
		std::string getValueOutput(uint32_t value) override;
		std::string getValueOutput(float value) override;
		std::string getValueOutput(double value) override;
		std::string getValueOutput(bool value) override;
		std::string getValueOutput(const ktm::fvec2& value) override;
		std::string getValueOutput(const ktm::fvec3& value) override;
		std::string getValueOutput(const ktm::fvec4& value) override;
		std::string getValueOutput(const ktm::svec2& value) override;
		std::string getValueOutput(const ktm::svec3& value) override;
		std::string getValueOutput(const ktm::svec4& value) override;
		std::string getValueOutput(const ktm::uvec2& value) override;
		std::string getValueOutput(const ktm::uvec3& value) override;
		std::string getValueOutput(const ktm::uvec4& value) override;
		std::string getValueOutput(const ktm::dvec2& value) override;
		std::string getValueOutput(const ktm::dvec3& value) override;
		std::string getValueOutput(const ktm::dvec4& value) override;
		std::string getValueOutput(const ktm::vec<2, bool>& value) override;
		std::string getValueOutput(const ktm::vec<3, bool>& value) override;
		std::string getValueOutput(const ktm::vec<4, bool>& value) override;
		std::string getValueOutput(const ktm::fmat2x2& value) override;
		std::string getValueOutput(const ktm::fmat3x3& value) override;
		std::string getValueOutput(const ktm::fmat4x4& value) override;
		std::string getValueOutput(const ktm::fmat2x3& value) override;
		std::string getValueOutput(const ktm::fmat2x4& value) override;
		std::string getValueOutput(const ktm::fmat3x2& value) override;
		std::string getValueOutput(const ktm::fmat3x4& value) override;
		std::string getValueOutput(const ktm::fmat4x2& value) override;
		std::string getValueOutput(const ktm::fmat4x3& value) override;

		std::string getParseOutput(const Ast::DefineLocalVariate* node) override;
		std::string getParseOutput(const Ast::DefineInputVariate* node) override;
		std::string getParseOutput(const Ast::Assign* node) override;
		std::string getParseOutput(const Ast::BinaryOperator* node) override;
		std::string getParseOutput(const Ast::MemberAccess* node) override;
		std::string getParseOutput(const Ast::DefineOutputVariate* node) override;
		std::string getParseOutput(const Ast::UniformVariate* node) override;
		std::string getParseOutput(const Ast::DefineUniformVariate* node) override;
		std::string getParseOutput(const Ast::IfStatement* node) override;

		std::shared_ptr<Ast::Variate> getPositionOutput() override;
	};
}