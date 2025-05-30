#include <AST/Parser.hpp>
#include <utility>

EmbeddedShader::AST::Parser::Parser(std::function<void()> shaderCode) : shaderCode(std::move(shaderCode))
{

}
