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
#define $IF(condition) if(GPU_IF gpuIfD5Hj7K3nP9rT2vX6cB8yN1mQ4zR0sF9(condition);true)


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
#define $ELIF(condition) if(GPU_ELSEIF gpuElseIfQ7Jk3P9mR2vX5nB8tW4yL6cZ1dG0sF9(condition);true)


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
#define $ELSE if(GPU_ELSE gpuElse3Tg8Hp2K6nQ9rV4xY7wB1mZ5cF0sD9;true)

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
#define $WHILE(condition) if(GPU_WHILE gpuWhileD5Hj7K3nP9rT2vX6cB8yN1mQ4zR0sF9(condition);true)
}