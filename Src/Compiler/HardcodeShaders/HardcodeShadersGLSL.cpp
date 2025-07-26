#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersGLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_64_35",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 12144 0
struct _MatrixStorage_float4x4_ColMajorstd140_0
{
    vec4  data_0[4];
};


#line 16 1
struct global_ubo_struct_std140_0
{
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_0_0;
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_1_0;
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_2_0;
};


#line 22921 0
layout(binding = 2, set = 1)
layout(std140) uniform block_global_ubo_struct_std140_0
{
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_0_0;
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_1_0;
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_2_0;
}_slang_resource_heap_0[];

#line 22879
struct GlobalParams_std140_0
{
    uvec2 global_ubo_0;
};


#line 22879
layout(binding = 0)
layout(std140) uniform block_GlobalParams_std140_0
{
    uvec2 global_ubo_0;
}globalParams_0;

#line 1 1
layout(location = 0)
in vec3 input_var_0_inPosition_0;


#line 22
struct vertex_output_0
{
    vec4 position_output_0;
};


#line 26
void main()
{

#line 27
    vertex_output_0 output_0;

    output_0.position_output_0 = (((vec4(input_var_0_inPosition_0, 1.0)) * ((((mat4x4(_slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[0][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[1][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[2][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[3][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[0][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[1][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[2][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[3][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[0][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[1][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[2][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[3][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[0][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[1][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[2][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[3][3])) * ((((mat4x4(_slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_1_0.data_0[0][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_1_0.data_0[1][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_1_0.data_0[2][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_1_0.data_0[3][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_1_0.data_0[0][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_1_0.data_0[1][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_1_0.data_0[2][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_1_0.data_0[3][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_1_0.data_0[0][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_1_0.data_0[1][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_1_0.data_0[2][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_1_0.data_0[3][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_1_0.data_0[0][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_1_0.data_0[1][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_1_0.data_0[2][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_1_0.data_0[3][3])) * (mat4x4(_slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[0][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[1][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[2][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[3][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[0][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[1][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[2][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[3][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[0][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[1][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[2][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[3][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[0][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[1][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[2][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[3][3]))))))))));

#line 29
    gl_Position = output_0.position_output_0;

#line 29
    return;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_65_34",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 20 0
void main()
{

#line 21
    return;
}

 )")
},
};