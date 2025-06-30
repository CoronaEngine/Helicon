#pragma once

#include <stack>

#include "VariateProxy.h"

namespace EmbeddedShader
{

	template<typename Type>
	struct GPU_IF
	{
		GPU_IF(VariateProxy<Type>& condition)
		{
			//if begin pattern
		}

		~GPU_IF()
		{
			//if end pattern
		}
	};
#define $IF(condition) if constexpr (GPU_IF gpuIfD5Hj7K3nP9rT2vX6cB8yN1mQ4zR0sF9(condition);true)


	template<typename Type>
	struct GPU_ELSEIF
	{
		GPU_ELSEIF(VariateProxy<Type>& condition)
		{
			//elseif begin pattern
		}

		~GPU_ELSEIF()
		{
			//elseif end pattern
		}
	};
#define $ELIF(condition) if constexpr (GPU_ELSEIF gpuElseIfQ7Jk3P9mR2vX5nB8tW4yL6cZ1dG0sF9(condition);true)


	struct GPU_ELSE
	{
		GPU_ELSE()
		{
			//else begin pattern
		}

		~GPU_ELSE()
		{
			//else end pattern
		}
	};
#define $ELSE if constexpr (GPU_ELSE gpuElse3Tg8Hp2K6nQ9rV4xY7wB1mZ5cF0sD9;true)

	struct GPU_WHILE_INFO
	{
		bool isDoWhile = false; // 是否为do while循环
		int loopCount = 0; // 循环次数计数
		bool isDoWhileInside = false; // 是否在do while循环内部
		static std::stack<GPU_WHILE_INFO> gpuWhileStack;
	};

	std::stack<GPU_WHILE_INFO> GPU_WHILE_INFO::gpuWhileStack{};

	struct GPU_WHILE
	{
		template<typename Type>
		static bool conditionProcess(VariateProxy<Type> condition)
		{
			auto& gpuWhileStack = GPU_WHILE_INFO::gpuWhileStack;
			if (gpuWhileStack.empty() || gpuWhileStack.top().isDoWhileInside)
			{
				//说明这是一个新的while
				gpuWhileStack.push({});
			}

			auto& top = gpuWhileStack.top();
			if (top.isDoWhile)
			{
				gpuWhileStack.pop();
				/////////////////////do while end/////////////////////
				//xxx
				return false;
			}

			//说明是while
			//while 时，第一次条件为true
			//while 时，第一次条件为false

			++top.loopCount;
			if (top.loopCount == 2)
			{
				gpuWhileStack.pop();
				/////////////////////while end/////////////////////
				return false;
			}
			/////////////////////while begin/////////////////////
			//xxx
			return true;
		}
	};

	struct GPU_DO_WHILE
	{
		GPU_DO_WHILE()
		{
			GPU_WHILE_INFO::gpuWhileStack.push({true, 0, true});
			/////////////////////do while begin/////////////////////
		}

		~GPU_DO_WHILE()
		{
			GPU_WHILE_INFO::gpuWhileStack.top().isDoWhileInside = false;
		}
	};

#define $DO do if constexpr (GPU_DO_WHILE gpuDoWhileL8kM3qW5xG1vY7dR4nP9tS2;true)
#define $WHILE(condition) while (GPU_WHILE::conditionProcess(condition))

	struct GPU_FOR
	{
		static void beginCatchCondition()
		{
            //for begin pattern
        }

		GPU_FOR(const std::function<void()>& condition)
		{
			condition();
		}

		~GPU_FOR()
		{
			//...
		}

		struct BREAK_FLAG_PROCESS
		{
			explicit BREAK_FLAG_PROCESS(bool& breakFlag)
            {
                if (breakFlag)
                {
                    beginCatchCondition();
                    breakFlag = false; // Reset the break flag
                }
            }
		};
	};
#define $FOR(condition) \
	if constexpr (GPU_FOR gpuForL8kM3qW5xG1vY7dR4nP9tS2{[&]{condition;}};true)\
		if constexpr (bool breakFlagJ6hF4rT9mK2zV8cX5bN1pQ3 = true; true)\
			for (condition)\
				if (GPU_FOR::BREAK_FLAG_PROCESS gpuForBreakFlagProcessU7gD2sH5nB9yR4vM8kL3wZ6{breakFlagJ6hF4rT9mK2zV8cX5bN1pQ3}; breakFlagJ6hF4rT9mK2zV8cX5bN1pQ3)
}