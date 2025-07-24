#include "AST.hpp"
#include <utility>
#include <Codegen/Generator/SlangGenerator.hpp>

#include "Parser.hpp"

std::shared_ptr<EmbeddedShader::Ast::LocalVariate> EmbeddedShader::Ast::AST::defineLocalVariate(std::shared_ptr<Type> type, std::shared_ptr<Value> initValue)
{
	initValue->access(AccessPermissions::ReadOnly);
	auto localVariate = std::make_shared<LocalVariate>();
	localVariate->name = Parser::getUniqueVariateName();
	localVariate->type = std::move(type);
	auto defineNode = std::make_shared<DefineLocalVariate>();
	defineNode->localVariate = localVariate;
	defineNode->value = std::move(initValue);
	addLocalStatement(defineNode);
	return localVariate;
}

std::shared_ptr<EmbeddedShader::Ast::Value> EmbeddedShader::Ast::AST::binaryOperator(std::shared_ptr<Value> value1, std::shared_ptr<Value> value2,
	std::string operatorType,std::shared_ptr<Type> type)
{
	value1->access(AccessPermissions::ReadOnly);
	value2->access(AccessPermissions::ReadOnly);
	auto binaryOp = std::make_shared<BinaryOperator>();
	binaryOp->value1 = std::move(value1);
	binaryOp->value2 = std::move(value2);
	binaryOp->operatorType = std::move(operatorType);
	binaryOp->type = type? std::move(type) : binaryOp->value1->type;
	return binaryOp; // 这里需要实现具体的操作符逻辑
}

std::shared_ptr<EmbeddedShader::Ast::Value> EmbeddedShader::Ast::AST::unaryOperator(std::shared_ptr<Value> value,
	std::string operatorType, bool isPrefix, AccessPermissions accessPermissions)
{
	value->access(accessPermissions);
	auto unaryOp = std::make_shared<UnaryOperator>();
	unaryOp->value = std::move(value);
	unaryOp->operatorType = std::move(operatorType);
	unaryOp->isPrefix = isPrefix;
	unaryOp->type = unaryOp->value->type;
	return unaryOp;
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
	addInputStatement(defineNode);
	return inputVariate;
}

std::shared_ptr<EmbeddedShader::Ast::MemberAccess> EmbeddedShader::Ast::AST::access(std::shared_ptr<Value> value,
                                                                                    std::string memberName, std::shared_ptr<Type> memberType) {
	auto memberAccess = std::make_shared<MemberAccess>();
	memberAccess->value = std::move(value);
	memberAccess->memberName = std::move(memberName);
    memberAccess->type = std::move(memberType);
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
	addOutputStatement(defineNode);
	return outputVariate;
}

void EmbeddedShader::Ast::AST::beginIf(std::shared_ptr<Value> condition)
{
	auto ifStatement = std::make_shared<IfStatement>();
	ifStatement->condition = std::move(condition);
	addLocalStatement(ifStatement);
	getLocalStatementStack().push(&ifStatement->statements);
}

void EmbeddedShader::Ast::AST::endIf()
{
	getLocalStatementStack().pop();
}

void EmbeddedShader::Ast::AST::beginElse()
{
	auto elseStatement = std::make_shared<ElseStatement>();
	addLocalStatement(elseStatement);
	getLocalStatementStack().push(&elseStatement->statements);
}

void EmbeddedShader::Ast::AST::endElse()
{
	getLocalStatementStack().pop();
}

std::shared_ptr<EmbeddedShader::Ast::UniversalArray> EmbeddedShader::Ast::AST::defineUniversalArray(std::shared_ptr<Type> elementType)
{
	auto variate = std::make_shared<UniversalArray>();
	variate->type = std::move(elementType);
	variate->name = Parser::getUniqueGlobalVariateName();
	auto defineNode = std::make_shared<DefineUniversalArray>();
	defineNode->array = variate;
	addGlobalStatement(defineNode);
	return variate;
}

std::shared_ptr<EmbeddedShader::Ast::UniversalTexture2D> EmbeddedShader::Ast::AST::defineUniversalTexture2D(std::shared_ptr<Type> elementType)
{
    auto variate = std::make_shared<UniversalTexture2D>();
    variate->type = std::move(elementType);
    variate->name = Parser::getUniqueGlobalVariateName();
    auto defineNode = std::make_shared<DefineUniversalTexture2D>();
    defineNode->texture = variate;
    addGlobalStatement(defineNode);
    return variate;
}

std::shared_ptr<EmbeddedShader::Ast::UniformVariate> EmbeddedShader::Ast::AST::defineUniformVariate(
	std::shared_ptr<Type> type, bool pushConstant)
{
	auto variate = std::make_shared<UniformVariate>();
	variate->type = std::move(type);
	variate->name = Parser::getUniqueGlobalVariateName();
	variate->pushConstant = pushConstant;
	auto defineNode = std::make_shared<DefineUniformVariate>();
	defineNode->variate = variate;
	addGlobalStatement(defineNode);
	return variate;
}

std::shared_ptr<EmbeddedShader::Ast::Variate> EmbeddedShader::Ast::AST::getPositionOutput()
{
	auto& posOutput = Parser::currentParser->positionOutput;
	if (posOutput)
		return posOutput;
	posOutput = Generator::SlangGenerator::getPositionOutput();
	return posOutput;
}

std::shared_ptr<EmbeddedShader::Ast::ElementVariate> EmbeddedShader::Ast::AST::at(
	std::shared_ptr<Variate> array, uint32_t index)
{
	auto variate = std::make_shared<ElementVariate>();
	variate->type = array->type;
	variate->name = array->name + "[" + std::to_string(index) + "]";
	variate->array = std::move(array);
	return variate;
}

std::shared_ptr<EmbeddedShader::Ast::ElementVariate> EmbeddedShader::Ast::AST::at(std::shared_ptr<Variate> array,
	const std::shared_ptr<Value>& index)
{
	auto variate = std::make_shared<ElementVariate>();
	variate->type = array->type;
	variate->name = array->name + "[" + index->parse() + "]";
	variate->array = std::move(array);
	return variate;
}

void EmbeddedShader::Ast::AST::addLocalUniversalStatement(
	std::shared_ptr<Node> node)
{
	auto universalStatement = std::make_shared<UniversalStatement>();
	universalStatement->node = std::move(node);
	addLocalStatement(universalStatement);
}

void EmbeddedShader::Ast::AST::addLocalStatement(std::shared_ptr<Statement> statement)
{
	getLocalStatementStack().top()->push_back(std::move(statement));
}

void EmbeddedShader::Ast::AST::addInputStatement(std::shared_ptr<Statement> inputStatement)
{
	Parser::currentParser->structure.inputStatements.push_back(std::move(inputStatement));
}

void EmbeddedShader::Ast::AST::addOutputStatement(std::shared_ptr<Statement> outputStatement)
{
	Parser::currentParser->structure.outputStatements.push_back(std::move(outputStatement));
}

void EmbeddedShader::Ast::AST::addGlobalStatement(std::shared_ptr<Statement> globalStatement)
{
	Parser::currentParser->structure.globalStatements.push_back(std::move(globalStatement));
}

std::stack<std::vector<std::shared_ptr<EmbeddedShader::Ast::Statement>>*>& EmbeddedShader::Ast::AST::getLocalStatementStack()
{
	return Parser::currentParser->localStatementStack;
}

EmbeddedShader::Ast::EmbeddedShaderStructure& EmbeddedShader::Ast::AST::getEmbeddedShaderStructure()
{
	return Parser::currentParser->structure;
}
