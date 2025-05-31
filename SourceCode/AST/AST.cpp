#include <AST/AST.hpp>

std::shared_ptr<EmbeddedShader::AST::Value> EmbeddedShader::AST::AST::addOperator(std::shared_ptr<Value> value1, std::shared_ptr<Value> value2)
{
	return nullptr; // 这里需要实现具体的操作符逻辑
}

void EmbeddedShader::AST::AST::addStatement(std::shared_ptr<Statement> statement)
{
	//不会出现currentParser == nullptr这种情况
	Parser::currentParser->statements.push_back(std::move(statement));
}
