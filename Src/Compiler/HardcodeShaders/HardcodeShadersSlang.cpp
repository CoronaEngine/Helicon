#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersSlang = {{"ComputeShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_203_32",
ShaderCodeModule(R"(uniform Texture2D.Handle textures;

// define a descriptor handle using builtin convenience typealias:
uniform RWStructuredBuffer<float4>.Handle output;

uniform ConstantBuffer<float4> input;

[numthreads(1,1,1)]
void main()
{
    output[0] = textures.Load(int3(0));
	output[1] = input;
} )")
},
};