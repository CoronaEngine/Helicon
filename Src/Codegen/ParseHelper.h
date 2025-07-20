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
			instance.bIsInShaderCodeLambda = true;
			f();
			instance.bIsInShaderCodeLambda = false;
		}

		template<typename ReturnType> requires !std::is_same_v<ReturnType, void>
		static auto callLambda(std::function<ReturnType()> f)
		{
			instance.bIsInShaderCodeLambda = true;
			auto result = f();
			instance.bIsInShaderCodeLambda = false;
			return result;
		}

		template<typename ReturnType,typename ParamType> requires std::is_same_v<ReturnType, void>
		static auto callLambda(std::function<ReturnType(ParamType)> f, ParamType param)
		{
			instance.bIsInShaderCodeLambda = true;
			puts("setting!");
			fflush(stdout);
			f(std::move(param));
			instance.bIsInShaderCodeLambda = false;
		}

		template<typename ReturnType,typename ParamType> requires !std::is_same_v<ReturnType, void>
		static auto callLambda(std::function<ReturnType(ParamType)> f, ParamType param)
		{
			instance.bIsInShaderCodeLambda = true;
			auto result = f(std::move(param));
			instance.bIsInShaderCodeLambda = false;
			return result;
		}

		template<typename ReturnType, typename... ParamTypes> requires std::is_same_v<ReturnType, void>
		static auto callLambda(std::function<ReturnType(ParamTypes...)> f,std::tuple<ParamTypes...> params)
		{
			instance.bIsInShaderCodeLambda = true;
			std::apply(f, std::move(params));
			instance.bIsInShaderCodeLambda = false;
		}

		template<typename ReturnType, typename... ParamTypes> requires !std::is_same_v<ReturnType, void>
		static auto callLambda(std::function<ReturnType(ParamTypes...)> f,std::tuple<ParamTypes...> params)
		{
			instance.bIsInShaderCodeLambda = true;
			auto result = std::apply(f, std::move(params));
			instance.bIsInShaderCodeLambda = false;
			return result;
		}

		template<typename ReturnType,typename... ParamTypes>
		static std::tuple<ParamTypes...> createParamTuple(const std::function<ReturnType(ParamTypes...)>& f)
		{
			instance.bIsInInputParameter = true;
			instance.currentInputIndex = sizeof...(ParamTypes);
			auto tuple = std::tuple<ParamTypes...>();
			instance.bIsInInputParameter = false;
			return tuple;
		}

		template<typename ReturnType,typename ParamType>
		static ParamType createParam(const std::function<ReturnType(ParamType)>& f)
		{
			instance.bIsInInputParameter = true;
			instance.currentInputIndex = 1;
			ParamType param;
			instance.bIsInInputParameter = false;
			return param;
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
			else if constexpr (!std::is_same_v<ReturnType1, void> && sizeof...(ParamTypes2) == 1)
			{
				if constexpr (std::is_same_v<ReturnType1,ParamTypes2...>)
					return true;
			}
			else
				return false;
		}

		template<typename T,typename... ParamTypes>
		static constexpr bool isReturnProxy(const std::function<T(ParamTypes...)>& f);

		static bool isInInputParameter()
		{
			return instance.bIsInInputParameter;
		}

		static bool isInShaderCodeLambda()
		{
			return instance.bIsInShaderCodeLambda;
		}

		static size_t getCurrentInputIndex()
		{
			return --instance.currentInputIndex;
		}
	private:
		bool bIsInInputParameter = false;
		bool bIsInShaderCodeLambda = false;
		size_t currentInputIndex = 0;
		static thread_local ParseHelper instance;
	};

	thread_local ParseHelper ParseHelper::instance;
}
