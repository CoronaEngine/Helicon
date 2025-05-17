#pragma once

#include "AbstractSyntaxTree.h"

#include "boost/pfr.hpp"
#include <sstream>
#include <regex>
#include <type_traits>
#include <cassert>
#include <unordered_map>
#include <string>
#include <tuple>
#include <ktm/ktm.h>
#include <ktm/type/vec.h>
// KTM类型名存储

//复合类型的元素类型萃取
template<typename T>
struct BasicType {
	using BaseType = T;
};

template<typename T, std::size_t N>
struct BasicType<T[N]> {
	using BaseType = typename BasicType<T>::BaseType;
};

template<typename T, std::size_t N>
struct BasicType<ktm::vec<N, T>> {
	using BaseType = T;
};

// ktm中复合结构的名称对应到DSL下的名称
extern std::unordered_map<std::string, std::string> ktm_class_mapping;

// 常规变量以及KTM库中的变量
template<typename T>
concept is_mathematical = requires(T a)
{
	a = a + a;
	a = a - a;
};

template<typename Type>
struct VariateProxy //AstNode left(children_element) root(define) right(variableExpression)
{
public:

	using ElementType = typename BasicType<Type>::BaseType;

	VariateProxy() requires (std::is_class<Type>::value&& std::is_aggregate<Type>::value && !is_mathematical<Type>) : elementCount(1)
	{
		
		// Ast节点设置
		std::string thisVariableName = "var_" + std::to_string(AstNode::defineTimes++);
		astNode = new AstNode(
			thisVariableName, typeid(Type).name(),
			is_mathematical<Type> ? AstNode::AstNodeType::VARIATE_DEFINE : std::is_array<Type>::value ?
			AstNode::AstNodeType::ARRAY_DEFINE : !is_mathematical<Type> ?
			AstNode::AstNodeType::STRUCT_DEFINE : AstNode::AstNodeType::UNKNOWN);

		
		// 数据拷贝
		Type defultValue;
		dataValuePointer = (Type*)malloc(sizeof(Type));
		memcpy(this->dataValuePointer, &defultValue, sizeof(Type));

		// 如果是结构体
		if (astNode->getAstNodeType() == AstNode::AstNodeType::STRUCT_DEFINE)
		{
			AstNode* pAstNode = astNode;
			// 构建结构体的Ast表达树
			auto lammdaReflect = [&](auto& structMember)
			{
				// 结构体的调用一定在里面内置类型的调用之后
				std::string structMemberName = thisVariableName + "." + structMember.getAstNode()->getVariateName();
				std::string structMemberType = structMember.getAstNode()->getTypeName();
				pAstNode->leftNode = new AstNode(structMemberName, structMemberType, AstNode::AstNodeType::STRUCT_ELEMENT);
				pAstNode = pAstNode->leftNode;
				pAstNode->faRootNode = astNode;

				pAstNode->rightNode = structMember.getAstNode();
				pAstNode->rightNode->setVariateName(structMemberName);
				structMember.getAstNode()->faRootNode = pAstNode;
			};
			boost::pfr::for_each_field(defultValue, lammdaReflect);
		}
		// 如果是数组的话 有点问题 数据元素默认一个 好像就不需要数组了
		
	}

	// 常规变量的带参构造
	VariateProxy(const Type& value) requires is_mathematical<Type> && std::is_fundamental<Type>::value : elementCount(1)
	{
		// 数据拷贝
		dataValuePointer = (Type*)malloc(sizeof(Type));
		memcpy(this->dataValuePointer, &value, sizeof(Type));

		// 变量的Ast构建
		std::string typeName = typeid(Type).name();
		std::string thisVariableName = "var_" + std::to_string(AstNode::defineTimes++);
		astNode = new AstNode(thisVariableName, typeName, AstNode::AstNodeType::VARIATE_DEFINE);

		std::stringstream ss;
		ss << value;
		std::string valueStr;
		std::getline(ss, valueStr);
		std::regex spaceRegex(" ");
		valueStr = std::regex_replace(valueStr, spaceRegex, ",");

		astNode->rightNode = new AstNode(valueStr, "", AstNode::AstNodeType::LITER_EXPRESSION);
	}


