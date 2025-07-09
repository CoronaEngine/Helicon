#include <Codegen/AST/AST.hpp>
#include <Codegen/AST/Parser.hpp>
#include <Codegen/Generator/SlangGenerator.hpp>
std::string EmbeddedShader::Generator::SlangGenerator::getShaderOutput(const Ast::EmbeddedShaderStructure& structure)
{
	currentStage = structure.stage;
	std::string output;

	for (auto& statement: structure.globalStatements)
	{
		output += statement->parse() + '\n';
	}

	std::string mainContent;
	for (auto& statement: structure.localStatements)
	{
		mainContent += "\t" + statement->parse() + '\n';
	}

	std::string stageType = "unknown";
	switch (structure.stage)
	{
		case Ast::ShaderStage::Vertex:
			stageType = "vertex";
			break;
		case Ast::ShaderStage::Fragment:
			stageType = "fragment";
			break;
	}

	std::string outputStructName = "void";
	std::string inputStructName;

	if (!structure.inputStatements.empty())
	{
		inputStructName = stageType + "_input";
		std::string inputStruct = "struct " + inputStructName +" {\n";
		for (auto& statement: structure.inputStatements)
		{
			inputStruct += "\t" + statement->parse() + '\n';
		}
		inputStruct += "}\n";
		output += inputStruct;
	}

	if (!structure.outputStatements.empty())
	{
		outputStructName = stageType + "_output";
		std::string outputStruct = "struct " + outputStructName +" {\n";
		for (auto& statement: structure.outputStatements)
		{
			outputStruct += "\t" + statement->parse() + '\n';
		}
		outputStruct += "}\n";
		output += outputStruct;
	}

	std::string entrypoint = "[shader(\"" + stageType + "\")]\n";
	entrypoint += outputStructName + " main(";
	if (!structure.inputStatements.empty())
		entrypoint += inputStructName + " input";
	entrypoint += ") {\n";
	if (!structure.outputStatements.empty())
		entrypoint += "\t" + outputStructName + " output;\n";
	entrypoint += mainContent;
	if (!structure.outputStatements.empty())
		entrypoint += "\treturn output;\n";
	entrypoint += "}\n";

	output += entrypoint;

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
	if (currentStage != Ast::ShaderStage::Fragment)
		return node->variate->type->parse() + " " + node->variate->name + " : LOCATION" + std::to_string(node->variate->location) + ";";
	return node->variate->type->parse() + " " + node->variate->name + " : SV_TARGET" + std::to_string(node->variate->location) + ";";
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

std::string EmbeddedShader::Generator::SlangGenerator::getParseOutput(const Ast::InputVariate* node)
{
	return "input." + node->name;
}

std::string EmbeddedShader::Generator::SlangGenerator::getParseOutput(const Ast::OutputVariate* node)
{
	return "output." + node->name;
}

std::shared_ptr<EmbeddedShader::Ast::Variate> EmbeddedShader::Generator::SlangGenerator::getPositionOutput()
{
	auto positionOutput = std::make_shared<Ast::OutputVariate>();
	positionOutput->type = Ast::AST::createVecType<ktm::fvec4>();
	positionOutput->name = "position_output";
	positionOutput->location = 0;
	auto defineNode = std::make_shared<DefineSystemSemanticVariate>();
	defineNode->variate = positionOutput;
	defineNode->semanticName = "SV_POSITION";
	Ast::AST::addOutputStatement(defineNode);
	return positionOutput;
}

std::string EmbeddedShader::Generator::SlangGenerator::getCodeIndentation()
{
	//ide可能会误报warning
	return std::string(nestHierarchy, '\t');
}

std::string EmbeddedShader::Generator::DefineSystemSemanticVariate::parse()
{
	return variate->type->parse() + " " + variate->name + " : " + semanticName + ";";
}
