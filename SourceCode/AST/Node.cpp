#include <AST/Node.hpp>
#include <AST/Parser.hpp>

std::string EmbeddedShader::AST::Node::parse()
{
	return "";
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
	auto result = type->parse() + " " + localVariate->name;
	if (value)
		result += " = " + value->parse();
	result += ";";
	return result;
}
