#pragma once
#include <ktm/ktm.h>
#include "VariateProxy.h"

namespace MathFunc
{
	template<typename T>
	T clamp(T variable, T a, T b)
	{
		T variableClamped = ktm::clamp(*(variable.getDataPointer()), *(a.getDataPointer()), *(b.getDataPointer()));
		AstNode* functionAstNode = new AstNode("clamp(" + variable.getAstNode()->variateName + "," + a.getAstNode()->variateName + "," + b.getAstNode()->variateName + ")", "", AstNode::AstNodeType::VARIATE_DEFINE);
		variableClamped.setAstNode(functionAstNode);
		return variableClamped;
	}

	template<typename T>
	T sqrt(T variable)
	{
		T variableSqrted = ktm::sqrt(*(variable.getDataPointer()));
		AstNode* functionAstNode = new AstNode("sqrt(" + variable.getAstNode()->variateName + ")", "", AstNode::AstNodeType::VARIATE_DEFINE);
		variableSqrted.setAstNode(functionAstNode);
		return variableSqrted;
	}

	template<typename T>
	T pow(T variable, T power)
	{
		T variablePowered = ktm::pow(*(variable.getDataPointer()), *(power.getDataPointer()));
		AstNode* functionAstNode = new AstNode("power(" + variable.getAstNode()->variateName + "," + power.getAstNode()->variateName + ")", "", AstNode::AstNodeType::VARIATE_DEFINE);
		variablePowered.setAstNode(functionAstNode);
		return variablePowered;
	}
}