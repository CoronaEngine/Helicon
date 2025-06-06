#pragma once

#include <AST/Parser.hpp>
#include <AST/Node.hpp>
#include <utility>

namespace EmbeddedShader::AST
{
	//AST不会写过多约束，此部分交给前端进行处理

	class AST
	{
		AST() = default;
	public:
		template<typename VariateType> requires std::is_arithmetic_v<VariateType>
		static std::shared_ptr<LocalVariate> defineLocalVariate(VariateType&& value);
		static std::shared_ptr<LocalVariate> defineLocalVariate(std::shared_ptr<Type> type, std::shared_ptr<Value> initValue);
		static std::shared_ptr<Value> binaryOperator(std::shared_ptr<Value> value1, std::shared_ptr<Value> value2, std::string operatorType);
		template<typename ArithmeticType> requires std::is_arithmetic_v<ArithmeticType>
		static std::shared_ptr<Value> binaryOperator(std::shared_ptr<Value> value1, ArithmeticType&& value2, std::string operatorType);
		static void assign(std::shared_ptr<LocalVariate> variate, std::shared_ptr<Value> value);
		static std::shared_ptr<InputVariate> defineInputVariate(std::shared_ptr<Type> type);
		template<typename VariateType> requires std::is_arithmetic_v<VariateType>
		static std::shared_ptr<InputVariate> defineInputVariate();
	private:
		static void addStatement(std::shared_ptr<Statement> statement);
		static void addGlobalStatement(std::shared_ptr<Statement> globalStatement);
	};

	template<typename VariateType> requires std::is_arithmetic_v<VariateType>
	std::shared_ptr<LocalVariate> AST::defineLocalVariate(VariateType&& value)
	{
		auto type = std::make_shared<NumericType>();
		type->name = NumericType::typeName<VariateType>;

		auto numericValue = std::make_shared<NumericValue>();
		numericValue->value = NumericValue::getValue(std::forward<VariateType>(value));

		auto localVariate = std::make_shared<LocalVariate>();
		localVariate->name = Parser::getUniqueVariateName();
		localVariate->type = std::move(type);

		auto defineNode = std::make_shared<DefineLocalVariate>();
		defineNode->localVariate = localVariate;
		defineNode->value = std::move(numericValue);
		addStatement(defineNode);
		return localVariate;
	}

	template<typename ArithmeticType> requires std::is_arithmetic_v<ArithmeticType>
	std::shared_ptr<Value> AST::binaryOperator(std::shared_ptr<Value> value1, ArithmeticType&& value2,
		std::string operatorType)
	{
		auto numericValue2 = std::make_shared<NumericValue>();
		numericValue2->value = NumericValue::getValue(std::forward<ArithmeticType>(value2));
		return binaryOperator(std::move(value1), std::move(numericValue2), std::move(operatorType));
	}

	template<typename VariateType> requires std::is_arithmetic_v<VariateType>
	std::shared_ptr<InputVariate> AST::defineInputVariate()
	{
		auto type = std::make_shared<NumericType>();
		type->name = NumericType::typeName<VariateType>;
		return defineInputVariate(type);
	}
}
