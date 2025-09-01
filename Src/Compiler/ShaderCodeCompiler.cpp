
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

    ShaderCodeCompiler::ShaderCodeCompiler(const std::string& shaderCode, ShaderStage inputStage,
        ShaderLanguage language, CompilerOption option, const std::source_location& sourceLocation)
    {
        sourceLocationStr = ShaderHardcodeManager::getSourceLocationString(sourceLocation);
        stage = enumToString(inputStage);
        compile(shaderCode,inputStage,language,option);
    }

    ShaderCodeModule ShaderCodeCompiler::getShaderCode(ShaderLanguage language, bool bindless) const
    {
        std::string bindlessStr = bindless ? "_Bindless" : "";
        ShaderCodeModule result;
        result.shaderCode = std::get<1>(ShaderHardcodeManager::getHardcodeShader(stage, ShaderHardcodeManager::getItemName(sourceLocationStr, enumToString(language) + bindlessStr)));
        result.shaderResources = std::get<0>(ShaderHardcodeManager::getHardcodeShader(stage, ShaderHardcodeManager::getItemName(sourceLocationStr, "Reflection" + bindlessStr)));
        return result;
    }

    void ShaderCodeCompiler::compile(const std::string& shaderCode, ShaderStage inputStage, ShaderLanguage language,
        CompilerOption option) const
    {
#if CABBAGE_ENGINE_DEBUG
        std::string bindlessStr = Ast::Parser::getBindless() ? "_Bindless" : "";
        std::vector<uint32_t> codeSpirV = {};
#ifdef WIN32
        std::vector<uint32_t> codeDXIL = {};
        std::vector<uint32_t> codeDXBC = {};
#endif

        if (Ast::Parser::getBindless())
            option.compileDXBC = false; // DXBC不支持sm6.6 bindless

        if (language != ShaderLanguage::Slang && language != ShaderLanguage::HLSL && !option.compileHLSL)
        {
            //slang可以直接编译到dxil和dxbc，但其他情况需要依赖HLSL，所以如果不需要HLSL就直接跳过
            option.compileDXIL = false;
            option.compileDXBC = false;
        }

        std::string codeGLSL;
        std::string codeHLSL;
        std::string codeSlang;

        switch (language)
        {
            case ShaderLanguage::Slang:
            {
                codeSlang = shaderCode;

                std::vector<std::string> outputs;
                std::vector<std::vector<uint32_t>> binaryOutputs;
                std::vector<ShaderLanguage> binaryLanguages;
                std::vector<ShaderLanguage> languages;
                if (option.compileSpirV)
                    binaryLanguages.push_back(ShaderLanguage::SpirV);
#ifdef WIN32
                if (option.compileDXIL)
                    binaryLanguages.push_back(ShaderLanguage::DXIL);
                if (option.compileDXBC)
                    binaryLanguages.push_back(ShaderLanguage::DXBC);
#endif
                if (option.compileGLSL)
                    languages.push_back(ShaderLanguage::GLSL);
                if (option.compileHLSL)
                    languages.push_back(ShaderLanguage::HLSL);


                ShaderLanguageConverter::slangCompiler(codeSlang, binaryLanguages, languages, binaryOutputs, outputs, true);
                size_t index = 0;
                if (option.compileSpirV)
                    codeSpirV = binaryOutputs[index++];
#ifdef WIN32
                if (option.compileDXIL)
                    codeDXIL = binaryOutputs[index++];
                if (option.compileDXBC)
                    codeDXBC = binaryOutputs[index++];

                // if (option.compileDXIL)
                //     codeDXIL = ShaderLanguageConverter::dxilCompiler(codeHLSL, inputStage);
                // if (!bindless && option.compileDXBC)
                //     codeDXBC = ShaderLanguageConverter::dxbcCompiler(codeHLSL, inputStage);
#endif

                index = 0;
                if (option.compileGLSL)
                    codeGLSL = outputs[index++];
                if (option.compileHLSL)
                    codeHLSL = outputs[index++];
                break;
            }
            case ShaderLanguage::GLSL:
                codeGLSL = shaderCode;
                if (option.compileSpirV)
                    codeSpirV = ShaderLanguageConverter::glslangSpirvCompiler(codeGLSL, language, inputStage);
                if (option.compileGLSL)
                    codeGLSL = ShaderLanguageConverter::spirvCrossConverter(codeSpirV, ShaderLanguage::GLSL);
                if (option.compileHLSL)
                    codeHLSL = ShaderLanguageConverter::spirvCrossConverter(codeSpirV, ShaderLanguage::HLSL);
#ifdef WIN32
                // codeDXIL = ShaderLanguageConverter::dxilCompiler(codeHLSL, inputStage);
                // if (!bindless)
                //     codeDXBC = ShaderLanguageConverter::dxbcCompiler(codeHLSL, inputStage);
#endif
                break;
            case ShaderLanguage::HLSL:
                codeHLSL = shaderCode;
                if (option.compileSpirV)
                    codeSpirV = ShaderLanguageConverter::glslangSpirvCompiler(codeHLSL, language, inputStage);
                if (option.compileGLSL)
                    codeGLSL = ShaderLanguageConverter::spirvCrossConverter(codeSpirV, ShaderLanguage::GLSL);
                if (option.compileHLSL)
                    codeHLSL = ShaderLanguageConverter::spirvCrossConverter(codeSpirV, ShaderLanguage::HLSL);
#ifdef WIN32
                if (option.compileDXIL)
                    codeDXIL = ShaderLanguageConverter::dxilCompiler(codeHLSL, inputStage);
                if (option.compileDXBC)
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

        if (option.compileSpirV)
            ShaderHardcodeManager::addTarget(codeSpirV, stage, ShaderHardcodeManager::getItemName(sourceLocationStr, "SpirV" + bindlessStr));
        if (language == ShaderLanguage::GLSL || option.compileGLSL)
            ShaderHardcodeManager::addTarget(codeGLSL, stage, ShaderHardcodeManager::getItemName(sourceLocationStr, "GLSL" + bindlessStr));
        if (language == ShaderLanguage::HLSL || option.compileDXIL)
            ShaderHardcodeManager::addTarget(codeHLSL, stage, ShaderHardcodeManager::getItemName(sourceLocationStr, "HLSL" + bindlessStr));
        if (language == ShaderLanguage::Slang)
            ShaderHardcodeManager::addTarget(codeSlang, stage, ShaderHardcodeManager::getItemName(sourceLocationStr, "Slang" + bindlessStr));
#ifdef WIN32
        if (option.compileDXIL)
            ShaderHardcodeManager::addTarget(codeDXIL, stage, ShaderHardcodeManager::getItemName(sourceLocationStr, "DXIL" + bindlessStr));
        if (option.compileDXBC)
            ShaderHardcodeManager::addTarget(codeDXBC, stage, ShaderHardcodeManager::getItemName(sourceLocationStr, "DXBC"));
#endif
#endif
    }
}