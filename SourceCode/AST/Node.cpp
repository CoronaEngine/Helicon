#include <AST/Node.hpp>
#include <AST/Parser.hpp>

std::string EmbeddedShader::AST::Node::parse()
{
	return "";
}

std::string EmbeddedShader::AST::NameType::parse()
{
	return name;
}

std::string EmbeddedShader::AST::Variate::parse()
{
	return name;
}

std::string EmbeddedShader::AST::BaseValue::parse()
{
	return value;
}

std::string EmbeddedShader::AST::VecValue::parse()
{
	return type->parse() + "(" + value + ")";
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
	return leftValue->parse() + " = " + rightValue->parse() + ";";
}

std::string EmbeddedShader::AST::DefineInputVariate::parse()
{
	return "layout(location = " + std::to_string(localVariate->index) + ") in " + localVariate->type->parse() + " " + localVariate->name + ";";
}

std::string EmbeddedShader::AST::MemberAccess::parse() {
	return value->parse() + "." + memberName;
}
