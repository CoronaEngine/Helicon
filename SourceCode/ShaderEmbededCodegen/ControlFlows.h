//#pragma once
//
//#include"ast.h"
//
//
//namespace MathLib
//{
//	class GPU_IF
//	{
//	private:
//		CSTNode* innerCondition;
//
//	public:
//
//		GPU_IF(CSTNode* condition)
//			: innerCondition(condition)
//		{
//		}
//
//		void operator % (std::function<void()> func)
//		{
//			//MathLib::runtimeAST.addNode(OperatorNodeType::IF, innerCondition);
//			//func();
//			//MathLib::runtimeAST.addNode(OperatorNodeType::CLOSE_SCOPE, nullptr);
//		}
//
//	};
//#define $IF(...) MathLib::GPU_IF(__VA_ARGS__) % [&]() noexcept -> void
//
//
//	class GPU_ELSEIF
//	{
//	private:
//		CSTNode* innerCondition;
//
//	public:
//
//		GPU_ELSEIF(CSTNode* condition) :innerCondition(condition)
//		{
//		}
//
//		void operator % (std::function<void()> func)
//		{
//			//MathLib::runtimeAST.addNode(OperatorNodeType::IF, innerCondition);
//			//func();
//			//MathLib::runtimeAST.addNode(OperatorNodeType::CLOSE_SCOPE, nullptr);
//		}
//	};
//#define $ELIF(...) ;MathLib::GPU_ELSEIF(__VA_ARGS__) % [&]() noexcept -> void
//
//
//	class GPU_ELSE
//	{
//	private:
//		//CSTNode* innerCondition;
//
//	public:
//		GPU_ELSE()
//		{
//
//		}
//
//		void operator % (std::function<void()> func)
//		{
//			//MathLib::runtimeAST.addNode(OperatorNodeType::IF, innerCondition);
//			//func();
//			//MathLib::runtimeAST.addNode(OperatorNodeType::CLOSE_SCOPE, nullptr);
//		}
//	};
//#define $ELSE ;MathLib::GPU_ELSE() % [&]() noexcept -> void
//
//};