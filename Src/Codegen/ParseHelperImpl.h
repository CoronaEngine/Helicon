#pragma once
#include <Codegen/ParseHelper.h>
#include <Codegen/VariateProxy.h>

namespace EmbeddedShader
{
	namespace Impl
	{
		template<typename T>
	   struct sIsReturnProxy
		{
			static constexpr bool value = false;
		};

		template<typename T, typename... ParamTypes>
		struct sIsReturnProxy<std::function<VariateProxy<T>(ParamTypes...)>>
		{
			static constexpr bool value = true;
		};
	}

	template<typename T, typename ... ParamTypes>
	constexpr bool ParseHelper::isReturnProxy(const std::function<T(ParamTypes...)>& f)
	{
		return Impl::sIsReturnProxy<std::remove_cvref_t<decltype(f)>>::value;
	}
}