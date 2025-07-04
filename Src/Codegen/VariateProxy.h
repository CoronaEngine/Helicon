#pragma once

#include "boost/pfr.hpp"
#include <sstream>
#include <regex>
#include <type_traits>
#include <cassert>
#include <unordered_map>
#include <string>
#include <tuple>
#include <ktm/ktm.h>
#include <ktm/type/vec.h>


namespace EmbeddedShader
{
	template<typename T>
	concept is_mathematical = requires(T a)
	{
		a = a + a;
		a = a - a;
	};

	template<typename Type>
	struct VariateProxy
	{
	public:
		VariateProxy() requires (std::is_class<Type>::value&& std::is_aggregate<Type>::value && !is_mathematical<Type>)
		{
		}

		VariateProxy(const Type& value) requires is_mathematical<Type>&& std::is_fundamental<Type>::value
		{
		}


		VariateProxy(const Type& value) requires (is_mathematical<Type> && !std::is_fundamental<Type>::value)
		{
		}


		VariateProxy(const Type& value) requires (std::is_class<Type>::value&& std::is_aggregate<Type>::value && !is_mathematical<Type>)
		{
			auto lammdaReflect = [&](auto& structMember)
				{
				};

			boost::pfr::for_each_field(value, lammdaReflect);
		}

		VariateProxy(const std::initializer_list<Type>& value)
		{
		}

		VariateProxy(const VariateProxy<Type>& value)
		{
		}

		~VariateProxy()
		{
		}

		VariateProxy& operator[](int input)
		{
			return *(new VariateProxy());
		}

		Type* operator->()
		{
			return value;
		}

		VariateProxy& operator=(const VariateProxy& rhs)
		{
			return *this;
		}

		VariateProxy& operator++()
		{
			return *this;
		}

		VariateProxy& operator--()
		{
			return *this;
		}

		VariateProxy& operator++(int)
		{
			return *this;
		}

		VariateProxy& operator--(int)
		{
			return *this;
		}

		VariateProxy& operator+(const Type& rhs)
		{
			return *this;
		}

		VariateProxy& operator-(const Type& rhs)
		{
			return *this;
		}

		VariateProxy& operator*(const Type& rhs)
		{
			return *this;
		}

		VariateProxy& operator/(const Type& rhs)
		{
			return *this;
		}

		VariateProxy& operator%(const Type& rhs)
		{
			return *this;
		}

		VariateProxy& operator!()
		{
			return *this;
		}

		VariateProxy& operator||(const VariateProxy& rhs)
		{
			return *this;
		}

		VariateProxy& operator&&(const VariateProxy& rhs)
		{
			return *this;
		}

		VariateProxy& operator~()
		{
			return *this;
		}

		VariateProxy& operator&(const VariateProxy& rhs)
		{
			return *this;
		}

		VariateProxy& operator|(const VariateProxy& rhs)
		{
			return *this;
		}

		VariateProxy& operator^(const VariateProxy& rhs)
		{
			return *this;
		}

		VariateProxy& operator<<(const VariateProxy& rhs)
		{
			return *this;
		}

		VariateProxy& operator>>(const VariateProxy& rhs)
		{
			return *this;
		}

		VariateProxy& operator+=(const VariateProxy& rhs)
		{
			return *this;
		}

		VariateProxy& operator-=(const VariateProxy& rhs)
		{
			return *this;
		}

		VariateProxy& operator*=(const VariateProxy& rhs)
		{
			return *this;
		}

		VariateProxy& operator/=(const VariateProxy& rhs)
		{
			return *this;
		}

		VariateProxy& operator%=(const VariateProxy& rhs)
		{
			return *this;
		}

		VariateProxy& operator&=(const VariateProxy& rhs)
		{
			return *this;
		}

		VariateProxy& operator|=(const VariateProxy& rhs)
		{
			return *this;
		}

		VariateProxy& operator^=(const VariateProxy& rhs)
		{
			return *this;
		}

		VariateProxy& operator>>=(const VariateProxy& rhs)
		{
			return *this;
		}

		VariateProxy& operator<<=(const VariateProxy& rhs)
		{
			return *this;
		}
		
