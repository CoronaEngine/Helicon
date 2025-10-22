#pragma once

#include <optional>

#include"ShaderCodeCompiler.h"

#include <slang-com-helper.h>
#include <slang-com-ptr.h>
#include <slang.h>

namespace EmbeddedShader
{
	struct ShaderLanguageConverter
	{
		// Compile HLSL or GLSL to SPIR-V.
		static std::vector<uint32_t> glslangSpirvCompiler(std::string shaderCode, ShaderLanguage inputLanguage, ShaderStage inputStage);

		//Compile SPIR-V to others
		static std::string spirvCrossConverter(std::vector<uint32_t> spirv_file, ShaderLanguage targetLanguage, int32_t targetVersion = -1);

		// Compile Slang to others
		static std::string slangCompiler(std::string shaderCode, ShaderLanguage targetLanguage, Slang::ComPtr<slang::IComponentType>& program);
		static std::vector<ShaderCodeModule::ShaderResources> slangCompiler(
            const std::string &shaderCode,
            const std::vector<ShaderLanguage> &targetBinary,
            const std::vector<ShaderLanguage> &targetLanguage,
            std::vector<std::vector<uint32_t>> &binaryTargetsOutput,
            std::vector<std::string> &targetsOutput,
            bool isEnabledReflection);

		static std::vector<uint32_t> slangSpirvCompiler(const std::string& shaderCode, Slang::ComPtr<slang::IComponentType>& program);
#ifdef WIN32
		static std::vector<uint32_t> dxilCompiler(const std::string& hlslShader, ShaderStage stage);
		static std::vector<uint32_t> dxbcCompiler(const std::string& hlslShader, ShaderStage stage);
#endif

		//get Reflected Bind Info
		static ShaderCodeModule::ShaderResources spirvCrossReflectedBindInfo(std::vector<uint32_t> spirv_file, ShaderLanguage targetLanguage = ShaderLanguage::GLSL, int32_t targetVersion = 330);

		//static ShaderCodeModule::ShaderResources slangReflectedBindInfo(const std::string& shaderCode);
	private:
		static void slangReflectAddBindInfo(slang::VariableLayoutReflection* var, ShaderCodeModule::ShaderResources& shaderResources, const std::string&
		                                    parentPrefix);

		static void slangReflectField(slang::VariableLayoutReflection* field, std::string_view accessPath, ShaderCodeModule::ShaderResources& reflection);
		static void slangReflectParameterBlock(slang::ProgramLayout* program, std::string_view uboName, ShaderCodeModule::ShaderResources& reflection);
		static void slangReflectDescriptor(slang::VariableLayoutReflection* var, int set, std::string_view name, ShaderCodeModule::ShaderResources& resource);
		static void slangReflectResource(slang::ProgramLayout* program);
		static void slangReflectTypeLayout(ShaderCodeModule::ShaderResources& shaderResources,int set,slang::VariableLayoutReflection* variableLayout);
	};
}