#include <AST/AST.hpp>
#include <utility>

std::shared_ptr<EmbeddedShader::AST::LocalVariate> EmbeddedShader::AST::AST::defineLocalVariate(std::shared_ptr<Type> type, std::shared_ptr<Value> initValue)
{
	auto localVariate = std::make_shared<LocalVariate>();
	localVariate->name = Parser::getUniqueVariateName();
	localVariate->type = std::move(type);
	auto defineNode = std::make_shared<DefineLocalVariate>();
	defineNode->localVariate = localVariate;
	defineNode->value = std::move(initValue);
	addStatement(defineNode);
	return localVariate;
}

std::shared_ptr<EmbeddedShader::AST::Value> EmbeddedShader::AST::AST::binaryOperator(std::shared_ptr<Value> value1, std::shared_ptr<Value> value2, std::string operatorType)
{
	auto binaryOp = std::make_shared<BinaryOperator>();
	binaryOp->value1 = std::move(value1);
	binaryOp->value2 = std::move(value2);
	binaryOp->type = std::move(operatorType);
	return binaryOp; // 这里需要实现具体的操作符逻辑
}

void EmbeddedShader::AST::AST::assign(std::shared_ptr<LocalVariate> variate, std::shared_ptr<Value> value)
{
	auto assignNode = std::make_shared<Assign>();
	assignNode->variate = std::move(variate);
	assignNode->value = std::move(value);
	addStatement(assignNode);
}

void EmbeddedShader::AST::AST::addStatement(std::shared_ptr<Statement> statement)
{
	//不会出现currentParser == nullptr这种情况
	Parser::currentParser->statements.push_back(std::move(statement));
}
