#pragma once
#include <Codegen/VariateProxy.h>

namespace EmbeddedShader
{
    template<typename T> requires ktm::is_vector_v<T>
    struct VecProxyMap;

    template<typename Type>
    struct SwizzleProxy : VariateProxy<Type>
    {
        using base_type = VariateProxy<Type>;
        using base_type::operator=;
        typename VecProxyMap<Type>::proxy_type operator->() requires (ktm::is_vector_v<Type>) = delete;

        SwizzleProxy(std::shared_ptr<Ast::Value> parent, std::string name) : base_type(Ast::AST::access(std::move(parent),std::move(name),Ast::AST::createType<Type>()))
        {

        }
    };

#define SWIZZLE_DECLARE(type,name) SwizzleProxy<type> name();
#define SWIZZLE_DEFINED(className,type,name) template<typename T> SwizzleProxy<type> className<T>::name() { return {this->parent,#name}; }

    template<typename T>
    struct Vec2Proxy
    {
        template<typename Type>
        friend struct VariateProxy;

        using value_type = T;
        static constexpr uint32_t dimension = 2;
        VariateProxy<T> x;
        VariateProxy<T> y;

        SWIZZLE_DECLARE(ktm::fvec2, xy)
        SWIZZLE_DECLARE(ktm::fvec2, yx)
    protected:
        std::shared_ptr<Ast::Value> parent;
    };

    SWIZZLE_DEFINED(Vec2Proxy,ktm::fvec2,xy)
    SWIZZLE_DEFINED(Vec2Proxy,ktm::fvec2,yx)

    template<typename T>
    struct Vec3Proxy : Vec2Proxy<T>
    {
        static constexpr uint32_t dimension = 3;
        VariateProxy<T> z;
        SWIZZLE_DECLARE(ktm::fvec2, xz)
        SWIZZLE_DECLARE(ktm::fvec2, yz)
        SWIZZLE_DECLARE(ktm::fvec2, zx)
        SWIZZLE_DECLARE(ktm::fvec2, zy)

        SWIZZLE_DECLARE(ktm::fvec3, xyz)
        SWIZZLE_DECLARE(ktm::fvec3, xzy)
        SWIZZLE_DECLARE(ktm::fvec3, yxz)
        SWIZZLE_DECLARE(ktm::fvec3, yzx)
        SWIZZLE_DECLARE(ktm::fvec3, zxy)
        SWIZZLE_DECLARE(ktm::fvec3, zyx)
    };

    SWIZZLE_DEFINED(Vec3Proxy,ktm::fvec2, xz)
    SWIZZLE_DEFINED(Vec3Proxy,ktm::fvec2, yz)
    SWIZZLE_DEFINED(Vec3Proxy,ktm::fvec2, zx)
    SWIZZLE_DEFINED(Vec3Proxy,ktm::fvec2, zy)

    SWIZZLE_DEFINED(Vec3Proxy,ktm::fvec3, xyz)
    SWIZZLE_DEFINED(Vec3Proxy,ktm::fvec3, xzy)
    SWIZZLE_DEFINED(Vec3Proxy,ktm::fvec3, yxz)
    SWIZZLE_DEFINED(Vec3Proxy,ktm::fvec3, yzx)
    SWIZZLE_DEFINED(Vec3Proxy,ktm::fvec3, zxy)
    SWIZZLE_DEFINED(Vec3Proxy,ktm::fvec3, zyx)

    template<typename T>
    struct Vec4Proxy : Vec3Proxy<T>
    {
        static constexpr uint32_t dimension = 4;
        VariateProxy<T> w;

        SWIZZLE_DECLARE(ktm::fvec2, xw)
        SWIZZLE_DECLARE(ktm::fvec2, yw)
        SWIZZLE_DECLARE(ktm::fvec2, zw)
        SWIZZLE_DECLARE(ktm::fvec2, wx)
        SWIZZLE_DECLARE(ktm::fvec2, wy)
        SWIZZLE_DECLARE(ktm::fvec2, wz)

