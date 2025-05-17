#pragma once

#include "VariateProxy.h"

namespace EmbeddedShader
{

	template<typename Type>
	struct GPU_IF
	{
		GPU_IF(VariateProxy<Type>& condition)
		{
		}
		void operator % (std::function<void()> func)
		{
		}
	};
#define $IF(...) ;GPU_IF(__VA_ARGS__) % [&]() noexcept -> void


	template<typename Type>
	struct GPU_ELSEIF
	{
		GPU_ELSEIF(VariateProxy<Type>& condition)
		{
		}
		void operator % (std::function<void()> func)
		{
		}
	};
#define $ELIF(...) ;GPU_ELSEIF(__VA_ARGS__) % [&]() noexcept -> void


	struct GPU_ELSE
	{
		GPU_ELSE()
		{
		}
		void operator % (std::function<void()> func)
		{
		}
	};
#define $ELSE ;GPU_ELSE() % [&]() noexcept -> void

}