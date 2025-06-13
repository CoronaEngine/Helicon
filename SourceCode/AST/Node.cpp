#include <AST/Node.hpp>
#include <AST/Parser.hpp>

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

std::string EmbeddedShader::Ast::BaseValue::parse()
{
	return value;
}

std::string EmbeddedShader::Ast::VecValue::parse()
{
	return type->parse() + "(" + value + ")";
}

std::string EmbeddedShader::Ast::DefineLocalVariate::parse()
{
	auto result = localVariate->type->parse() + " " + localVariate->name;
	if (value)
		result += " = " + value->parse();
	result += ";";
	return result;
}

std::string EmbeddedShader::Ast::BinaryOperator::parse()
{
	return "(" + value1->parse() + " " + type + " " + value2->parse() + ")";
}

std::string EmbeddedShader::Ast::Assign::parse()
{
	return leftValue->parse() + " = " + rightValue->parse() + ";";
}

std::string EmbeddedShader::Ast::DefineInputVariate::parse()
{
	return "layout(location = " + std::to_string(variate->index) + ") in " + variate->type->parse() + " " + variate->name + ";";
}

std::string EmbeddedShader::Ast::MemberAccess::parse() {
	return value->parse() + "." + memberName;
}
