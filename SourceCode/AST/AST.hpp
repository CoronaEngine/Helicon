#pragma once

#include <AST/Parser.hpp>
#include <AST/Node.hpp>

namespace EmbeddedShader::AST
{
	//AST不会写过多约束，此部分交给前端进行处理

	class AST
	{
		AST() = default;
	public:
		template<typename VariateType> requires std::is_arithmetic_v<VariateType>
		static std::shared_ptr<LocalVariate> defineLocalVariate(VariateType&& value);
		static std::shared_ptr<Value> binaryOperator(std::shared_ptr<Value> value1, std::shared_ptr<Value> value2, BinaryOperator::Type type);
	private:
		static void addStatement(std::shared_ptr<Statement> statement);
	};

	template<typename VariateType> requires std::is_arithmetic_v<VariateType>
	std::shared_ptr<LocalVariate> AST::defineLocalVariate(VariateType&& value)
	{
		NumericType type;
		type.name = NumericType::typeName<VariateType>;

		NumericValue numericValue;
		numericValue.value = NumericValue::getValue(std::forward<VariateType>(value));

		auto localVariate = std::make_shared<LocalVariate>();
		localVariate->name = Parser::getUniqueVariateName();

		auto defineNode = std::make_shared<DefineLocalVariate>();
		defineNode->localVariate = localVariate;
		defineNode->type = std::make_shared<NumericType>(type);
		defineNode->value = std::make_shared<NumericValue>(numericValue);
		addStatement(defineNode);
		return localVariate;
	}
}