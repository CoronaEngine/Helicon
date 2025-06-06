#pragma once
#include <string>
#include <memory>

namespace EmbeddedShader::AST
{
	struct Statement;
	struct DefineLocalVariate;
	struct Node
	{
		friend class Parser;
		virtual ~Node() = default;
		virtual std::string parse();
	};

	class Type : public Node
	{

	};

	class Value : public Node
	{
	};

	struct Variate : Value
	{
		std::string name;
		std::shared_ptr<Type> type;
		std::string parse() override;
	};

	using LocalVariate = Variate;

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

	struct DefineLocalVariate : Statement
	{
		std::shared_ptr<LocalVariate> localVariate;
		std::shared_ptr<Value> value;
		std::string parse() override;
	};

	struct BinaryOperator : Value
	{
		// enum class Type
		// {
		// 	Add, // +
		// 	Subtract, // -
		// 	Multiply, // *
		// 	Divide,  // /
		// 	Modulo,  // %
		// 	BitwiseAnd, // &
		// 	BitwiseOr, // |
		// 	BitwiseXor, // ^
		// 	BitwiseLeftShift, // <<
		// 	BitwiseRightShift, // >>
		// 	Equal, // =
		// 	NotEqual, // !=
		// 	LessThan, // <
		// 	LessThanOrEqual, // <=
		// 	GreaterThan, // >=
		// 	GreaterThanOrEqual, // >
		// 	And, // &&,
		// 	Or, // ||
		// };

		std::shared_ptr<Value> value1;
		std::shared_ptr<Value> value2;
		std::string type;
		std::string parse() override;
	};

	struct Assign : Statement
    {
        std::shared_ptr<LocalVariate> variate;
        std::shared_ptr<Value> value;
		std::string parse() override;
    };

	struct InputVariate : Variate
	{
		size_t index = 0;
	};

	struct DefineInputVariate : Statement
    {
		std::shared_ptr<InputVariate> localVariate;
		std::string parse() override;
    };
}
