#pragma once
#include <unordered_map>
#include "../ShaderCodeCompiler.h"
class HardcodeShaders
{
	static std::unordered_map<std::string,std::unordered_map<std::string, ShaderCodeModule>*> hardcodeShaders;	static std::unordered_map<std::string, ShaderCodeModule> hardcodeShadersSpirV;	static std::unordered_map<std::string, ShaderCodeModule> hardcodeShadersGLSL;	static std::unordered_map<std::string, ShaderCodeModule> hardcodeShadersHLSL;	static std::unordered_map<std::string, ShaderCodeModule> hardcodeShadersSlang;
};