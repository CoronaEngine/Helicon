#include"HardcodeShaders.h"
std::unordered_map<std::string,std::unordered_map<std::string, ShaderCodeModule>*> HardcodeShaders::hardcodeShaders = {{"VertexShader",&hardcodeShadersVertexShader},{"FragmentShader",&hardcodeShadersFragmentShader},{"ComputeShader",&hardcodeShadersComputeShader},
};