        SWIZZLE_DECLARE(ktm::fvec3, xyw)
        SWIZZLE_DECLARE(ktm::fvec3, xwy)
        SWIZZLE_DECLARE(ktm::fvec3, xzw)
        SWIZZLE_DECLARE(ktm::fvec3, xwz)
        SWIZZLE_DECLARE(ktm::fvec3, yxw)
        SWIZZLE_DECLARE(ktm::fvec3, ywx)
        SWIZZLE_DECLARE(ktm::fvec3, yzw)
        SWIZZLE_DECLARE(ktm::fvec3, ywz)
        SWIZZLE_DECLARE(ktm::fvec3, zxw)
        SWIZZLE_DECLARE(ktm::fvec3, zwx)
        SWIZZLE_DECLARE(ktm::fvec3, zyw)
        SWIZZLE_DECLARE(ktm::fvec3, zwy)

        SWIZZLE_DECLARE(ktm::fvec4, xyzw)
        SWIZZLE_DECLARE(ktm::fvec4, xywz)
        SWIZZLE_DECLARE(ktm::fvec4, xzyw)
        SWIZZLE_DECLARE(ktm::fvec4, xzwy)
        SWIZZLE_DECLARE(ktm::fvec4, xwyz)
        SWIZZLE_DECLARE(ktm::fvec4, xwzy)

        SWIZZLE_DECLARE(ktm::fvec4, yxzw)
        SWIZZLE_DECLARE(ktm::fvec4, yxwz)
        SWIZZLE_DECLARE(ktm::fvec4, yzxw)
        SWIZZLE_DECLARE(ktm::fvec4, yzwx)
        SWIZZLE_DECLARE(ktm::fvec4, ywxz)
        SWIZZLE_DECLARE(ktm::fvec4, ywzx)

        SWIZZLE_DECLARE(ktm::fvec4, zxyw)
        SWIZZLE_DECLARE(ktm::fvec4, zxwy)
        SWIZZLE_DECLARE(ktm::fvec4, zyxw)
        SWIZZLE_DECLARE(ktm::fvec4, zywx)
        SWIZZLE_DECLARE(ktm::fvec4, zwxy)
        SWIZZLE_DECLARE(ktm::fvec4, zwyx)

        SWIZZLE_DECLARE(ktm::fvec4, wxyz)
        SWIZZLE_DECLARE(ktm::fvec4, wxzy)
        SWIZZLE_DECLARE(ktm::fvec4, wyxz)
        SWIZZLE_DECLARE(ktm::fvec4, wyzx)
        SWIZZLE_DECLARE(ktm::fvec4, wzxy)
        SWIZZLE_DECLARE(ktm::fvec4, wzyx)
    };

    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec2, xw)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec2, yw)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec2, zw)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec2, wx)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec2, wy)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec2, wz)

    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec3, xyw)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec3, xwy)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec3, xzw)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec3, xwz)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec3, yxw)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec3, ywx)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec3, yzw)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec3, ywz)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec3, zxw)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec3, zwx)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec3, zyw)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec3, zwy)

    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec4, xyzw)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec4, xywz)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec4, xzyw)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec4, xzwy)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec4, xwyz)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec4, xwzy)

    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec4, yxzw)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec4, yxwz)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec4, yzxw)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec4, yzwx)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec4, ywxz)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec4, ywzx)

    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec4, zxyw)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec4, zxwy)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec4, zyxw)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec4, zywx)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec4, zwxy)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec4, zwyx)

    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec4, wxyz)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec4, wxzy)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec4, wyxz)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec4, wyzx)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec4, wzxy)
    SWIZZLE_DEFINED(Vec4Proxy,ktm::fvec4, wzyx)

#undef SWIZZLE_DECLARE
#undef SWIZZLE_DEFINED

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