#include <AST/Parser.hpp>
#include <utility>

std::string EmbeddedShader::AST::Parser::parse(const std::function<void()>& shaderCode)
{
	currentParser = new Parser();
	shaderCode();
	std::string output = currentParser->getOutput();
	delete currentParser;
	currentParser = nullptr;
	return output;
}

std::string EmbeddedShader::AST::Parser::getOutput()
{
	return "Parsed Shader Code";
}
