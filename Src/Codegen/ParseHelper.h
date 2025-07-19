#pragma once
#include <functional>
#include <Codegen/VariateProxy.h>

namespace EmbeddedShader
{
	class ParseHelper
	{
	public:
		template<typename ReturnType,typename... ParamTypes>
		std::tuple<ParamTypes...> createParamTuple(const std::function<ReturnType(ParamTypes...)>& f)
		{
			return std::tuple<ParamTypes...>();
		}

		template<typename ReturnType,typename... ParamTypes>
		static constexpr bool hasReturnValue(const std::function<ReturnType(ParamTypes...)>& f)
		{
			return !std::is_same_v<ReturnType, void>;
		}

		template<typename ReturnType1,typename ReturnType2,typename... ParamTypes1,typename... ParamTypes2>
		static constexpr bool isMatchInputAndOutput(const std::function<ReturnType1(ParamTypes1...)>& fOutput,const std::function<ReturnType2(ParamTypes2...)>& fInput)
		{
			//1.没有输入输出
			//2. 输入和输出类型相同
			//note:这里的if constexpr不能省略，因为std::is_same_v<ReturnType1,ParamTypes2...>这条代码必须要求sizeof...(ParamTypes2) == 1
			if constexpr (std::is_same_v<ReturnType1, void> && sizeof...(ParamTypes2) == 0)
				return true;
			else if constexpr (!std::is_same_v<ReturnType1, void> && sizeof...(ParamTypes2) == 1 && std::is_same_v<ReturnType1,ParamTypes2...>)
				return true;
			else
				return false;
		}

		template<typename T,typename... ParamTypes>
		static constexpr bool isReturnProxy(const std::function<T(ParamTypes...)>& f)
		{
			return sIsReturnProxy<std::remove_cvref_t<decltype(f)>>::value;
		}
	private:
		template<typename T>
		struct sIsReturnProxy
		{
			static constexpr bool value = false;
		};

		template<typename T,typename... ParamTypes>
		struct sIsReturnProxy<std::function<VariateProxy<T>(ParamTypes...)>>
		{
			static constexpr bool value = true;
		};
	};
}
