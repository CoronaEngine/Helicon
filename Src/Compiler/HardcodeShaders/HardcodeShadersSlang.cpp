#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersSlang = {{"ComputeShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_197_32",
ShaderCodeModule(R"(uniform RWStructuredBuffer<float4>.Handle output;
uniform ConstantBuffer<float4>.Handle buffer;
[numthreads(1,1,1)]
void main() {
	(*output)[0] = *buffer;
} )")
},
};