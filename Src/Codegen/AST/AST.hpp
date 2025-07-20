#pragma once

#include <Codegen/AST/Node.hpp>
#include <utility>
#include <boost/pfr/core.hpp>
#include <boost/pfr/core_name.hpp>
#include <Codegen/AST/Parser.hpp>
#include <Codegen/Generator/SlangGenerator.hpp>
#include <Codegen/ParseHelper.h>

namespace EmbeddedShader::Generator
{
	class SlangGenerator;
	namespace OpenGL
	{
		class ShaderGenerator;
	}
}

namespace EmbeddedShader::Ast
{
	//AST不会写过多约束，此部分交给前端进行处理

	class AST
	{
		friend class Generator::OpenGL::ShaderGenerator;
		friend class Generator::SlangGenerator;
		AST() = default;
	public:

		template<typename T> requires std::is_arithmetic_v<T>
		static std::shared_ptr<BasicType> createType();
		template<typename T> requires ktm::is_vector_v<T>
		static std::shared_ptr<VecType> createType();
		template<typename T> requires std::is_aggregate_v<T>
		static std::shared_ptr<AggregateType> createType();

		template<typename VariateType> requires std::is_arithmetic_v<VariateType>
		static std::shared_ptr<BasicValue> createValue(VariateType value);
		template<typename VariateType> requires ktm::is_vector_v<VariateType>
		static std::shared_ptr<VecValue> createValue(const VariateType& value);
		template<typename VariateType> requires std::is_aggregate_v<VariateType>
		static std::shared_ptr<AggregateValue> createValue(const VariateType& value);

		template<typename ValueType,typename... Args> requires ktm::is_vector_v<ValueType>
		static std::shared_ptr<VecValue> createVecValue(Args&&... args);

		template<typename VariateType>
		static std::shared_ptr<LocalVariate> defineLocalVariate(VariateType&& value);
		static std::shared_ptr<LocalVariate> defineLocalVariate(std::shared_ptr<Type> type, std::shared_ptr<Value> initValue);

		static std::shared_ptr<Value> binaryOperator(std::shared_ptr<Value> value1, std::shared_ptr<Value> value2, std::string operatorType);
		static std::shared_ptr<Value> binaryOperator(auto&& value1, auto&& value2, std::string operatorType);

		static void assign(std::shared_ptr<Value> variate, std::shared_ptr<Value> value);
		static void assign(auto&& variate, auto&& value);

		static std::shared_ptr<InputVariate> defineInputVariate(std::shared_ptr<Type> type, size_t location);
		template<typename VariateType>
		static std::shared_ptr<InputVariate> defineInputVariate(size_t location);

		static std::shared_ptr<MemberAccess> access(std::shared_ptr<Value> value, std::string memberName);

		static std::shared_ptr<OutputVariate> defineOutputVariate(std::shared_ptr<Type> type, size_t location);
		template<typename VariateType>
		static std::shared_ptr<OutputVariate> defineOutputVariate(size_t location);

		static void beginIf(std::shared_ptr<Value> condition);
		static void endIf();

		static std::shared_ptr<UniversalArray> defineUniversalArray(std::shared_ptr<Type> elementType);
		template<typename ElementType>
		static std::shared_ptr<UniversalArray> defineUniversalArray();

		static std::shared_ptr<UniformVariate> defineUniformVariate(std::shared_ptr<Type> type);
		template<typename VariateType>
		static std::shared_ptr<UniformVariate> defineUniformVariate();

		template<typename T> requires std::is_aggregate_v<T>
		static std::shared_ptr<AggregateType> createAggregateType(const T& value);

		static std::shared_ptr<Variate> getPositionOutput();

		static std::shared_ptr<ElementVariate> at(std::shared_ptr<UniversalArray> array, uint32_t index);
		static std::shared_ptr<ElementVariate> at(std::shared_ptr<UniversalArray> array, const std::shared_ptr<Value>& index);
	private:
		static void addLocalStatement(std::shared_ptr<Statement> statement);
		static void addInputStatement(std::shared_ptr<Statement> inputStatement);
		static void addOutputStatement(std::shared_ptr<Statement> outputStatement);
		static void addGlobalStatement(std::shared_ptr<Statement> globalStatement);
		static std::stack<std::vector<std::shared_ptr<Statement>>*>& getLocalStatementStack();
		static EmbeddedShaderStructure& getEmbeddedShaderStructure();

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

		template<typename T> requires ktm::is_vector_v<T>
		static std::shared_ptr<VecType> createVecType()
		{
			auto type = std::make_shared<VecType>();
			type->name = Generator::SlangGenerator::getVariateTypeName<T>();
			return type;
		}
	};

	template<typename T> requires std::is_arithmetic_v<T>
	std::shared_ptr<BasicType> AST::createType()
	{
		auto type = std::make_shared<BasicType>();
		type->name = Generator::SlangGenerator::getVariateTypeName<T>();
		return type;
	}

	template<typename T> requires ktm::is_vector_v<T>
	std::shared_ptr<VecType> AST::createType()
	{
		return createVecType<T>();
	}

