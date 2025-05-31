#include <AST/Node.hpp>
#include <AST/Parser.hpp>

void EmbeddedShader::AST::Node::addNode(std::shared_ptr<Statement> node)
{
	//不会出现currentParser == nullptr这种情况
	Parser::currentParser->nodes.push_back(std::move(node));
}

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

std::string EmbeddedShader::AST::LocalVariate::parse()
{
	auto result = type->parse() + " " + Parser::getUniqueVariateName();
	if (value)
		result += " = " + value->parse();
	result += ";";
	return result;
}
