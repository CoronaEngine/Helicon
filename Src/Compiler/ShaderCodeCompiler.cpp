
#include "ShaderCodeCompiler.h"

#include <slang-com-helper.h>
#include <slang-com-ptr.h>
#include <slang.h>

#include <Codegen/AST/Parser.hpp>

#include "ShaderHardcodeManager.h"
#include "ShaderLanguageConverter.h"
namespace EmbeddedShader
{
    std::string enumToString(ShaderLanguage language) {
        switch (language)
        {
            case ShaderLanguage::GLSL:
                return "GLSL";
            case ShaderLanguage::HLSL:
                return "HLSL";
            case ShaderLanguage::SpirV:
                return "SpirV";
            case ShaderLanguage::Slang:
                return "Slang";
            default:break;
        }
        return "Unknown";
    }

    std::string enumToString(ShaderStage stage)
    {
        switch (stage)
        {
            case ShaderStage::VertexShader:
                return "VertexShader";
            case ShaderStage::FragmentShader:
                return "FragmentShader";
            case ShaderStage::ComputeShader:
                return "ComputeShader";
            default:break;
        }
        return "Unknown";
    }

    ShaderCodeCompiler::ShaderCodeCompiler(const std::string &shaderCode, ShaderStage inputStage, ShaderLanguage language, const std::source_location &sourceLocation)
    {
        sourceLocationStr = ShaderHardcodeManager::getSourceLocationString(sourceLocation);
        stage = enumToString(inputStage);
        compile(shaderCode,inputStage,language);
    }

    ShaderCodeModule ShaderCodeCompiler::getShaderCode(ShaderLanguage language, bool bindless) const
    {
        std::string bindlessStr = bindless ? "_Bindless" : "";
        ShaderCodeModule result;
        result.shaderCode = std::get<1>(ShaderHardcodeManager::getHardcodeShader(stage, ShaderHardcodeManager::getItemName(sourceLocationStr, enumToString(language) + bindlessStr)));
        result.shaderResources = std::get<0>(ShaderHardcodeManager::getHardcodeShader(stage, ShaderHardcodeManager::getItemName(sourceLocationStr, "Reflection" + bindlessStr)));
        return result;
    }