	template<typename T> requires std::is_aggregate_v<T>
	std::shared_ptr<AggregateType> AST::createType()
	{
		return createAggregateType<T>({});
	}

	template<typename VariateType> requires std::is_arithmetic_v<VariateType>
	std::shared_ptr<BasicValue> AST::createValue(VariateType value)
	{
		auto basicValue = std::make_shared<BasicValue>();
		basicValue->value = Generator::SlangGenerator::getValueOutput(std::forward<VariateType>(value));
		basicValue->type = createType<std::remove_cvref_t<VariateType>>();
		return basicValue;
	}

	template<typename VariateType> requires ktm::is_vector_v<VariateType>
	std::shared_ptr<VecValue> AST::createValue(const VariateType& value)
	{
		auto type = createVecType<VariateType>();
		auto vecValue = std::make_shared<VecValue>();
		vecValue->type = type;

		vecValue->value = Generator::SlangGenerator::getValueOutput<VariateType>(value);
		return vecValue;
	}

	template<typename VariateType> requires std::is_aggregate_v<VariateType>
	std::shared_ptr<AggregateValue> AST::createValue(const VariateType& value)
	{
		auto aggregateValue = std::make_shared<AggregateValue>();
		aggregateValue->type = createType<std::remove_cvref_t<VariateType>>();
		aggregateValue->value = Generator::SlangGenerator::getValueOutput<std::remove_cvref_t<VariateType>>(value);
		return aggregateValue;
	}

	template<typename ValueType, typename ... Args> requires ktm::is_vector_v<ValueType>
	std::shared_ptr<VecValue> AST::createVecValue(Args&&... args)
	{
		auto type = createVecType<ValueType>();
		auto vecValue = std::make_shared<VecValue>();
		vecValue->type = type;

		bool first = true;
		//ide可能会误报警告
		vecValue->value = Generator::SlangGenerator::getVariateTypeName<ValueType>() + "(" + ((first? (first = false,valueConverter(std::forward<Args>(args))->parse()) :
				valueConverter(std::forward<Args>(args))->parse() + ",") + ...) + ")";
		return vecValue;
	}

	template<typename VariateType>
	std::shared_ptr<LocalVariate> AST::defineLocalVariate(VariateType&& value)
	{
		return defineLocalVariate(createType<std::remove_cvref_t<VariateType>>(),createValue(std::forward<VariateType>(value)));
	}

	std::shared_ptr<Value> AST::binaryOperator(auto&& value1, auto&& value2, std::string operatorType)
	{
		return binaryOperator(valueConverter(std::forward<decltype(value1)>(value1)),valueConverter(std::forward<decltype(value2)>(value2)),std::move(operatorType));
	}

	void AST::assign(auto&& variate, auto&& value)
	{
		assign(valueConverter(std::forward<decltype(variate)>(variate)),valueConverter(std::forward<decltype(value)>(value)));
	}

	template<typename VariateType>
	std::shared_ptr<InputVariate> AST::defineInputVariate(size_t location)
	{
		return defineInputVariate(createType<std::remove_cvref_t<VariateType>>(),location);
	}

	template<typename VariateType>
	std::shared_ptr<OutputVariate> AST::defineOutputVariate(size_t location)
	{
		return defineOutputVariate(createType<std::remove_cvref_t<VariateType>>(), location);
	}

	template<typename ElementType>
	std::shared_ptr<UniversalArray> AST::defineUniversalArray()
	{
		return defineUniversalArray(createType<std::remove_cvref_t<ElementType>>());
	}

	template<typename VariateType>
	std::shared_ptr<UniformVariate> AST::defineUniformVariate()
	{
		return defineUniformVariate(createType<VariateType>());
	}

	template<typename T> requires std::is_aggregate_v<T>
	std::shared_ptr<AggregateType> AST::createAggregateType(const T& value)
	{
		auto& map = AggregateType::aggregateTypeMap;
		auto it = map.find(typeid(T).name());
		if (it != map.end())
		{
			auto aggregateType = it->second;
			if (!aggregateType->isUsed)
			{
				auto defineNode = std::make_shared<DefineAggregateType>();
				defineNode->aggregate = aggregateType;
				addGlobalStatement(defineNode);
				aggregateType->isUsed = true;
			}

			return aggregateType;
		}

		auto aggregateType = std::make_shared<AggregateType>();
		aggregateType->isUsed = true;
		aggregateType->name = Parser::getUniqueAggregateTypeName();
		auto reflect = [&](std::string_view name, auto&& structMember, std::size_t i)
		{
			using MemberType = std::remove_cvref_t<decltype(structMember)>;
			auto member = std::make_shared<Variate>();
			member->name = name;

			if constexpr (ParseHelper::isProxy<MemberType>())
				member->type = createType<std::remove_cvref_t<typename MemberType::value_type>>();
			else
				member->type = createType<MemberType>();

			aggregateType->members.push_back(std::move(member));
		};
		boost::pfr::for_each_field_with_name(value,reflect);

		auto defineNode = std::make_shared<DefineAggregateType>();
		defineNode->aggregate = aggregateType;
		addGlobalStatement(defineNode);

		map.insert({typeid(T).name(), aggregateType});
		return aggregateType;
	}
}
