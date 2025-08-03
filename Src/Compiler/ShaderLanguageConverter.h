#pragma once

#include"ShaderCodeCompiler.h"

namespace EmbeddedShader
{
	struct ShaderLanguageConverter
	{
		// Compile HLSL or GLSL to SPIR-V.
		static std::vector<uint32_t> glslangSpirvCompiler(std::string shaderCode, ShaderLanguage inputLanguage, ShaderStage inputStage);

		//Compile SPIR-V to others
		static std::string spirvCrossConverter(std::vector<uint32_t> spirv_file, ShaderLanguage targetLanguage, int32_t targetVersion = -1);

		// Compile Slang to others
		static std::string slangCompiler(std::string shaderCode, ShaderLanguage targetLanguage);

		static std::vector<uint32_t> slangSpirvCompiler(const std::string& shaderCode);
#ifdef WIN32
		static std::vector<uint32_t> dxilCompiler(const std::string& hlslShader, ShaderStage stage);
		static std::vector<uint32_t> dxbcCompiler(const std::string& hlslShader, ShaderStage stage);
#endif

		//get Reflected Bind Info
		static ShaderCodeModule::ShaderResources spirvCrossReflectedBindInfo(std::vector<uint32_t> spirv_file, ShaderLanguage targetLanguage = ShaderLanguage::GLSL, int32_t targetVersion = 330);
	};
}