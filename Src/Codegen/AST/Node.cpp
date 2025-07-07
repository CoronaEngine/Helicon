#include "Node.hpp"
#include "Parser.hpp"

std::string EmbeddedShader::Ast::Node::parse()
{
	return "";
}

std::string EmbeddedShader::Ast::NameType::parse()
{
	return name;
}

std::string EmbeddedShader::Ast::Variate::parse()
{
	return name;
}

std::shared_ptr<EmbeddedShader::Ast::VecType> EmbeddedShader::Ast::VecType::createVecType(VariateType type)
{
	auto vecType = std::make_shared<VecType>();
	vecType->name = Parser::getShaderGenerator()->getVariateTypeName(type);
	return vecType;
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
	return  Parser::getShaderGenerator()->getParseOutput(this);
}

std::string EmbeddedShader::Ast::BinaryOperator::parse()
{
	return Parser::getShaderGenerator()->getParseOutput(this);
}

std::string EmbeddedShader::Ast::Assign::parse()
{
	return Parser::getShaderGenerator()->getParseOutput(this);
}

std::string EmbeddedShader::Ast::DefineInputVariate::parse()
{
	return Parser::getShaderGenerator()->getParseOutput(this);
}

std::string EmbeddedShader::Ast::MemberAccess::parse()
{
	return Parser::getShaderGenerator()->getParseOutput(this);
}

std::string EmbeddedShader::Ast::DefineOutputVariate::parse()
{
	return Parser::getShaderGenerator()->getParseOutput(this);
}

std::string EmbeddedShader::Ast::UniformVariate::parse()
{
	return Parser::getShaderGenerator()->getParseOutput(this);
}

std::string EmbeddedShader::Ast::DefineUniformVariate::parse()
{
	return Parser::getShaderGenerator()->getParseOutput(this);
}

std::string EmbeddedShader::Ast::IfStatement::parse()
{
	return Parser::getShaderGenerator()->getParseOutput(this);
}

std::string EmbeddedShader::Ast::UniversalVariate::parse()
{
	return Variate::parse();
}

std::string EmbeddedShader::Ast::DefineUniversalVariate::parse()
{
	return Statement::parse();
}
