#include <Codegen/AST/Parser.hpp>
#include <Codegen/Generator/SlangGenerator.hpp>
std::string EmbeddedShader::Generator::SlangGenerator::getShaderOutput(const Ast::EmbeddedShaderStructure& structure)
{
	std::string output;

	for (auto& statement: structure.globalStatements)
	{
		output += statement->parse() + '\n';
	}

	for (auto& statement: structure.shaderOnlyStatements)
	{
		output += statement->parse() + '\n';
	}

	std::string mainContent;
	for (auto& statement: structure.localStatements)
	{
		mainContent += statement->parse() + '\n';
	}

	// std::string entrypoint;
	// std::string outputStruct;
	// std::string outputStructName;
	// {
	// 	std::string stageType = "unknown";
	// 	switch (structure.stage)
	// 	{
	// 		case Ast::ShaderStage::Vertex:
	// 			stageType = "vertex";
	// 			break;
	// 		case Ast::ShaderStage::Fragment:
	// 			stageType = "fragment";
	// 			break;
	// 	}
	//
	// 	outputStructName = stageType + "_output";
	//
	// 	entrypoint = "[shader(\"" + stageType + "\")]\n";
	// 	entrypoint += outputStructName + " main(";
	// }

	return output;
}

std::string EmbeddedShader::Generator::SlangGenerator::getParseOutput(const Ast::DefineLocalVariate* node)
{
	return node->localVariate->type->parse() + " " + node->localVariate->name +
		(node->value ? " = " + node->value->parse() : "") + ";";
}

std::string EmbeddedShader::Generator::SlangGenerator::getParseOutput(const Ast::DefineInputVariate* node)
{
	//这段内容应放在Generator生成的input struct中
	return node->variate->type->parse() + " " + node->variate->name + " : LOCATION" + std::to_string(node->variate->location) + ";";
}

std::string EmbeddedShader::Generator::SlangGenerator::getParseOutput(const Ast::Assign* node)
{
	return node->leftValue->parse() + " = " + node->rightValue->parse() + ";";
}

std::string EmbeddedShader::Generator::SlangGenerator::getParseOutput(const Ast::BinaryOperator* node)
{
	return node->value1->parse() + " " + node->type + " " + node->value2->parse() + ";";
}

std::string EmbeddedShader::Generator::SlangGenerator::getParseOutput(const Ast::MemberAccess* node)
{
	return node->value->parse() + "." + node->memberName + ";";
}

std::string EmbeddedShader::Generator::SlangGenerator::getParseOutput(const Ast::DefineOutputVariate* node)
{
	return node->variate->type->parse() + " " + node->variate->name + " : LOCATION" + std::to_string(node->variate->location) + ";";
}

std::string EmbeddedShader::Generator::SlangGenerator::getParseOutput(const Ast::IfStatement* node)
{
	auto result = "if (" + node->condition->parse() + ") {\n";
	nestHierarchy++;
	for (auto& statement: node->statements)
	{
		result += getCodeIndentation() + statement->parse() + "\n";
	}
	nestHierarchy--;
	result += getCodeIndentation() + "}";
	return result;
}

std::shared_ptr<EmbeddedShader::Ast::Variate> EmbeddedShader::Generator::SlangGenerator::getPositionOutput()
{
	//思考Slang的语义问题，先这样写，后续修改

	auto positionOutput = std::make_shared<Ast::OutputVariate>();
	positionOutput->type = Ast::VecType::createVecType(Ast::VariateType::Vec4); //后续接入Slang Generator的type mapping之后这里需要修改
	positionOutput->name = "position_output";
	positionOutput->location = 0;
	return positionOutput;
}

std::string EmbeddedShader::Generator::SlangGenerator::getCodeIndentation()
{
	//ide可能会误报warning
	return std::string(nestHierarchy, '\t');
}
