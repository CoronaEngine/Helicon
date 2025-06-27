#pragma once

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

	template<typename Type>
	struct GPU_WHILE
	{
		GPU_WHILE(VariateProxy<Type>& condition)
		{
			//while begin pattern
		}

		~GPU_WHILE()
		{
			//while end pattern
		}
	};
#define $WHILE(condition) if constexpr (GPU_WHILE gpuWhileD5Hj7K3nP9rT2vX6cB8yN1mQ4zR0sF9(condition);true)

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