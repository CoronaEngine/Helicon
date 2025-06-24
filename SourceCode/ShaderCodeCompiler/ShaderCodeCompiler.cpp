
#include "ShaderCodeCompiler.h"

#include "ShaderHardcodeManager.h"
#include "ShaderLanguageConverter.h"


ShaderCodeCompiler::ShaderCodeCompiler(const std::string &shaderCodePath, ShaderStage inputStage, ShaderLanguage language, const std::source_location &sourceLocation)
{
    hardcodeVariableName = ShaderHardcodeManager::getHardcodeVariableName(sourceLocation, inputStage);

#if CABBAGE_ENGINE_DEBUG
    std::vector<uint32_t> codeSpirV = {};
    std::string codeGLSL = "";
    std::string codeHLSL = "";

    switch (language)
    {
    case ShaderLanguage::GLSL:
        codeGLSL = CabbageFiles::readStringFile(shaderCodePath);
        codeSpirV = ShaderLanguageConverter::glslangSpirvCompiler(codeGLSL, language, inputStage);
        codeGLSL = ShaderLanguageConverter::spirvCrossConverter(codeSpirV, ShaderLanguage::GLSL);
        codeHLSL = ShaderLanguageConverter::spirvCrossConverter(codeSpirV, ShaderLanguage::HLSL);
        break;
    case ShaderLanguage::HLSL:
        codeHLSL = CabbageFiles::readStringFile(shaderCodePath);
        codeSpirV = ShaderLanguageConverter::glslangSpirvCompiler(codeHLSL, language, inputStage);
        codeGLSL = ShaderLanguageConverter::spirvCrossConverter(codeSpirV, ShaderLanguage::GLSL);
        codeHLSL = ShaderLanguageConverter::spirvCrossConverter(codeSpirV, ShaderLanguage::HLSL);
        break;
    case ShaderLanguage::SpirV:
        codeSpirV = CabbageFiles::readBinaryFile(shaderCodePath);
        codeGLSL = ShaderLanguageConverter::spirvCrossConverter(codeSpirV, ShaderLanguage::GLSL);
        codeHLSL = ShaderLanguageConverter::spirvCrossConverter(codeSpirV, ShaderLanguage::HLSL);
        break;
    default:
        break;
    }

    ShaderHardcodeManager::hardcodeShaderCode(codeSpirV, ShaderLanguage::SpirV, inputStage, sourceLocation);
    ShaderHardcodeManager::hardcodeShaderCode(codeGLSL, ShaderLanguage::GLSL, inputStage, sourceLocation);
    ShaderHardcodeManager::hardcodeShaderCode(codeHLSL, ShaderLanguage::HLSL, inputStage, sourceLocation);
#endif
}

ShaderCodeModule ShaderCodeCompiler::getShaderCode(ShaderLanguage language) const
{
    ShaderCodeModule result = ShaderHardcodeManager::getHardcodeShader(hardcodeVariableName, language);
    result.shaderResources = ShaderLanguageConverter::spirvCrossReflectedBindInfo(ShaderHardcodeManager::getHardcodeShader(hardcodeVariableName, ShaderLanguage::SpirV), ShaderLanguage::HLSL);
    return result;
}