#include <AST/Node.hpp>
#include <AST/Parser.hpp>

void EmbeddedShader::AST::Node::addNode(std::shared_ptr<Node> node)
{
	Parser::currentParser->nodes.push_back(std::move(node));
}
