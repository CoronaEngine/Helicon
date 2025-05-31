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
	for (auto& node: nodes)
	{
		 output += node->parse() + '\n';
	}
	return output;
}

std::string EmbeddedShader::AST::Parser::getUniqueVariateName()
{
	return "var_" + std::to_string(currentParser->currentVariateIndex++);
}
