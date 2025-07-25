#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersGLSL = {{"ComputeShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_197_32",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 22857 0
layout(binding = 2, set = 1)
layout(std140) uniform block_S1_0
{
    vec4 _data;
} _slang_resource_heap_0[];

#line 22857
layout(std430, binding = 2, set = 1) buffer StructuredBuffer_vectorx3Cfloatx2C4x3E_t_0 {
    vec4 _data[];
} _slang_resource_heap_1[];

#line 22815
struct GlobalParams_std140_0
{
    uvec2 output_0;
    uvec2 buffer_0;
};


#line 22815
layout(binding = 0)
layout(std140) uniform block_GlobalParams_std140_0
{
    uvec2 output_0;
    uvec2 buffer_0;
}globalParams_0;

#line 4 1
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main()
{

#line 5
    _slang_resource_heap_1[globalParams_0.output_0.x]._data[uint(0)] = _slang_resource_heap_0[globalParams_0.buffer_0.x]._data;
    return;
}

 )")
},
};