	VariateProxy(const Type& value) requires is_mathematical<Type> && !std::is_fundamental<Type>::value : elementCount(1)
	{
		// 数据拷贝
		dataValuePointer = (Type*)malloc(sizeof(Type));
		memcpy(this->dataValuePointer, &value, sizeof(Type));

		// 变量的Ast构建
		std::string typeName = typeid(Type).name();
		std::string thisVariableName = "var_" + std::to_string(AstNode::defineTimes++);
		astNode = new AstNode(thisVariableName, typeName, AstNode::AstNodeType::VARIATE_DEFINE);

		std::stringstream ss;
		ss << value;
		std::string valueStr;
		std::getline(ss, valueStr);
		std::regex spaceRegex(" ");
		valueStr = std::regex_replace(valueStr, spaceRegex, ",");

		std::string mapping_name = ktm_class_mapping[typeid(Type).name()];
		//vec
		if (mapping_name.find("vec") != std::string::npos)
		{
			int max_index = mapping_name[mapping_name.length() - 1] - '0';
			ElementType initDefaultValue = 0;
			indexVisitPointer = (VariateProxy<ElementType>*) (malloc(sizeof(VariateProxy<ElementType>) * max_index));

			for (int index = 0; index < max_index; index++)
			{
				VariateProxy<ElementType>* tempIndexProxy = new VariateProxy<ElementType>(value[index]);
				memcpy(indexVisitPointer + index, tempIndexProxy, sizeof(VariateProxy<ElementType>));
				indexVisitPointer[index].isIndexVariable = true;
				indexVisitPointer[index].getAstNode(false)->variateName = thisVariableName + "[" + std::to_string(index) + "]";
			}
		}
		//mat
		else
		{

		}
		valueStr = typeName + "(" + valueStr + ")";
		
		astNode->rightNode = new AstNode(valueStr, "", AstNode::AstNodeType::LITER_EXPRESSION);
	}


	// 结构体变量的带参构造
	//boost::pfr just for aggregate
	VariateProxy(const Type& value) requires (std::is_class<Type>::value && std::is_aggregate<Type>::value && !is_mathematical<Type>) : elementCount(1)
	{
		// 存储数据
		dataValuePointer = (Type*)malloc(sizeof(Type));
		memcpy(this->dataValuePointer, &value, sizeof(Type));

		// 结构体Ast结构定义
		std::string typeName = typeid(Type).name();
		std::string thisVariableName = "var_" + std::to_string(AstNode::defineTimes++);
		astNode = new AstNode(thisVariableName, typeName, AstNode::AstNodeType::STRUCT_DEFINE);


		AstNode* pAstNode = astNode;

		auto lammdaReflect = [&](auto& structMember)
		{
			// 结构体的调用一定在里面内置类型的调用之后
			std::string structMemberName = thisVariableName + "." + structMember.getAstNode()->getVariateName();
			std::string structMemberType = structMember.getAstNode()->getTypeName();
			pAstNode->leftNode = new AstNode(structMemberName, structMemberType, AstNode::AstNodeType::STRUCT_ELEMENT);
			pAstNode = pAstNode->leftNode;
			pAstNode->faRootNode = astNode;

			pAstNode->rightNode = structMember.getAstNode();
			pAstNode->rightNode->setVariateName(structMemberName);
			structMember.getAstNode()->faRootNode = pAstNode;
		};
	
		boost::pfr::for_each_field(value, lammdaReflect);
	}

	//VariateProxy(const Type& value)
	//	: elementCount(1)
	//{
	//	//this->variateName = "var_" + std::to_string(AstNode::defineTimes);
	//	//this->typeName = typeid(Type).name();

	//	astNode = new AstNode("var_" + std::to_string(AstNode::defineTimes++), typeid(Type).name(), AstNode::AstNodeType::VARIATE_DEFINE);

	//	dataValuePointer = (Type*)malloc(sizeof(Type));
	//	memcpy(this->dataValuePointer, &value, sizeof(Type));

	//	//astNode->rightNode = new AstNode(std::to_string(value), typeid(Type).name(), AstNode::AstNodeType::VARIATE_DEFINE);
	//}
	
	
	VariateProxy(const std::initializer_list<Type>& value) : elementCount(value.size())
	{
		//this->variateName = "arr_" + std::to_string(AstNode::defineTimes) + "[" + std::to_string(value.size()) + "]";
		//this->typeName = typeid(Type).name();
		assert(value.size() > 0);
		
	 	astNode = new AstNode("arr_" + std::to_string(AstNode::defineTimes), typeid(Type).name(), AstNode::AstNodeType::ARRAY_DEFINE),
		dataValuePointer = (Type*)malloc(value.size() * sizeof(Type));

		uint32_t index = 0;
		AstNode* pAstNode = astNode;
		for (const Type& item : value)
		{
			memcpy(dataValuePointer + index, &item, sizeof(Type));

			pAstNode->leftNode = new AstNode(astNode->getVariateName() + "[" + std::to_string(index) + "]", typeid(Type).name(), AstNode::AstNodeType::ARRAY_ELEMENT);
			pAstNode = pAstNode->leftNode;
			pAstNode->rightNode = item.getAstNode();
			item.getAstNode()->faRootNode = pAstNode;

			pAstNode -> faRootNode = astNode;
			index++;
		}
	}


