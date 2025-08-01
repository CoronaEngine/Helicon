#include"HardcodeShaders.h"
std::unordered_map<std::string,std::unordered_map<std::string, ShaderCodeModule>*> HardcodeShaders::hardcodeShaders = {{"SpirV",&hardcodeShadersSpirV},{"GLSL",&hardcodeShadersGLSL},{"HLSL",&hardcodeShadersHLSL},{"Slang",&hardcodeShadersSlang},
};