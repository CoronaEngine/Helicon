#pragma once
#include <unordered_map>
#include "../ShaderCodeCompiler.h"
class HardcodeShaders
{
	friend class ShaderHardcodeManager;
	static std::unordered_map<std::string,std::unordered_map<std::string, ShaderCodeModule>*> hardcodeShaders;
	static std::unordered_map<std::string, ShaderCodeModule> hardcodeShadersVertexShader;
	static std::unordered_map<std::string, ShaderCodeModule> hardcodeShadersFragmentShader;
	static std::unordered_map<std::string, ShaderCodeModule> hardcodeShadersComputeShader;
};