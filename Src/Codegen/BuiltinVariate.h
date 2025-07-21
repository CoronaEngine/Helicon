#pragma once
#include <Codegen/VariateProxy.h>

namespace EmbeddedShader
{
    inline VariateProxy<ktm::fvec4> position()
    {
        return {Ast::AST::getPositionOutput()};
    }
}