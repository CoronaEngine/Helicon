#include <AST/Node.hpp>
#include <AST/Parser.hpp>

std::string EmbeddedShader::AST::Node::parse()
{
	return "";
}

std::string EmbeddedShader::AST::LocalVariate::parse()
{
	return name;
}

std::string EmbeddedShader::AST::NumericType::parse()
{
	return name;
}

std::string EmbeddedShader::AST::NumericValue::parse()
{
	return value;
}

std::string EmbeddedShader::AST::DefineLocalVariate::parse()
{
	auto result = localVariate->type->parse() + " " + localVariate->name;
	if (value)
		result += " = " + value->parse();
	result += ";";
	return result;
}

std::string EmbeddedShader::AST::BinaryOperator::parse()
{
	return "(" + value1->parse() + " " + type + " " + value2->parse() + ")";
}

std::string EmbeddedShader::AST::Assign::parse()
{
	return variate->name + " = " + value->parse() + ";";
}
