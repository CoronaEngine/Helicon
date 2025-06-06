#include <AST/Parser.hpp>
#include <utility>
#include <AST/Node.hpp>

std::string EmbeddedShader::AST::Parser::parse(const std::function<void()>& shaderCode)
{
	currentParser = new Parser();
	shaderCode();
	std::string output = currentParser->getOutput();
	delete currentParser;
	currentParser = nullptr;
	return output;
}

std::string EmbeddedShader::AST::Parser::getOutput() const
{
	std::string output;
	output += "#version 330 core\n";

	//global statements
	for (auto& node: globalStatements)
	{
		output += node->parse() + '\n';
	}

	output += "void main() {\n";
	for (auto& node: statements)
	{
		 output += '\t' + node->parse() + '\n';
	}
	output += "}\n";
	return output;
}

std::string EmbeddedShader::AST::Parser::getUniqueVariateName()
{
	return "var_" + std::to_string(currentParser->currentVariateIndex++);
}
