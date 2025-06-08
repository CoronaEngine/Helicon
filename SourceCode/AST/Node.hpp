#pragma once
#include <string>
#include <memory>
#include <ktm/type_vec.h>

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

	struct NameType : Type
	{
		std::string name;
		std::string parse() override;
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

	struct BaseType : NameType
	{
		template<typename Type>
		static inline std::string_view typeName = "Unknown";
#define DEFINE_TYPE_NAME(Type,TypeName) template<> static inline std::string_view typeName<Type> = #TypeName;

		DEFINE_TYPE_NAME(int32_t,int);
		DEFINE_TYPE_NAME(uint32_t,uint);
		DEFINE_TYPE_NAME(float,float);
		DEFINE_TYPE_NAME(double,double);
		DEFINE_TYPE_NAME(bool,bool);

#undef DEFINE_TYPE_NAME
	};

	struct VecType : NameType
	{
		template<typename VecDataType>
		[[nodiscard]] static std::shared_ptr<VecType> createVecType();

		template<typename VecDataType>
		static constexpr std::string_view vecTypes = "Unknown";
#define DEFINE_VEC_TYPE(VecDataType,TypeName) template<> static constexpr std::string_view vecTypes<VecDataType> = #TypeName;
		DEFINE_VEC_TYPE(ktm::svec2,ivec2)
		DEFINE_VEC_TYPE(ktm::svec3,ivec3)
		DEFINE_VEC_TYPE(ktm::svec4,ivec4)
		DEFINE_VEC_TYPE(ktm::uvec2,uvec2)
		DEFINE_VEC_TYPE(ktm::uvec3,uvec3)
		DEFINE_VEC_TYPE(ktm::uvec4,uvec4)
		DEFINE_VEC_TYPE(ktm::fvec2,vec2)
		DEFINE_VEC_TYPE(ktm::fvec3,vec3)
		DEFINE_VEC_TYPE(ktm::fvec4,vec4)
		DEFINE_VEC_TYPE(ktm::dvec2,dvec2)
		DEFINE_VEC_TYPE(ktm::dvec3,dvec3)
		DEFINE_VEC_TYPE(ktm::dvec4,dvec4)
		using bvec2 = ktm::vec<2,bool>;
		using bvec3 = ktm::vec<3,bool>;
		using bvec4 = ktm::vec<4,bool>;
		DEFINE_VEC_TYPE(bvec2,bvec2)
		DEFINE_VEC_TYPE(bvec3,bvec3)
		DEFINE_VEC_TYPE(bvec4,bvec4)
#undef DEFINE_VEC_TYPE
	};

	template<typename VecDataType>
	std::shared_ptr<VecType> VecType::createVecType()
	{
		auto vecType = std::make_shared<VecType>();
		vecType->name = vecTypes<VecDataType>;
		return vecType;
	}

	struct BaseValue : Value
	{
		std::string value;
		template<typename ValueType>
		static std::string getValue(ValueType value) { return std::to_string(value);}
#define DEFINE_NUMERIC_VALUE(ValueType,ValueOperate) static std::string getValue(ValueType value) { return ValueOperate; }
//...
#undef DEFINE_NUMERIC_VALUE
		std::string parse() override;
	};

	struct VecValue : Value
	{
		std::string value;
		std::shared_ptr<VecType> type;
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
        std::shared_ptr<Value> leftValue;
        std::shared_ptr<Value> rightValue;
		std::string parse() override;
    };

	struct InputVariate : Variate
	{
		size_t index = 0;
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
	};
}
