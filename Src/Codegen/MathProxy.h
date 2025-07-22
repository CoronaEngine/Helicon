#pragma once
#include <Codegen/VariateProxy.h>

namespace EmbeddedShader
{
    template<typename T>
    struct Vec2Proxy
    {
        template<typename Type>
        friend struct VariateProxy;

        using value_type = T;
        static constexpr uint32_t dimension = 2;
        VariateProxy<T> x;
        VariateProxy<T> y;
    private:
        std::shared_ptr<Ast::Value> parent;
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

    template<size_t N,typename T>
    struct VecProxy
    {

    };

    template<typename T>
    struct VecProxy<2,T>
    {
        using proxy_type = Vec2Proxy<T>;
    };

    template<typename T>
    struct VecProxy<3,T>
    {
        using proxy_type = Vec3Proxy<T>;
    };

    template<typename T>
    struct VecProxy<4,T>
    {
        using proxy_type = Vec4Proxy<T>;
    };

    template<typename T> requires ktm::is_vector_v<T>
    struct VecProxyMap
    {
        using proxy_type = typename VecProxy<ktm::vec_traits_len<T>,ktm::vec_traits_base_t<T>>::proxy_type;
    };
}