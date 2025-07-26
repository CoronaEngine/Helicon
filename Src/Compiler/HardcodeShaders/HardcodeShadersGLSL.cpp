#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersGLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_70_35",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 12144 0
struct _MatrixStorage_float4x4_ColMajorstd140_0
{
    vec4  data_0[4];
};


#line 12399
struct _MatrixStorage_float3x3_ColMajorstd140_0
{
    vec3  data_1[3];
};


#line 17 1
struct global_ubo_struct_std140_0
{
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_0_0;
    _MatrixStorage_float3x3_ColMajorstd140_0 global_var_1_0;
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_2_0;
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_3_0;
};


#line 22921 0
layout(binding = 2, set = 1)
layout(std140) uniform block_global_ubo_struct_std140_0
{
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_0_0;
    _MatrixStorage_float3x3_ColMajorstd140_0 global_var_1_0;
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_2_0;
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_3_0;
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

#line 7 1
struct aggregate_type_1_0
{
    vec3 fragPos_0;
    vec3 fragNormal_0;
    vec2 fragTexCoord_0;
    vec3 fragColor_0;
};


#line 7
aggregate_type_1_0 aggregate_type_1_x24init_0(vec3 fragPos_1, vec3 fragNormal_1, vec2 fragTexCoord_1, vec3 fragColor_1)
{

#line 7
    aggregate_type_1_0 _S1;
    _S1.fragPos_0 = fragPos_1;
    _S1.fragNormal_0 = fragNormal_1;
    _S1.fragTexCoord_0 = fragTexCoord_1;
    _S1.fragColor_0 = fragColor_1;

#line 7
    return _S1;
}


#line 12399 0
layout(location = 0)
out vec3 entryPointParam_main_var_2_fragPos_0;


#line 12399
layout(location = 1)
out vec3 entryPointParam_main_var_2_fragNormal_0;


#line 12399
layout(location = 2)
out vec2 entryPointParam_main_var_2_fragTexCoord_0;


#line 12399
layout(location = 3)
out vec3 entryPointParam_main_var_2_fragColor_0;


#line 12399
layout(location = 0)
in vec3 input_var_0_inPosition_0;


#line 12399
layout(location = 1)
in vec3 input_var_0_inNormal_0;


#line 12399
layout(location = 2)
in vec2 input_var_0_inTexCoord_0;


#line 12399
layout(location = 3)
in vec3 input_var_0_inColor_0;


#line 23 1
struct vertex_output_0
{
    vec4 position_output_0;
    aggregate_type_1_0 var_2_0;
};


#line 28
void main()
{

#line 8
    const vec3 _S2 = vec3(0.0, 0.0, 0.0);

#line 30
    aggregate_type_1_0 var_1_0 = aggregate_type_1_x24init_0(_S2, _S2, vec2(0.0, 0.0), _S2);

#line 29
    vertex_output_0 output_0;

#line 29
    uvec2 _S3 = globalParams_0.global_ubo_0;

    vec4 _S4 = vec4(input_var_0_inPosition_0, 1.0);

#line 31
    output_0.position_output_0 = (((_S4) * ((((mat4x4(_slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[0][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[1][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[2][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[3][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[0][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[1][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[2][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[3][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[0][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[1][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[2][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[3][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[0][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[1][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[2][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[3][3])) * ((((mat4x4(_slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[0][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[1][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[2][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[3][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[0][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[1][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[2][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[3][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[0][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[1][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[2][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[3][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[0][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[1][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[2][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[3][3])) * (mat4x4(_slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[0][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[1][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[2][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[3][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[0][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[1][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[2][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[3][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[0][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[1][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[2][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[3][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[0][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[1][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[2][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[3][3]))))))))));
    var_1_0.fragPos_0 = (((_S4) * (mat4x4(_slang_resource_heap_0[_S3.x].global_var_0_0.data_0[0][0], _slang_resource_heap_0[_S3.x].global_var_0_0.data_0[1][0], _slang_resource_heap_0[_S3.x].global_var_0_0.data_0[2][0], _slang_resource_heap_0[_S3.x].global_var_0_0.data_0[3][0], _slang_resource_heap_0[_S3.x].global_var_0_0.data_0[0][1], _slang_resource_heap_0[_S3.x].global_var_0_0.data_0[1][1], _slang_resource_heap_0[_S3.x].global_var_0_0.data_0[2][1], _slang_resource_heap_0[_S3.x].global_var_0_0.data_0[3][1], _slang_resource_heap_0[_S3.x].global_var_0_0.data_0[0][2], _slang_resource_heap_0[_S3.x].global_var_0_0.data_0[1][2], _slang_resource_heap_0[_S3.x].global_var_0_0.data_0[2][2], _slang_resource_heap_0[_S3.x].global_var_0_0.data_0[3][2], _slang_resource_heap_0[_S3.x].global_var_0_0.data_0[0][3], _slang_resource_heap_0[_S3.x].global_var_0_0.data_0[1][3], _slang_resource_heap_0[_S3.x].global_var_0_0.data_0[2][3], _slang_resource_heap_0[_S3.x].global_var_0_0.data_0[3][3])))).xyz;
    var_1_0.fragNormal_0 = normalize((((input_var_0_inNormal_0) * (mat3x3(_slang_resource_heap_0[_S3.x].global_var_1_0.data_1[0][0], _slang_resource_heap_0[_S3.x].global_var_1_0.data_1[1][0], _slang_resource_heap_0[_S3.x].global_var_1_0.data_1[2][0], _slang_resource_heap_0[_S3.x].global_var_1_0.data_1[0][1], _slang_resource_heap_0[_S3.x].global_var_1_0.data_1[1][1], _slang_resource_heap_0[_S3.x].global_var_1_0.data_1[2][1], _slang_resource_heap_0[_S3.x].global_var_1_0.data_1[0][2], _slang_resource_heap_0[_S3.x].global_var_1_0.data_1[1][2], _slang_resource_heap_0[_S3.x].global_var_1_0.data_1[2][2])))));
    var_1_0.fragColor_0 = input_var_0_inColor_0;
    var_1_0.fragTexCoord_0 = input_var_0_inTexCoord_0;
    output_0.var_2_0 = var_1_0;
    vertex_output_0 _S5 = output_0;

#line 37
    gl_Position = output_0.position_output_0;

#line 37
    entryPointParam_main_var_2_fragPos_0 = _S5.var_2_0.fragPos_0;

#line 37
    entryPointParam_main_var_2_fragNormal_0 = _S5.var_2_0.fragNormal_0;

#line 37
    entryPointParam_main_var_2_fragTexCoord_0 = _S5.var_2_0.fragTexCoord_0;

#line 37
    entryPointParam_main_var_2_fragColor_0 = _S5.var_2_0.fragColor_0;

#line 37
    return;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_71_34",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 24 0
void main()
{

#line 25
    return;
}

 )")
},
};