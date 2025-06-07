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

std::shared_ptr<EmbeddedShader::AST::InputVariate> EmbeddedShader::AST::AST::defineInputVariate(std::shared_ptr<Type> type)
{
	auto inputVariate = std::make_shared<InputVariate>();
	inputVariate->type = std::move(type);
	inputVariate->name = Parser::getUniqueVariateName();
	inputVariate->index = Parser::currentParser->currentInputVariateIndex++;
	auto defineNode = std::make_shared<DefineInputVariate>();
	defineNode->localVariate = inputVariate;
	addGlobalStatement(defineNode);
	return inputVariate;
}

std::shared_ptr<EmbeddedShader::AST::Variate> EmbeddedShader::AST::AST::getPositionOutput()
{
	//不会出现currentParser == nullptr这种情况
	auto& posOutput = Parser::currentParser->positionOutput;
	if (posOutput)
		return posOutput;
	posOutput = std::make_shared<Variate>();
	posOutput->name = "gl_Position";
	posOutput->type = VecType::createVecType<ktm::fvec4>();
	return posOutput;
}

void EmbeddedShader::AST::AST::addStatement(std::shared_ptr<Statement> statement)
{
	//不会出现currentParser == nullptr这种情况
	Parser::currentParser->statements.push_back(std::move(statement));
}

void EmbeddedShader::AST::AST::addGlobalStatement(std::shared_ptr<Statement> globalStatement)
{
	//不会出现currentParser == nullptr这种情况
	Parser::currentParser->globalStatements.push_back(std::move(globalStatement));
}
