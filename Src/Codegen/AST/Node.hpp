#pragma once
#include <string>
#include <memory>

#include <Codegen/AST/Enum.hpp>

namespace EmbeddedShader::Ast
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

	struct NameType : Type
	{
		std::string name;
		std::string parse() override;
	};

	class Value : public Node
	{
	public:
		std::shared_ptr<Type> type;
		virtual void access(AccessPermissions permissions);
	};

	struct Variate : Value
	{
		std::string name;
		std::string parse() override;
	};

	struct LocalVariate : Variate
	{

	};

	struct BasicType : NameType
	{

	};

	struct VecType : NameType
	{
	};

	struct BasicValue : Value
	{
		std::string value;
		std::string parse() override;
	};

	struct VecValue : Value
	{
		std::string value;
		std::string parse() override;
	};

	struct Statement : Node
	{
		virtual void resetAccessPermissions() {}
		virtual void resetUsedFlag() {}
	};

	struct DefineLocalVariate : Statement
	{
		std::shared_ptr<LocalVariate> localVariate;
		std::shared_ptr<Value> value;
		std::string parse() override;
	};

	struct BinaryOperator : Value
	{
		std::shared_ptr<Value> value1;
		std::shared_ptr<Value> value2;
		std::string operatorType;
		std::string parse() override;
	};

	struct Assign : Statement
    {
        std::shared_ptr<Value> leftValue;
        std::shared_ptr<Value> rightValue;
		std::string parse() override;
    };

	struct InputVariate : Variate
	{
		size_t location = 0;
		std::string parse() override;
	};

	struct DefineInputVariate : Statement
    {
		std::shared_ptr<InputVariate> variate;
		std::string parse() override;
    };

	struct MemberAccess : Value
	{
		std::shared_ptr<Value> value;
		std::string memberName;
		std::string parse() override;
		void access(AccessPermissions permissions) override;
	};

	struct OutputVariate : Variate
	{
		size_t location = 0;
		std::string parse() override;
	};

	struct DefineOutputVariate : Statement
	{
		std::shared_ptr<OutputVariate> variate;
		std::string parse() override;
	};

	struct IfStatement : Statement
    {
        std::shared_ptr<Value> condition;
        std::vector<std::shared_ptr<Statement>> statements;
        std::string parse() override;
    };

	//StructuredBuffer or RWStructuredBuffer
	struct UniversalArray : Variate
	{
		//Variate::type 将被解释为元素类型

		AccessPermissions permissions = AccessPermissions::None;
		void access(AccessPermissions permissions) override;
	};

	struct ElementVariate : Variate
	{
		std::shared_ptr<UniversalArray> array;
		void access(AccessPermissions permissions) override;
	};

	struct DefineUniversalArray : Statement
	{
		std::shared_ptr<UniversalArray> array;
		std::string parse() override;
		void resetAccessPermissions() override;
	};

	struct UniformVariate : Variate
	{
		AccessPermissions permissions = AccessPermissions::None;
		std::string parse() override;
		void access(AccessPermissions permissions) override;
	};

	struct DefineUniformVariate : Statement
	{
		std::shared_ptr<UniformVariate> variate;
		std::string parse() override;
		void resetAccessPermissions() override;
	};

	struct AggregateType : NameType
	{
		bool isUsed = false;
		std::vector<std::shared_ptr<Variate>> members;
		static thread_local inline std::unordered_map<std::string,std::shared_ptr<AggregateType>> aggregateTypeMap;
	};

	struct DefineAggregateType : Statement
	{
		std::shared_ptr<AggregateType> aggregate;
		void resetUsedFlag() override;
		std::string parse() override;
	};
}
