#pragma once

#include"ShaderCodeCompiler.h"


struct ShaderLanguageConverter
{
	// Compile HLSL or GLSL to SPIR-V.
	static std::vector<uint32_t> glslangSpirvCompiler(std::string shaderCode, ShaderLanguage inputLanguage, ShaderStage inputStage);

	//Compile SPIR-V to others
	static std::string spirvCrossConverter(std::vector<uint32_t> spirv_file, ShaderLanguage targetLanguage, int32_t targetVersion = -1);

	// Compile Slang to others
    //static std::string slangCompiler(std::string _filePath, ShaderLanguage targetLanguage);

	//get Reflected Bind Info
	static ShaderCodeModule::ShaderResources spirvCrossReflectedBindInfo(std::vector<uint32_t> spirv_file, ShaderLanguage targetLanguage = ShaderLanguage::GLSL, int32_t targetVersion = 330);
};
