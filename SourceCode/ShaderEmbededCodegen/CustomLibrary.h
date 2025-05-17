#pragma once

#include <ktm/ktm.h>
#include "VariateProxy.h"

namespace EmbeddedShader
{
	template<typename Type>
	VariateProxy<Type> max(VariateProxy<Type> a, VariateProxy<Type> b)
	{
		return a;
	}

	template<typename Type>
	VariateProxy<Type> min(VariateProxy<Type> a, VariateProxy<Type> b)
	{
		return a;
	}
}
