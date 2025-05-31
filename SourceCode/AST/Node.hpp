#pragma once
#include <string>
#include <memory>

namespace EmbeddedShader::AST
{
	struct Statement;
	class Node
	{
		friend class Parser;
	public:
		virtual ~Node() = default;
		template<typename VariateType> requires std::is_arithmetic_v<VariateType>
		static void localVariate(VariateType&& value);
	private:
		static void addNode(std::shared_ptr<Statement> node);
	public:
		virtual std::string parse();
	};

	class Type : public Node
	{

	};

	class Value : public Node
	{

	};

	struct NumericType : Type
	{
		std::string name;

		template<typename Type>
		static inline std::string_view typeName = "Unknown";
#define DEFINE_TYPE_NAME(Type,TypeName) template<> static inline std::string_view typeName<Type> = #TypeName;

		DEFINE_TYPE_NAME(int32_t,int);
		DEFINE_TYPE_NAME(uint32_t,uint);
		DEFINE_TYPE_NAME(float,float);
		DEFINE_TYPE_NAME(double,double);

#undef DEFINE_TYPE_NAME
		std::string parse() override;
	};

	struct NumericValue : Value
	{
		std::string value;

		template<typename ValueType>
		static std::string getValue(ValueType value) { return std::to_string(value);}
#define DEFINE_NUMERIC_VALUE(ValueType,ValueOperate) static std::string getValue(ValueType value) { return ValueOperate; }
//...
#undef DEFINE_NUMERIC_VALUE
		std::string parse() override;
	};

	struct Statement : Node
	{
	};

	struct LocalVariate : Statement
	{
		std::shared_ptr<Type> type;
		std::shared_ptr<Value> value;
		std::string parse() override;
	};

	template<typename VariateType> requires std::is_arithmetic_v<VariateType>
	void Node::localVariate(VariateType&& value)
	{
		NumericType type;
		type.name = NumericType::typeName<VariateType>;

		NumericValue numericValue;
		numericValue.value = NumericValue::getValue(std::forward<VariateType>(value));

		LocalVariate localVariateNode;
		localVariateNode.type = std::make_shared<NumericType>(type);
		localVariateNode.value = std::make_shared<NumericValue>(numericValue);
		addNode(std::make_shared<LocalVariate>(localVariateNode));
	}
}
