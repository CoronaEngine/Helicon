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
		template<typename VecValueType>
		struct VecTraits
		{

		};

		template<typename Type,size_t N>
		struct VecTraits<ktm::vec<N,Type>>
		{
			using ValueType = Type;
			static constexpr size_t dimension = N;
		};
	public:

		template<typename VariateType> requires std::is_arithmetic_v<VariateType>
		static std::shared_ptr<BaseValue> createValue(VariateType&& value);
		template<typename VariateType> requires ktm::is_vector_v<VariateType>
		static std::shared_ptr<VecValue> createValue(const VariateType& value);

		template<typename ValueType,size_t N>
		static std::shared_ptr<VecValue> createVecValue(const std::array<std::shared_ptr<Value>, N>& value);
		template<typename ValueType,typename... Args>
		static std::shared_ptr<VecValue> createVecValue(Args&&... args);

		template<typename VariateType> requires std::is_arithmetic_v<VariateType>
		static std::shared_ptr<LocalVariate> defineLocalVariate(VariateType&& value);
		template<typename VariateType> requires ktm::is_vector_v<VariateType>
		static std::shared_ptr<LocalVariate> defineLocalVariate(const VariateType& value);
		static std::shared_ptr<LocalVariate> defineLocalVariate(std::shared_ptr<Type> type, std::shared_ptr<Value> initValue);

		static std::shared_ptr<Value> binaryOperator(std::shared_ptr<Value> value1, std::shared_ptr<Value> value2, std::string operatorType);
		template<typename ArithmeticType> requires std::is_arithmetic_v<ArithmeticType>
		static std::shared_ptr<Value> binaryOperator(std::shared_ptr<Value> value1, ArithmeticType&& value2, std::string operatorType);

		static void assign(std::shared_ptr<Value> variate, std::shared_ptr<Value> value);

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

		template<typename Type>
		struct ValueConverter<std::shared_ptr<Type>>
		{
			static std::shared_ptr<Value> convert(const std::shared_ptr<Type>& value)
			{
				return value;
			}
		};
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

	template<typename ValueType, size_t N>
	std::shared_ptr<VecValue> AST::createVecValue(const std::array<std::shared_ptr<Value>, N>& value)
	{
		auto type = VecType::createVecType<ValueType>();
		auto vecValue = std::make_shared<VecValue>();
		vecValue->type = type;

		std::string valueStr;
		for (size_t i = 0; i < value.size() - 1; ++i)
		{
			valueStr += value[i]->parse() + ",";
		}
		valueStr += value.back()->parse();
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
		vecValue->value = ((first? (first = false,ValueConverter<std::remove_cvref_t<Args>>::convert(std::forward<Args>(args))->parse()) :
				ValueConverter<std::remove_cvref_t<Args>>::convert(std::forward<Args>(args))->parse() + ",") + ...);
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
		auto vecValue = createValue(vecValue);
		return defineLocalVariate(vecValue->type,vecValue);
	}

	template<typename BaseType> requires std::is_arithmetic_v<BaseType>
	std::shared_ptr<Value> AST::binaryOperator(std::shared_ptr<Value> value1, BaseType&& value2,
		std::string operatorType)
	{
		auto numericValue2 = std::make_shared<BaseValue>();
		numericValue2->value = BaseValue::getValue(std::forward<BaseType>(value2));
		return binaryOperator(std::move(value1), std::move(numericValue2), std::move(operatorType));
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
