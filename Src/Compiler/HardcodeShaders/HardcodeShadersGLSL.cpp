#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersGLSL = {{"ComputeShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_203_32",
ShaderCodeModule(R"(#version 450
#extension GL_EXT_samplerless_texture_functions : require
#extension GL_EXT_nonuniform_qualifier : require
layout(row_major) uniform;
layout(row_major) buffer;

#line 90 0
layout(binding = 2, set = 1)
uniform texture2D  _slang_resource_heap_0[];


#line 22857 1
layout(std430, binding = 2, set = 1) buffer StructuredBuffer_vectorx3Cfloatx2C4x3E_t_0 {
    vec4 _data[];
} _slang_resource_heap_1[];

#line 6 2
layout(binding = 1)
layout(std140) uniform block_S1_0
{
    vec4 _data;
} input_0;

#line 22815 1
struct GlobalParams_std140_0
{
    uvec2 textures_0;
    uvec2 output_0;
};


#line 22815
layout(binding = 0)
layout(std140) uniform block_GlobalParams_std140_0
{
    uvec2 textures_0;
    uvec2 output_0;
}globalParams_0;

#line 9 2
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main()
{

#line 9
    uvec2 _S2 = globalParams_0.output_0;

    const ivec3 _S3 = ivec3(0);

#line 11
    _slang_resource_heap_1[globalParams_0.output_0.x]._data[uint(0)] = (texelFetch((_slang_resource_heap_0[globalParams_0.textures_0.x]), ((_S3)).xy, ((_S3)).z));
    _slang_resource_heap_1[_S2.x]._data[uint(1)] = input_0._data;
    return;
}

 )")
},
};