    void ShaderCodeCompiler::compile(const std::string& shaderCode, ShaderStage inputStage, ShaderLanguage language) const
    {
#if CABBAGE_ENGINE_DEBUG
        std::string bindlessStr = EmbeddedShader::Ast::Parser::getBindless() ? "_Bindless" : "";
        std::vector<uint32_t> codeSpirV = {};
#ifdef WIN32
        std::vector<uint32_t> codeDXIL = {};
        bool bindless = EmbeddedShader::Ast::Parser::getBindless();
        std::vector<uint32_t> codeDXBC = {};
#endif
        std::string codeGLSL;
        std::string codeHLSL;
        std::string codeSlang;
        Slang::ComPtr<slang::IComponentType> program;

        switch (language)
        {
            case ShaderLanguage::Slang:
            {
                codeSlang = shaderCode;
                // codeSpirV = ShaderLanguageConverter::slangSpirvCompiler(codeSlang, program);
                // codeGLSL = ShaderLanguageConverter::slangCompiler(codeSlang,ShaderLanguage::GLSL,program);
                // codeHLSL = ShaderLanguageConverter::slangCompiler(codeSlang,ShaderLanguage::HLSL,program);
                std::vector<std::string> outputs;
                program = ShaderLanguageConverter::slangCompiler(codeSlang,true,{ShaderLanguage::GLSL,ShaderLanguage::HLSL},codeSpirV,outputs);
                auto layout = program->getLayout();
                codeGLSL = outputs[0];
                codeHLSL = outputs[1];
#ifdef WIN32
                codeDXIL = ShaderLanguageConverter::dxilCompiler(codeHLSL, inputStage);
                if (!bindless)
                    codeDXBC = ShaderLanguageConverter::dxbcCompiler(codeHLSL, inputStage);
#endif
                break;
            }
            case ShaderLanguage::GLSL:
                codeGLSL = shaderCode;
                codeSpirV = ShaderLanguageConverter::glslangSpirvCompiler(codeGLSL, language, inputStage);
                codeGLSL = ShaderLanguageConverter::spirvCrossConverter(codeSpirV, ShaderLanguage::GLSL);
                codeHLSL = ShaderLanguageConverter::spirvCrossConverter(codeSpirV, ShaderLanguage::HLSL);
#ifdef WIN32
                // codeDXIL = ShaderLanguageConverter::dxilCompiler(codeHLSL, inputStage);
                // if (!bindless)
                //     codeDXBC = ShaderLanguageConverter::dxbcCompiler(codeHLSL, inputStage);
#endif
                break;
            case ShaderLanguage::HLSL:
                codeHLSL = shaderCode;
                codeSpirV = ShaderLanguageConverter::glslangSpirvCompiler(codeHLSL, language, inputStage);
                codeGLSL = ShaderLanguageConverter::spirvCrossConverter(codeSpirV, ShaderLanguage::GLSL);
                codeHLSL = ShaderLanguageConverter::spirvCrossConverter(codeSpirV, ShaderLanguage::HLSL);
#ifdef WIN32
                codeDXIL = ShaderLanguageConverter::dxilCompiler(codeHLSL, inputStage);
                if (!bindless)
                    codeDXBC = ShaderLanguageConverter::dxbcCompiler(codeHLSL, inputStage);
#endif
                break;
                //case ShaderLanguage::SpirV:
                //    codeSpirV = shaderCode;
                //    codeGLSL = ShaderLanguageConverter::spirvCrossConverter(codeSpirV, ShaderLanguage::GLSL);
                //    codeHLSL = ShaderLanguageConverter::spirvCrossConverter(codeSpirV, ShaderLanguage::HLSL);
                //    break;
            default:
                break;
        }

        // ShaderHardcodeManager::hardcodeShaderCode(codeSpirV, ShaderLanguage::SpirV, inputStage, sourceLocation);
        // ShaderHardcodeManager::hardcodeShaderCode(codeGLSL, ShaderLanguage::GLSL, inputStage, sourceLocation);
        // ShaderHardcodeManager::hardcodeShaderCode(codeHLSL, ShaderLanguage::HLSL, inputStage, sourceLocation);
        // ShaderHardcodeManager::hardcodeShaderCode(codeSlang, ShaderLanguage::Slang, inputStage, sourceLocation);

        auto shaderResource = ShaderLanguageConverter::spirvCrossReflectedBindInfo(codeSpirV, ShaderLanguage::HLSL);
        ShaderHardcodeManager::addTarget(shaderResource, stage, ShaderHardcodeManager::getItemName(sourceLocationStr, "Reflection" + bindlessStr));
        ShaderHardcodeManager::addTarget(codeSpirV, stage, ShaderHardcodeManager::getItemName(sourceLocationStr, "SpirV" + bindlessStr));
        ShaderHardcodeManager::addTarget(codeGLSL, stage, ShaderHardcodeManager::getItemName(sourceLocationStr, "GLSL" + bindlessStr));
        ShaderHardcodeManager::addTarget(codeHLSL, stage, ShaderHardcodeManager::getItemName(sourceLocationStr, "HLSL" + bindlessStr));
        ShaderHardcodeManager::addTarget(codeSlang, stage, ShaderHardcodeManager::getItemName(sourceLocationStr, "Slang" + bindlessStr));
#ifdef WIN32
        ShaderHardcodeManager::addTarget(codeDXIL, stage, ShaderHardcodeManager::getItemName(sourceLocationStr, "DXIL" + bindlessStr));
        if (!bindless)
            ShaderHardcodeManager::addTarget(codeDXBC, stage, ShaderHardcodeManager::getItemName(sourceLocationStr, "DXBC"));
#endif
#endif
    }
}