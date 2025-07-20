#pragma once
#include <Codegen/ParseHelper.h>
#include <Codegen/VariateProxy.h>

namespace EmbeddedShader
{
	namespace Impl
	{
		template<typename T>
		struct IsReturnProxy
		{
			static constexpr bool value = false;
		};

		template<typename T, typename... ParamTypes>
		struct IsReturnProxy<std::function<VariateProxy<T>(ParamTypes...)>>
		{
			static constexpr bool value = true;
		};
	}

	template<typename T, typename ... ParamTypes>
	constexpr bool ParseHelper::isReturnProxy(const std::function<T(ParamTypes...)>& f)
	{
		return Impl::IsReturnProxy<std::remove_cvref_t<decltype(f)>>::value;
	}
}
