#pragma once

#include"ShaderCodeCompiler.h"


struct ShaderLanguageConverter
{
	// Compile HLSL or GLSL to SPIR-V.
	static std::vector<uint32_t> glslangSpirvCompiler(std::string shaderCode, ShaderLanguage inputLanguage, ShaderStage inputStage);

	//Compile SPIR-V to others
	static std::string spirvCrossConverter(std::vector<uint32_t> spirv_file, ShaderLanguage targetLanguage, int32_t targetVersion = -1);

	// Compile Slang to others
    static std::string slangCompiler(std::string shaderCode, ShaderLanguage targetLanguage);

    static std::vector<uint32_t> slangSpirvCompiler(const std::string& shaderCode);

	//get Reflected Bind Info
	static ShaderCodeModule::ShaderResources spirvCrossReflectedBindInfo(std::vector<uint32_t> spirv_file, ShaderLanguage targetLanguage = ShaderLanguage::GLSL, int32_t targetVersion = 330);
};
