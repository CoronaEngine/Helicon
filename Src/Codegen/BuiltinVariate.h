#pragma once
#include <Codegen/VariateProxy.h>
#include <Codegen/Generator/SlangGenerator.hpp>

namespace EmbeddedShader
{
    inline VariateProxy<ktm::fvec4> position()
    {
        return VariateProxy<ktm::fvec4>{Ast::AST::getPositionOutput()};
    }

    inline VariateProxy<ktm::uvec3> dispatchThreadID()
    {
        return VariateProxy<ktm::uvec3>{Ast::AST::getDispatchThreadIDInput()};
    }

    inline void numthreads(ktm::uvec3 xyz)
    {
        Generator::SlangGenerator::numthreads = std::move(xyz);
    }

    inline void numthreads(uint32_t x,uint32_t y,uint32_t z)
    {
        numthreads(ktm::uvec3{x,y,z});
    }
}