		VariateProxy<bool>& operator>(const VariateProxy& rhs)
		{
			return *(new VariateProxy<bool>(true));
		}

		VariateProxy<bool>& operator>=(const VariateProxy& rhs)
		{
			return *(new VariateProxy<bool>(true));
		}

		VariateProxy<bool>& operator<(const VariateProxy& rhs)
		{
			return *(new VariateProxy<bool>(true));
		}

		VariateProxy<bool>& operator<=(const VariateProxy& rhs)
		{
			return *(new VariateProxy<bool>(true));
		}

		VariateProxy<bool>& operator!=(const VariateProxy& rhs)
		{
			return *(new VariateProxy<bool>(true));
		}

		VariateProxy<bool>& operator==(const VariateProxy& rhs)
		{
			return *(new VariateProxy<bool>(true));
		}


		VariateProxy& operator+() { return *(new VariateProxy()); }
		VariateProxy& operator-() { return *(new VariateProxy()); }
		VariateProxy& operator!() { return *(new VariateProxy()); }
		VariateProxy& operator~() { return *(new VariateProxy()); }

		VariateProxy& operator+(const VariateProxy& rhs) { return *(new VariateProxy()); }
		VariateProxy& operator-(const VariateProxy& rhs) { return *(new VariateProxy()); }
		VariateProxy& operator*(const VariateProxy& rhs) { return *(new VariateProxy()); }
		VariateProxy& operator/(const VariateProxy& rhs) { return *(new VariateProxy()); }
		VariateProxy& operator%(const VariateProxy& rhs) { return *(new VariateProxy()); }
		VariateProxy& operator||(const VariateProxy& rhs) { return *(new VariateProxy()); }
		VariateProxy& operator&&(const VariateProxy& rhs) { return *(new VariateProxy()); }
		VariateProxy& operator&(const VariateProxy& rhs) { return *(new VariateProxy()); }
		VariateProxy& operator|(const VariateProxy& rhs) { return *(new VariateProxy()); }
		VariateProxy& operator^(const VariateProxy& rhs) { return *(new VariateProxy()); }
		VariateProxy& operator<<(const VariateProxy& rhs) { return *(new VariateProxy()); }
		VariateProxy& operator>>(const VariateProxy& rhs) { return *(new VariateProxy()); }
		VariateProxy& operator+=(const VariateProxy& rhs) { return *(new VariateProxy()); }
		VariateProxy& operator-=(const VariateProxy& rhs) { return *(new VariateProxy()); }
		VariateProxy& operator*=(const VariateProxy& rhs) { return *(new VariateProxy()); }
		VariateProxy& operator/=(const VariateProxy& rhs) { return *(new VariateProxy()); }
		VariateProxy& operator%=(const VariateProxy& rhs) { return *(new VariateProxy()); }
		VariateProxy& operator&=(const VariateProxy& rhs) { return *(new VariateProxy()); }
		VariateProxy& operator|=(const VariateProxy& rhs) { return *(new VariateProxy()); }
		VariateProxy& operator^=(const VariateProxy& rhs) { return *(new VariateProxy()); }
		VariateProxy& operator>>=(const VariateProxy& rhs) { return *(new VariateProxy()); }
		VariateProxy& operator<<=(const VariateProxy& rhs) { return *(new VariateProxy()); }

		VariateProxy<bool>& operator>(const VariateProxy& rhs) { return *(new VariateProxy<bool>(true)); }
		VariateProxy<bool>& operator>=(const VariateProxy& rhs) { return *(new VariateProxy<bool>(true)); }
		VariateProxy<bool>& operator<(const VariateProxy& rhs) { return *(new VariateProxy<bool>(true)); }
		VariateProxy<bool>& operator<=(const VariateProxy& rhs) { return *(new VariateProxy<bool>(true)); }
		VariateProxy<bool>& operator!=(const VariateProxy& rhs) { return *(new VariateProxy<bool>(true)); }
		VariateProxy<bool>& operator==(const VariateProxy& rhs) { return *(new VariateProxy<bool>(true)); }    


	private:
		Type* value;
	};
}
