#pragma once
#include <functional>
#include <Codegen/VariateProxy.h>

namespace EmbeddedShader
{
	class ParseHelper final
	{
	public:
		template<typename ReturnType> requires std::is_same_v<ReturnType, void>
		static void callLambda(std::function<ReturnType()> f)
		{
			instance.isInShaderCodeLambda = true;
			f();
			instance.isInShaderCodeLambda = false;
		}

		template<typename ReturnType> requires !std::is_same_v<ReturnType, void>
		static auto callLambda(std::function<ReturnType()> f)
		{
			instance.isInShaderCodeLambda = true;
			auto result = f();
			instance.isInShaderCodeLambda = false;
			return result;
		}

		template<typename ReturnType,typename ParamType> requires std::is_same_v<ReturnType, void>
		static auto callLambda(std::function<ReturnType(ParamType)> f, const ParamType& param)
		{
			instance.isInShaderCodeLambda = true;
			f(param);
			instance.isInShaderCodeLambda = false;
		}

		template<typename ReturnType,typename ParamType> requires !std::is_same_v<ReturnType, void>
		static auto callLambda(std::function<ReturnType(ParamType)> f, const ParamType& param)
		{
			instance.isInShaderCodeLambda = true;
			auto result = f(param);
			instance.isInShaderCodeLambda = false;
			return result;
		}

		template<typename ReturnType, typename... ParamTypes> requires std::is_same_v<ReturnType, void>
		static auto callLambda(std::function<ReturnType(ParamTypes...)> f,std::tuple<ParamTypes...> params)
		{
			instance.isInShaderCodeLambda = true;
			std::apply(f, params);
			instance.isInShaderCodeLambda = false;
		}

		template<typename ReturnType, typename... ParamTypes> requires !std::is_same_v<ReturnType, void>
		static auto callLambda(std::function<ReturnType(ParamTypes...)> f,std::tuple<ParamTypes...> params)
		{
			instance.isInShaderCodeLambda = true;
			auto result = std::apply(f, params);
			instance.isInShaderCodeLambda = false;
			return result;
		}

		template<typename ReturnType,typename... ParamTypes>
		static std::tuple<ParamTypes...> createParamTuple(const std::function<ReturnType(ParamTypes...)>& f)
		{
			instance.isInInputParameter = true;
			auto tuple = std::tuple<ParamTypes...>();
			instance.isInInputParameter = false;
			return tuple;
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
		bool isInInputParameter = false;
		bool isInShaderCodeLambda = false;
		static thread_local ParseHelper instance;

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

	thread_local ParseHelper ParseHelper::instance;
}
