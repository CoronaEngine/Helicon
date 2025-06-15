#include <AST/AST.hpp>
#include <utility>
#include <AST/Parser.hpp>

std::shared_ptr<EmbeddedShader::Ast::LocalVariate> EmbeddedShader::Ast::AST::defineLocalVariate(std::shared_ptr<Type> type, std::shared_ptr<Value> initValue)
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

std::shared_ptr<EmbeddedShader::Ast::Value> EmbeddedShader::Ast::AST::binaryOperator(std::shared_ptr<Value> value1, std::shared_ptr<Value> value2, std::string operatorType)
{
	auto binaryOp = std::make_shared<BinaryOperator>();
	binaryOp->value1 = std::move(value1);
	binaryOp->value2 = std::move(value2);
	binaryOp->type = std::move(operatorType);
	return binaryOp; // 这里需要实现具体的操作符逻辑
}

void EmbeddedShader::Ast::AST::assign(std::shared_ptr<Value> variate, std::shared_ptr<Value> value)
{
	auto assignNode = std::make_shared<Assign>();
	assignNode->leftValue = std::move(variate);
	assignNode->rightValue = std::move(value);
	addStatement(assignNode);
}

std::shared_ptr<EmbeddedShader::Ast::InputVariate> EmbeddedShader::Ast::AST::defineInputVariate(std::shared_ptr<Type> type)
{
	auto inputVariate = std::make_shared<InputVariate>();
	inputVariate->type = std::move(type);
	inputVariate->name = Parser::getUniqueVariateName();
	inputVariate->index = Parser::currentParser->currentInputVariateIndex++;
	auto defineNode = std::make_shared<DefineInputVariate>();
	defineNode->variate = inputVariate;
	addGlobalStatement(defineNode);
	return inputVariate;
}

std::shared_ptr<EmbeddedShader::Ast::MemberAccess> EmbeddedShader::Ast::AST::access(std::shared_ptr<Value> value,
	std::string memberName) {
	auto memberAccess = std::make_shared<MemberAccess>();
	memberAccess->value = std::move(value);
	memberAccess->memberName = std::move(memberName);
	return memberAccess;
}

std::shared_ptr<EmbeddedShader::Ast::Variate> EmbeddedShader::Ast::AST::getPositionOutput()
{
	//不会出现currentParser == nullptr这种情况
	auto& posOutput = Parser::currentParser->positionOutput;
	if (posOutput)
		return posOutput;
	posOutput = std::make_shared<Variate>();
	posOutput->name = "gl_Position";
	posOutput->type = VecType::createVecType(variateTypeToEnum<ktm::fvec4>);
	return posOutput;
}

void EmbeddedShader::Ast::AST::addStatement(std::shared_ptr<Statement> statement)
{
	//不会出现currentParser == nullptr这种情况
	Parser::currentParser->structure.statements.push_back(std::move(statement));
}

void EmbeddedShader::Ast::AST::addGlobalStatement(std::shared_ptr<Statement> globalStatement)
{
	//不会出现currentParser == nullptr这种情况
	Parser::currentParser->structure.globalStatements.push_back(std::move(globalStatement));
}
