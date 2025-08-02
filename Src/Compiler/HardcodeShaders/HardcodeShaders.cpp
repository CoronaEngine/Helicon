#include"HardcodeShaders.h"
std::unordered_map<std::string,std::unordered_map<std::string, std::variant<ShaderCodeModule::ShaderResources,std::variant<std::vector<uint32_t>,std::string>>>*> HardcodeShaders::hardcodeShaders = {{"VertexShader",&hardcodeShadersVertexShader},{"FragmentShader",&hardcodeShadersFragmentShader},{"ComputeShader",&hardcodeShadersComputeShader},
};