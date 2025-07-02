#pragma once

#include<boost/pfr.hpp>

#include <boost/preprocessor.hpp>


// ͨ�� FunctionWrapper ģ��
template <typename T>
struct FunctionWrapper;

// �����ͨ��Ա�������ػ�
template <typename R, typename C, typename... Args>
struct FunctionWrapper<R (C::*)(Args...)>
{
    using MemberFunctionPtr = R (C::*)(Args...);
    MemberFunctionPtr func_ptr;

    FunctionWrapper(MemberFunctionPtr ptr)
        : func_ptr(ptr)
    {
        // std::cout << "FunctionWrapper created for member function: " << typeid(R(C::*)(Args...)).name() << std::endl;
    }

    // ������ͨ��Ա������Ҫһ������ʵ��
    R operator()(C *obj, Args... args) const
    {
        return (obj->*func_ptr)(std::forward<Args>(args)...);
    }
};

// ��� const ��Ա�������ػ�
template <typename R, typename C, typename... Args>
struct FunctionWrapper<R (C::*)(Args...) const>
{
    using ConstMemberFunctionPtr = R (C::*)(Args...) const;
    ConstMemberFunctionPtr func_ptr;

    FunctionWrapper(ConstMemberFunctionPtr ptr)
        : func_ptr(ptr)
    {
        // std::cout << "FunctionWrapper created for const member function: " << typeid(R(C::*)(Args...) const).name() << std::endl;
    }

    R operator()(const C *obj, Args... args) const
    {
        return (obj->*func_ptr)(std::forward<Args>(args)...);
    }
};

// ��Ծ�̬��Ա�������ػ�
template <typename R, typename... Args>
struct FunctionWrapper<R (*)(Args...)>
{
    using StaticFunctionPtr = R (*)(Args...);
    StaticFunctionPtr func_ptr;

    FunctionWrapper(StaticFunctionPtr ptr)
        : func_ptr(ptr)
    {
        // std::cout << "FunctionWrapper created for static function: " << typeid(R(*)(Args...)).name() << std::endl;
    }

    // ���þ�̬��Ա��������Ҫ����ʵ��
    R operator()(Args... args) const
    {
        return func_ptr(std::forward<Args>(args)...);
    }
};

#define PFR_REFLECTABLE_MEMBER_FUNCTION_ONE(r, CLASSNAME, MemberFunction) \
    FunctionWrapper<decltype(&CLASSNAME::MemberFunction)> BOOST_PP_CAT(MemberFunction, _ptr){&CLASSNAME::MemberFunction};

#define PFR_REFLECTABLE_MEMBER_FUNCTION(CLASSNAME, ...) \
    BOOST_PP_SEQ_FOR_EACH(PFR_REFLECTABLE_MEMBER_FUNCTION_ONE, CLASSNAME, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))