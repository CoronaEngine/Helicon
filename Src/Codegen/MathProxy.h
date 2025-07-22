#pragma once
#include <Codegen/VariateProxy.h>

namespace EmbeddedShader
{
    template<typename T>
    struct Vec2Proxy
    {
        using value_type = T;
        static constexpr uint32_t dimension = 2;
        VariateProxy<T> x;
        VariateProxy<T> y;
    };

    template<typename T>
    struct Vec3Proxy : Vec2Proxy<T>
    {
        static constexpr uint32_t dimension = 3;
        VariateProxy<T> z;
    };

    template<typename T>
    struct Vec4Proxy : Vec3Proxy<T>
    {
        static constexpr uint32_t dimension = 4;
        VariateProxy<T> w;
    };

    template<typename T>
    struct IsVecProxy
    {
        static constexpr bool value = false;
    };

    template<typename T>
    struct IsVecProxy<Vec2Proxy<T>>
    {
        static constexpr bool value = true;
    };

    template<typename T>
    struct IsVecProxy<Vec3Proxy<T>>
    {
        static constexpr bool value = true;
    };

    template<typename T>
    struct IsVecProxy<Vec4Proxy<T>>
    {
        static constexpr bool value = true;
    };

    template<typename T> requires IsVecProxy<T>::value
    struct VecProxyMap
    {

    };
}