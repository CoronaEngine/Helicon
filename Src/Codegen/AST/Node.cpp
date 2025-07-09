#include "Node.hpp"

#include <Codegen/Generator/SlangGenerator.hpp>

#include "Parser.hpp"

std::string EmbeddedShader::Ast::Node::parse()
{
	return "";
}

std::string EmbeddedShader::Ast::NameType::parse()
{
	return name;
}

void EmbeddedShader::Ast::Value::access(AccessPermissions permissions) {}

std::string EmbeddedShader::Ast::Variate::parse()
{
	return name;
}

std::string EmbeddedShader::Ast::BasicValue::parse()
{
	return value;
}

std::string EmbeddedShader::Ast::VecValue::parse()
{
	return value;
}

std::string EmbeddedShader::Ast::DefineLocalVariate::parse()
{
	return Generator::SlangGenerator::getParseOutput(this);
}

std::string EmbeddedShader::Ast::BinaryOperator::parse()
{
	return Generator::SlangGenerator::getParseOutput(this);
}

std::string EmbeddedShader::Ast::Assign::parse()
{
	return Generator::SlangGenerator::getParseOutput(this);
}

std::string EmbeddedShader::Ast::InputVariate::parse()
{
	return Generator::SlangGenerator::getParseOutput(this);
}

std::string EmbeddedShader::Ast::DefineInputVariate::parse()
{
	return Generator::SlangGenerator::getParseOutput(this);
}

std::string EmbeddedShader::Ast::MemberAccess::parse()
{
	return Generator::SlangGenerator::getParseOutput(this);
}

void EmbeddedShader::Ast::MemberAccess::access(AccessPermissions permissions)
{
	value->access(permissions);
}

std::string EmbeddedShader::Ast::OutputVariate::parse()
{
	return Generator::SlangGenerator::getParseOutput(this);
}

std::string EmbeddedShader::Ast::DefineOutputVariate::parse()
{
	return Generator::SlangGenerator::getParseOutput(this);
}

std::string EmbeddedShader::Ast::IfStatement::parse()
{
	return Generator::SlangGenerator::getParseOutput(this);
}

std::string EmbeddedShader::Ast::UniversalVariate::parse()
{
	return Variate::parse();
}

void EmbeddedShader::Ast::UniversalVariate::access(AccessPermissions permissions)
{
	this->permissions = this->permissions | permissions;
}

std::string EmbeddedShader::Ast::DefineUniversalVariate::parse()
{
	return Statement::parse();
}
