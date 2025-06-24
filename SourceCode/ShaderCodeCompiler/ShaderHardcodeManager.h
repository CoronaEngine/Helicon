#pragma once

#include "ShaderCodeCompiler.h"


struct ShaderHardcodeManager
{
public:
	static bool hardcodeShaderCode(const std::string& shaderCode, ShaderLanguage language, ShaderStage inputStage, const std::source_location& sourceLocation);
	static bool hardcodeShaderCode(const std::vector<uint32_t>& shaderCode, ShaderLanguage language, ShaderStage inputStage, const std::source_location& sourceLocation);
	static std::string getHardcodeVariableName(const std::source_location& sourceLocation, ShaderStage inputStage);
	static ShaderCodeModule getHardcodeShader(const std::string &hardcodeVariableName, ShaderLanguage language);

private:
	static bool hardcodeFileOpened;
	static bool generateHardcodeFiles();
	static std::string ShaderLanguageFlagToString(ShaderLanguage language);
};