	// 有问题
	VariateProxy(const VariateProxy<Type>& value) : elementCount(1)
	{
		astNode = new AstNode("var_" + std::to_string(AstNode::defineTimes++), typeid(Type).name(), value.getAstNode()->getAstNodeType());

		dataValuePointer = (Type*)malloc(sizeof(Type));
		if (value.dataValuePointer != nullptr)
		{
			memcpy(this->dataValuePointer, value.dataValuePointer, sizeof(Type));
		}

		astNode->rightNode = value.getAstNode();
	}

	//用于生成一个Proxy来保存AstNode
	VariateProxy(AstNode* pAstNode)
	{
		this->astNode = pAstNode;
	}

	~VariateProxy() 
	{
		if(astNode == nullptr)
		{
			return;
		}

		if(std::is_class<Type>::value || std::is_fundamental<Type>::value)//包装类
		{

		}else if(std::is_array<Type>::value)//数组
		{

		}else// 基本元素
		{

		} 

	}

	Type* operator->()
	{
		return dataValuePointer;
	}

	//operator Type* ()
	//{
	//	return dataValuePointer;
	//}

	auto operator[](int input) -> VariateProxy<ElementType>&
	{
		if(getAstNode()->astNodeType == AstNode::AstNodeType::ARRAY_DEFINE)
		{
			AstNode* pAstNode = getAstNode();
			for (int idx = 0; idx < input; ++idx)
			{
				pAstNode = pAstNode->leftNode;
			}
			return indexVisitPointer[input];
		}
		else if (ktm_class_mapping.find(typeid(Type).name()) != ktm_class_mapping.end())
		{
			// vec
			std::string mapping_name = ktm_class_mapping[typeid(Type).name()];
			if (mapping_name.find("vec") != std::string::npos)
			{
				int max_index = mapping_name[mapping_name.length() - 1] - '0';
				if (input >= max_index)
				{
					throw "out of boundary about class : " + mapping_name + ", visited index : " + std::to_string(input);
				}
				else
				{
					return indexVisitPointer[input];
				}
			}
			// mat
			else
			{

			}
		}
		else 
		{
			throw "try to visit element by [] on incorrect variable type";
		}
	}

	// 访问的时候 不只是当前元素 如果它是某个元素的子元素 也会连带其他元素一起访问
	AstNode* getAstNode(bool addVisitedTime=true) const
	{
		addVisitedTime &= !isIndexVariable;
		if (addVisitedTime)
		{
			AstNode* pAstNode = astNode;
			while (pAstNode != nullptr)
			{
				if (pAstNode->inited == false)
				{
					pAstNode->inited = true;
					if (astNode->astNodeType == AstNode::AstNodeType::VARIATE_DEFINE
						|| astNode->astNodeType == AstNode::AstNodeType::STRUCT_DEFINE
						|| astNode->astNodeType == AstNode::AstNodeType::ARRAY_DEFINE)
					{
						abstractSyntaxTree.addAstStmts(pAstNode);
					}
				}
				pAstNode = pAstNode->faRootNode;
			}
		}
		return astNode;
	}

	AstNode getComputeNode()
	{
		getAstNode();
		return this->computeAstNode;
	}

	std::string getValueExpression()
	{
		std::string valueExpression = "";

		if (elementCount == 1)
		{
			valueExpression = std::to_string(*dataValuePointer);
		}
		else
		{
			valueExpression = "{";
			for (int elementIdx = 0; elementIdx < elementCount; ++elementIdx)
			{
				valueExpression += std::to_string(dataValuePointer[elementIdx]);
				if (elementIdx < elementCount - 1)
				{
					valueExpression += ",";
				}
			}
			valueExpression += "}";
		}
		return valueExpression;
	}

