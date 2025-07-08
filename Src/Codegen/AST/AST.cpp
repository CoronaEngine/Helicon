#include "AST.hpp"
#include <utility>
#include "Parser.hpp"

std::shared_ptr<EmbeddedShader::Ast::LocalVariate> EmbeddedShader::Ast::AST::defineLocalVariate(std::shared_ptr<Type> type, std::shared_ptr<Value> initValue)
{
	auto localVariate = std::make_shared<LocalVariate>();
	localVariate->name = Parser::getUniqueVariateName();
	localVariate->type = std::move(type);
	auto defineNode = std::make_shared<DefineLocalVariate>();
	defineNode->localVariate = localVariate;
	defineNode->value = std::move(initValue);
	addLocalStatement(defineNode);
	return localVariate;
}

std::shared_ptr<EmbeddedShader::Ast::Value> EmbeddedShader::Ast::AST::binaryOperator(std::shared_ptr<Value> value1, std::shared_ptr<Value> value2, std::string operatorType)
{
	value1->access(AccessPermissions::ReadOnly);
	value2->access(AccessPermissions::ReadOnly);
	auto binaryOp = std::make_shared<BinaryOperator>();
	binaryOp->value1 = std::move(value1);
	binaryOp->value2 = std::move(value2);
	binaryOp->type = std::move(operatorType);
	return binaryOp; // 这里需要实现具体的操作符逻辑
}

void EmbeddedShader::Ast::AST::assign(std::shared_ptr<Value> variate, std::shared_ptr<Value> value)
{
	variate->access(AccessPermissions::WriteOnly);
	value->access(AccessPermissions::ReadOnly);
	auto assignNode = std::make_shared<Assign>();
	assignNode->leftValue = std::move(variate);
	assignNode->rightValue = std::move(value);
	addLocalStatement(assignNode);
}

std::shared_ptr<EmbeddedShader::Ast::InputVariate> EmbeddedShader::Ast::AST::defineInputVariate(std::shared_ptr<Type> type, size_t location)
{
	auto inputVariate = std::make_shared<InputVariate>();
	inputVariate->type = std::move(type);
	inputVariate->name = Parser::getUniqueVariateName();
	inputVariate->location = location;
	auto defineNode = std::make_shared<DefineInputVariate>();
	defineNode->variate = inputVariate;
	addShaderOnlyStatement(defineNode);
	return inputVariate;
}

std::shared_ptr<EmbeddedShader::Ast::MemberAccess> EmbeddedShader::Ast::AST::access(std::shared_ptr<Value> value,
	std::string memberName) {
	auto memberAccess = std::make_shared<MemberAccess>();
	memberAccess->value = std::move(value);
	memberAccess->memberName = std::move(memberName);
	return memberAccess;
}

std::shared_ptr<EmbeddedShader::Ast::OutputVariate> EmbeddedShader::Ast::AST::defineOutputVariate(std::shared_ptr<Type> type, size_t location)
{
	auto outputVariate = std::make_shared<OutputVariate>();
	outputVariate->type = std::move(type);
	outputVariate->name = Parser::getUniqueVariateName();
	outputVariate->location = location;
	auto defineNode = std::make_shared<DefineOutputVariate>();
	defineNode->variate = outputVariate;
	addShaderOnlyStatement(defineNode);
	return outputVariate;
}

void EmbeddedShader::Ast::AST::beginIf(std::shared_ptr<Value> condition)
{
	auto ifStatement = std::make_shared<IfStatement>();
	ifStatement->condition = std::move(condition);
	addLocalStatement(ifStatement);
	getStatementStack().push(&ifStatement->statements);
}

void EmbeddedShader::Ast::AST::endIf()
{
	getStatementStack().pop();
}

std::shared_ptr<EmbeddedShader::Ast::UniversalVariate> EmbeddedShader::Ast::AST::defineUniversalVariate(std::shared_ptr<Type> type)
{
	auto variate = std::make_shared<UniversalVariate>();
	variate->type = std::move(type);
	variate->name = Parser::getUniqueGlobalVariateName();
	auto defineNode = std::make_shared<DefineUniversalVariate>();
	defineNode->variate = variate;
	addGlobalStatement(defineNode);
	return variate;
}

std::shared_ptr<EmbeddedShader::Ast::Variate> EmbeddedShader::Ast::AST::getPositionOutput()
{
	auto& posOutput = Parser::currentParser->positionOutput;
	if (posOutput)
		return posOutput;
	posOutput = Parser::getShaderGenerator()->getPositionOutput();
	return posOutput;
}

void EmbeddedShader::Ast::AST::addLocalStatement(std::shared_ptr<Statement> statement)
{
	getStatementStack().top()->push_back(std::move(statement));
}

void EmbeddedShader::Ast::AST::addShaderOnlyStatement(std::shared_ptr<Statement> shaderOnlyStatement)
{
	Parser::currentParser->structure.shaderOnlyStatements.push_back(std::move(shaderOnlyStatement));
}

void EmbeddedShader::Ast::AST::addGlobalStatement(std::shared_ptr<Statement> globalStatement)
{
	Parser::currentParser->structure.globalStatements.push_back(std::move(globalStatement));
}

std::stack<std::vector<std::shared_ptr<EmbeddedShader::Ast::Statement>>*>& EmbeddedShader::Ast::AST::getStatementStack()
{
	return Parser::currentParser->statementStack;
}

EmbeddedShader::Ast::EmbeddedShaderStructure& EmbeddedShader::Ast::AST::getEmbeddedShaderStructure()
{
	return Parser::currentParser->structure;
}
