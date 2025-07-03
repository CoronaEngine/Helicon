#pragma once
#include <unordered_map>
#include"../ShaderCodeCompiler.h"
class HardcodeShaders
{
	friend struct ShaderHardcodeManager;
	static std::unordered_map<std::string, ShaderCodeModule> hardcodeShadersSpirV;
	static std::unordered_map<std::string, ShaderCodeModule> hardcodeShadersHLSL;
	static std::unordered_map<std::string, ShaderCodeModule> hardcodeShadersGLSL;
};
