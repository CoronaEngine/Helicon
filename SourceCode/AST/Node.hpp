#pragma once
#include <string>
#include <memory>

namespace EmbeddedShader::AST
{
	class Node
	{
	public:
		virtual ~Node() = default;
		template<typename VariateType> requires std::is_arithmetic_v<VariateType>
		static void localVariate(VariateType&& value);
	private:
		static void addNode(std::shared_ptr<Node> node);
	};

	class Type : public Node
	{

	};

	struct NumericType : Type
	{
		std::string name;

		template<typename Type>
		static inline std::string_view typeName = "Unknown";
#define DEFINE_TYPE_NAME(Type,TypeName) template<> static inline std::string_view typeName<Type> = #TypeName;

		DEFINE_TYPE_NAME(int,int);
		DEFINE_TYPE_NAME(float,float);
		DEFINE_TYPE_NAME(double,double);

#undef DEFINE_TYPE_NAME
	};

	struct Statement : Node
	{
	};

	struct LocalVariate : Statement
	{
		std::shared_ptr<Type> type;
	};

	template<typename VariateType> requires std::is_arithmetic_v<VariateType>
	void Node::localVariate(VariateType&& value)
	{
		LocalVariate localVariateNode;
		localVariateNode.type = std::make_shared<NumericType>(NumericType{.name = NumericType::typeName<VariateType>});
		addNode(std::make_shared<LocalVariate>(localVariateNode));
	}
}
