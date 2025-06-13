#pragma once

#include <AST/Parser.hpp>
#include <AST/Node.hpp>
#include <utility>

namespace EmbeddedShader::Ast
{
	//AST不会写过多约束，此部分交给前端进行处理

	class AST
	{
		AST() = default;
	public:

		template<typename VariateType> requires std::is_arithmetic_v<VariateType>
		static std::shared_ptr<BaseValue> createValue(VariateType&& value);
		template<typename VariateType> requires ktm::is_vector_v<VariateType>
		static std::shared_ptr<VecValue> createValue(const VariateType& value);

		template<typename ValueType,typename... Args>
		static std::shared_ptr<VecValue> createVecValue(Args&&... args);

		template<typename VariateType> requires std::is_arithmetic_v<VariateType>
		static std::shared_ptr<LocalVariate> defineLocalVariate(VariateType&& value);
		template<typename VariateType> requires ktm::is_vector_v<VariateType>
		static std::shared_ptr<LocalVariate> defineLocalVariate(const VariateType& value);
		static std::shared_ptr<LocalVariate> defineLocalVariate(std::shared_ptr<Type> type, std::shared_ptr<Value> initValue);

		static std::shared_ptr<Value> binaryOperator(std::shared_ptr<Value> value1, std::shared_ptr<Value> value2, std::string operatorType);
		static std::shared_ptr<Value> binaryOperator(auto&& value1, auto&& value2, std::string operatorType);

		static void assign(std::shared_ptr<Value> variate, std::shared_ptr<Value> value);
		static void assign(auto&& variate, auto&& value);

		static std::shared_ptr<InputVariate> defineInputVariate(std::shared_ptr<Type> type);
		template<typename VariateType> requires std::is_arithmetic_v<VariateType>
		static std::shared_ptr<InputVariate> defineInputVariate();
		template<typename VariateType> requires ktm::is_vector_v<VariateType>
		static std::shared_ptr<InputVariate> defineInputVariate();

		static std::shared_ptr<MemberAccess> access(std::shared_ptr<Value> value, std::string memberName);

		static std::shared_ptr<Variate> getPositionOutput();
	private:
		static void addStatement(std::shared_ptr<Statement> statement);
		static void addGlobalStatement(std::shared_ptr<Statement> globalStatement);
		template<typename Type>
		struct ValueConverter
		{
			static std::shared_ptr<Value> convert(Type&& value)
			{
				return createValue(std::forward<Type>(value));
			}
		};

		template<typename Type> requires std::is_arithmetic_v<Type>
		struct ValueConverter<Type>
		{
			static std::shared_ptr<Value> convert(Type value)
			{
				return createValue(std::forward<Type>(value));
			}
		};

		template<typename Type>
		struct ValueConverter<std::shared_ptr<Type>>
		{
			static std::shared_ptr<Value> convert(const std::shared_ptr<Type>& value)
			{
				return value;
			}
		};

		static std::shared_ptr<Value> valueConverter(auto&& value)
		{
			return ValueConverter<std::remove_cvref_t<decltype(value)>>::convert(std::forward<decltype(value)>(value));
		}
	};

	template<typename VariateType> requires std::is_arithmetic_v<VariateType>
	std::shared_ptr<BaseValue> AST::createValue(VariateType&& value)
	{
		auto baseValue = std::make_shared<BaseValue>();
		baseValue->value = BaseValue::getValue(std::forward<VariateType>(value));
		return baseValue;
	}

	template<typename VariateType> requires ktm::is_vector_v<VariateType>
	std::shared_ptr<VecValue> AST::createValue(const VariateType& value)
	{
		auto type = VecType::createVecType<VariateType>();
		auto vecValue = std::make_shared<VecValue>();
		vecValue->type = type;

		std::string valueStr;
		auto vecArr = value.to_array();
		for (size_t i = 0; i < vecArr.size() - 1; ++i)
		{
			valueStr += BaseValue::getValue(vecArr[i]) + ",";
		}
		valueStr += BaseValue::getValue(vecArr.back());

		vecValue->value = std::move(valueStr);
		return vecValue;
	}

	template<typename ValueType, typename ... Args>
	std::shared_ptr<VecValue> AST::createVecValue(Args&&... args)
	{
		auto type = VecType::createVecType<ValueType>();
		auto vecValue = std::make_shared<VecValue>();
		vecValue->type = type;

		bool first = true;
		//ide可能会误报警告
		vecValue->value = ((first? (first = false,valueConverter(std::forward<Args>(args))->parse()) :
				valueConverter(std::forward<Args>(args))->parse() + ",") + ...);
		return vecValue;
	}

	template<typename VariateType> requires std::is_arithmetic_v<VariateType>
	std::shared_ptr<LocalVariate> AST::defineLocalVariate(VariateType&& value)
	{
		auto type = std::make_shared<BaseType>();
		type->name = BaseType::typeName<VariateType>;

		return defineLocalVariate(std::move(type), createValue(value));
	}

	template<typename VariateType> requires ktm::is_vector_v<VariateType>
	std::shared_ptr<LocalVariate> AST::defineLocalVariate(const VariateType& value)
	{
		auto vecValue = createValue(value);
		return defineLocalVariate(vecValue->type,vecValue);
	}

	std::shared_ptr<Value> AST::binaryOperator(auto&& value1, auto&& value2, std::string operatorType)
	{
		return binaryOperator(valueConverter(std::forward<decltype(value1)>(value1)),valueConverter(std::forward<decltype(value2)>(value2)),std::move(operatorType));
	}

	void AST::assign(auto&& variate, auto&& value)
	{
		assign(valueConverter(std::forward<decltype(variate)>(variate)),valueConverter(std::forward<decltype(value)>(value)));
	}

	template<typename VariateType> requires std::is_arithmetic_v<VariateType>
	std::shared_ptr<InputVariate> AST::defineInputVariate()
	{
		auto type = std::make_shared<BaseType>();
		type->name = BaseType::typeName<VariateType>;
		return defineInputVariate(type);
	}

	template<typename VariateType> requires ktm::is_vector_v<VariateType>
	std::shared_ptr<InputVariate> AST::defineInputVariate()
	{
		return defineInputVariate(VecType::createVecType<VariateType>());
	}
}
