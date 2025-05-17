#pragma once

#include<vector>
#include<memory>
#include<string>
#include<functional>
#include<unordered_set>
#include<iostream>
struct AstNode
{
public:
	static uint32_t defineTimes;

	enum AstNodeType
	{
		VARIATE_DEFINE,   //

		STRUCT_DEFINE,  //
		STRUCT_ELEMENT, //

		ARRAY_DEFINE,
		ARRAY_ELEMENT, //

		LITER_EXPRESSION,

		VARIATE_OPERATOR,

		UNKNOWN
	};
	AstNodeType astNodeType = LITER_EXPRESSION;

	AstNode* leftNode = nullptr;
	AstNode* rightNode = nullptr;
	AstNode* faRootNode = nullptr; //找上一级节点 而不是父亲节点
	uint32_t arraySize = 0;
	bool inited = false;

	AstNode()
	{
		
	}

	AstNode(std::string variateName, std::string typeName, AstNodeType astNodeType, uint32_t arraySize = 0)
	{
		this->variateName = variateName;
		this->typeName = typeName;
		this->astNodeType = astNodeType;
		this->arraySize = arraySize;
	}

	AstNode(std::string literalString, AstNodeType astNodeType)
	{
		this->literalString = literalString;
		this->astNodeType = astNodeType;
	}

	std::string getVariateName(bool inStatement = false)
	{
		return inStatement && astNodeType == AstNode::ARRAY_DEFINE ? this->variateName + "[" + std::to_string(arraySize) + "]" : this->variateName;
	}

	std::string getTypeName()
	{
		return this->typeName;
	}

	AstNodeType getAstNodeType()
	{
		return this->astNodeType;
	}

	void setVariateName(std::string variateName)
	{
		this->variateName = variateName;
	}

	void setTypeName()
	{
		this->typeName = typeName;
	}

	AstNode(AstNode* astNode)//仅拷贝当前节点
	{
		this->astNodeType = astNode->astNodeType;
		this->arraySize = astNode->arraySize;
		this->variateName = astNode->variateName;
		this->typeName = astNode->typeName;
		this->literalString = astNode->literalString;
	}

public:
	std::string variateName;
	std::string typeName;
	std::string literalString;
};

class AbstractSyntaxTree
{
private:
	
	std::vector<AstNode*> stmts, globalDefinations;
	std::unordered_set<std::string> statedStructSet;
	int structDefineTimes = 0;
	bool inGlobalRegion = true;

public:

	AstNode* dfsCopyAstTree(AstNode* astNode)
	{
		if(astNode == nullptr)
		{
			return nullptr;
		}
		AstNode* rootNode = new AstNode(astNode);
		rootNode->leftNode = dfsCopyAstTree(astNode->leftNode);
		rootNode->rightNode = dfsCopyAstTree(astNode->rightNode);
		return rootNode;
	}

	void addAstStmts(AstNode* astNode)
	{
		//节点拷贝 不走直接拿节点 否则释放后出错 并且存在较大的依赖问题
		AstNode* rootNode = dfsCopyAstTree(astNode);
		stmts.emplace_back(rootNode);
	}
	
	//针对结构体定义的转译
	std::string parseStructStatement(AstNode* astNode)
	{
		std::string structDefineStr = astNode->getTypeName() + "{\n";

		for(astNode = astNode->leftNode; astNode != nullptr; astNode = astNode->leftNode)
		{
			AstNode* variateAstNode = astNode->rightNode;
			switch(variateAstNode->getAstNodeType())
			{
				case AstNode::AstNodeType::VARIATE_DEFINE:
					// structDefineStr = structDefineStr + "	" + variateAstNode->getTypeName() + " " + variateAstNode->getVariateName() + ";\n";
					// break;
				case AstNode::AstNodeType::ARRAY_DEFINE:
					structDefineStr = structDefineStr + "	" + parseStmt(variateAstNode);
					break;
				case AstNode::AstNodeType::STRUCT_DEFINE: 
					break;

			}
		}
		return structDefineStr + "};\n";
	}

	std::string parseStmt(AstNode* astNode)
	{
		std::string leftExpression = "", rightExpression = "", structTypeName = "";
		switch (astNode->astNodeType)
		{
			case AstNode::AstNodeType::VARIATE_DEFINE:
				leftExpression = astNode->getTypeName() + " " + astNode->getVariateName();
				rightExpression = parseExpression(astNode->rightNode, true);
				return leftExpression + (rightExpression == "" ? "" : "=" + rightExpression) + ";\n";
			case AstNode::AstNodeType::STRUCT_DEFINE:
				//结构体没有声明过
				structTypeName = astNode->getTypeName();

				if(statedStructSet.find(structTypeName) == statedStructSet.end())
				{
					statedStructSet.insert(structTypeName);
					leftExpression = leftExpression + parseStructStatement(astNode) + ";\n";
				}
				leftExpression =  leftExpression + astNode->getTypeName() + " " + astNode->getVariateName();
				rightExpression = parseExpression(astNode->leftNode, true);
				return leftExpression + (rightExpression == "" ? "" : "=" + rightExpression) + ";\n";
			case AstNode::AstNodeType::ARRAY_DEFINE:
				leftExpression = astNode->getTypeName() + " " + astNode->getVariateName();
				rightExpression = parseExpression(astNode->leftNode, true);
				if(rightExpression != "")
				{
					rightExpression = "= {" + rightExpression.substr(0, rightExpression.size() - 1) + "};";
				}
				return leftExpression + rightExpression + "\n";
			case AstNode::AstNodeType::VARIATE_OPERATOR:
				return astNode->leftNode->getVariateName() + astNode->literalString + parseExpression(astNode->rightNode) + ";\n";
		}
		return "";
	}

	std::string parseExpression(AstNode* astNode, bool inDefination=true)
	{
		if (astNode == nullptr)
		{
			return "";
		}

		std::string expressionStr = "";

		switch (astNode->astNodeType)
		{
			case AstNode::AstNodeType::VARIATE_DEFINE:
			case AstNode::AstNodeType::STRUCT_DEFINE:
			case AstNode::AstNodeType::ARRAY_DEFINE:
				return astNode->getVariateName();
			case AstNode::AstNodeType::ARRAY_ELEMENT:
				expressionStr = astNode->rightNode->getVariateName() + "," + parseExpression(astNode->leftNode, inDefination);
				break;
			case AstNode::AstNodeType::VARIATE_OPERATOR:
				expressionStr = "(" + parseExpression(astNode->leftNode, inDefination) + astNode->literalString + parseExpression(astNode->rightNode, inDefination) + ")";
				break;
			case AstNode::AstNodeType::LITER_EXPRESSION:
				expressionStr = astNode->getVariateName();
				break;
		}
		return expressionStr;
	}

	std::string parseStructDefination(AstNode* astNode, std::string& codeStr)
	{
		while (AstNode* structChildNode = astNode->leftNode)
		{
			switch (structChildNode->astNodeType)
			{
				
			}
		}
	}

	std::string parseArrayDefination()
	{
		return "";
	}

	std::string parse(std::function<void()> func)
	{
		std::string dslResult = "";
		stmts.clear();
		inGlobalRegion = false;
		func();

		//全局变量
		for(AstNode* astNode : globalDefinations)
		{
			dslResult += parseStmt(astNode);
		}

		for(AstNode* astNode : stmts)
		{
			dslResult += parseStmt(astNode);
		}
		
		inGlobalRegion = true;
		return dslResult;
	}
	
};

extern AbstractSyntaxTree abstractSyntaxTree;