	VariateProxy& operator=(const VariateProxy& rhs)
	{
		AstNode* resultAstNode = new AstNode("=", AstNode::AstNodeType::VARIATE_OPERATOR);
		resultAstNode->leftNode = this->getAstNode();
		resultAstNode->rightNode = rhs.getAstNode();
		abstractSyntaxTree.addAstStmts(resultAstNode);
		return *this;
	}

#define CREATE_OPERATOR_UNARY(Operator) \
	VariateProxy& operator Operator() \
	{ \
		AstNode* resultAstNode = new AstNode(std::string(#Operator), AstNode::AstNodeType::VARIATE_OPERATOR);\
		resultAstNode->leftNode = nullptr;\
		resultAstNode->rightNode = this->getAstNode(false); \
		return *(new VariateProxy(resultAstNode)); \
	}

#define CREATE_OPERATOR_BINARY(Operator) \
	VariateProxy& operator Operator(const VariateProxy& rhs) \
	{ \
		AstNode* resultAstNode = new AstNode(std::string(#Operator), AstNode::AstNodeType::VARIATE_OPERATOR);\
		resultAstNode->leftNode = this->getAstNode(false);\
		resultAstNode->rightNode = rhs.getAstNode(false);\
		return *(new VariateProxy(resultAstNode)); \
	}

	CREATE_OPERATOR_UNARY(+);
	CREATE_OPERATOR_UNARY(-);

	CREATE_OPERATOR_BINARY(+);
	CREATE_OPERATOR_BINARY(-);
	CREATE_OPERATOR_BINARY(*);
	CREATE_OPERATOR_BINARY(/ );
	CREATE_OPERATOR_BINARY(%);

	CREATE_OPERATOR_UNARY(++);
	CREATE_OPERATOR_UNARY(--);

	CREATE_OPERATOR_UNARY(!);
	CREATE_OPERATOR_BINARY(|| );
	CREATE_OPERATOR_BINARY(&&);

	CREATE_OPERATOR_BINARY(> );
	CREATE_OPERATOR_BINARY(>= );
	CREATE_OPERATOR_BINARY(< );
	CREATE_OPERATOR_BINARY(<= );
	CREATE_OPERATOR_BINARY(!= );
	CREATE_OPERATOR_BINARY(== );

	CREATE_OPERATOR_UNARY(~);
	CREATE_OPERATOR_BINARY(&);
	CREATE_OPERATOR_BINARY(| );
	CREATE_OPERATOR_BINARY(^);
	CREATE_OPERATOR_BINARY(<< );
	CREATE_OPERATOR_BINARY(>> );

	CREATE_OPERATOR_BINARY(+= );
	CREATE_OPERATOR_BINARY(-= );
	CREATE_OPERATOR_BINARY(*= );
	CREATE_OPERATOR_BINARY(/= );
	CREATE_OPERATOR_BINARY(%= );
	CREATE_OPERATOR_BINARY(&= );
	CREATE_OPERATOR_BINARY(|= );
	CREATE_OPERATOR_BINARY(^= );
	CREATE_OPERATOR_BINARY(>>= );
	CREATE_OPERATOR_BINARY(<<= );

	//CREATE_OPERATOR_EQUAL(=);

	//CREATE_OPERATOR_PARAMETER_INT(++);
	//CREATE_OPERATOR_PARAMETER_INT(--);
	//CREATE_OPERATOR_PARAMETER_INT([]);

	VariateProxy* rootProxy = nullptr;

	Type* getDataPointer()
	{
		return dataValuePointer;
	}

	void dfsReleaseAstNode(AstNode* root)
	{
		if (!root) return;
		if (root->leftNode)
		{
			dfsReleaseAstNode(root->leftNode);
		}
		if (root->rightNode)
		{
			dfsReleaseAstNode(root->rightNode);
		}
		delete root;
	}

	void releaseAstNode()
	{
		dfsReleaseAstNode(astNode);
	}

	void setAstNode(AstNode* root)
	{
		dfsReleaseAstNode(root->rightNode);
		astNode ->rightNode = root;
	}

	bool isIndexVariable = false;

private:
	uint16_t elementCount = 1;
	Type* dataValuePointer = nullptr;
	AstNode* astNode = nullptr;
	mutable bool inited = false;
 	std::string variateName = "";
	std::string typeName = "";
	VariateProxy<ElementType>* indexVisitPointer = nullptr;

	// define operator  ast:{type, variableName, left, right, nodeType} 
	/*
	Int A = 1;

	Int A[10];->IntA
		A[1];->IntA[1]

	// if else while
	$if(a > 1 && b > 1)=>
	{
		a = b + c;
		b = c + d;
		condition->
	}
	*/
};