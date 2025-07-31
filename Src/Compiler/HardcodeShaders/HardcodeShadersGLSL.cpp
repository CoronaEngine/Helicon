#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersGLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp", ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 561 0
struct _MatrixStorage_float4x4_ColMajorstd140_0
{
    vec4  data_0[4];
};


#line 2 1
struct _MatrixStorage_float3x3_ColMajorstd140_0
{
    vec3  data_1[3];
};


#line 14
struct global_ubo_struct_std140_0
{
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_0_0;
    _MatrixStorage_float3x3_ColMajorstd140_0 global_var_1_0;
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_2_0;
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_3_0;
    vec3 global_var_4_0;
    vec3 global_var_5_0;
    vec3 global_var_6_0;
    uvec2 global_var_9_0;
};


#line 22921 0
layout(binding = 2, set = 1)
layout(std140) uniform block_global_ubo_struct_std140_0
{
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_0_0;
    _MatrixStorage_float3x3_ColMajorstd140_0 global_var_1_0;
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_2_0;
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_3_0;
    vec3 global_var_4_0;
    vec3 global_var_5_0;
    vec3 global_var_6_0;
    uvec2 global_var_9_0;
}_slang_resource_heap_0[];

#line 22879
struct GlobalParams_std140_0
{
    uvec2 global_var_7_0;
    uvec2 global_ubo_0;
};


#line 22879
layout(binding = 0)
layout(std140) uniform block_GlobalParams_std140_0
{
    uvec2 global_var_7_0;
    uvec2 global_ubo_0;
}globalParams_0;

#line 8 1
struct aggregate_type_1_0
{
    vec3 fragPos_0;
    vec3 fragNormal_0;
    vec2 fragTexCoord_0;
    vec3 fragColor_0;
};


#line 8
aggregate_type_1_0 aggregate_type_1_x24init_0(vec3 fragPos_1, vec3 fragNormal_1, vec2 fragTexCoord_1, vec3 fragColor_1)
{

#line 8
    aggregate_type_1_0 _S1;
    _S1.fragPos_0 = fragPos_1;
    _S1.fragNormal_0 = fragNormal_1;
    _S1.fragTexCoord_0 = fragTexCoord_1;
    _S1.fragColor_0 = fragColor_1;

#line 8
    return _S1;
}


#line 12144 0
layout(location = 0)
out vec3 entryPointParam_main_var_6_fragPos_0;


#line 12144
layout(location = 1)
out vec3 entryPointParam_main_var_6_fragNormal_0;


#line 12144
layout(location = 2)
out vec2 entryPointParam_main_var_6_fragTexCoord_0;


#line 12144
layout(location = 3)
out vec3 entryPointParam_main_var_6_fragColor_0;


#line 12144
layout(location = 0)
in vec3 input_var_0_inPosition_0;


#line 28 1
struct vertex_output_0
{
    vec4 position_output_0;
    aggregate_type_1_0 var_6_0;
};


#line 33
void main()
{

#line 9
    const vec3 _S2 = vec3(0.0, 0.0, 0.0);

#line 35
    aggregate_type_1_0 var_1_0 = aggregate_type_1_x24init_0(_S2, _S2, vec2(0.0, 0.0), _S2);

#line 34
    vertex_output_0 output_0;

    output_0.position_output_0 = (((vec4(input_var_0_inPosition_0, 1.0)) * ((((mat4x4(_slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[0][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[1][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[2][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[3][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[0][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[1][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[2][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[3][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[0][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[1][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[2][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[3][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[0][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[1][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[2][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_0_0.data_0[3][3])) * ((((mat4x4(_slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[0][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[1][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[2][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[3][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[0][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[1][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[2][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[3][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[0][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[1][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[2][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[3][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[0][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[1][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[2][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_2_0.data_0[3][3])) * (mat4x4(_slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[0][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[1][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[2][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[3][0], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[0][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[1][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[2][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[3][1], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[0][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[1][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[2][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[3][2], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[0][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[1][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[2][3], _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_3_0.data_0[3][3]))))))))));

#line 41
    output_0.var_6_0 = var_1_0;
    vertex_output_0 _S3 = output_0;

#line 42
    gl_Position = output_0.position_output_0;

#line 42
    entryPointParam_main_var_6_fragPos_0 = _S3.var_6_0.fragPos_0;

#line 42
    entryPointParam_main_var_6_fragNormal_0 = _S3.var_6_0.fragNormal_0;

#line 42
    entryPointParam_main_var_6_fragTexCoord_0 = _S3.var_6_0.fragTexCoord_0;

#line 42
    entryPointParam_main_var_6_fragColor_0 = _S3.var_6_0.fragColor_0;

#line 42
    return;
}

)"),},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp", ShaderCodeModule(R"(#version 450
#extension GL_EXT_nonuniform_qualifier : require
layout(row_major) uniform;
layout(row_major) buffer;

#line 90 0
layout(binding = 2, set = 1)
uniform texture2D  _slang_resource_heap_0[];


#line 22921 1
layout(binding = 0, set = 1)
uniform sampler  _slang_resource_heap_1[];


#line 15 2
struct _MatrixStorage_float4x4_ColMajorstd140_0
{
    vec4  data_0[4];
};


#line 12399 1
struct _MatrixStorage_float3x3_ColMajorstd140_0
{
    vec3  data_1[3];
};


#line 22879
struct global_ubo_struct_std140_0
{
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_0_0;
    _MatrixStorage_float3x3_ColMajorstd140_0 global_var_1_0;
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_2_0;
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_3_0;
    vec3 global_var_4_0;
    vec3 global_var_5_0;
    vec3 global_var_6_0;
    uvec2 global_var_9_0;
};


#line 22921
layout(binding = 2, set = 1)
layout(std140) uniform block_global_ubo_struct_std140_0
{
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_0_0;
    _MatrixStorage_float3x3_ColMajorstd140_0 global_var_1_0;
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_2_0;
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_3_0;
    vec3 global_var_4_0;
    vec3 global_var_5_0;
    vec3 global_var_6_0;
    uvec2 global_var_9_0;
}_slang_resource_heap_2[];

#line 22879
struct GlobalParams_std140_0
{
    uvec2 global_var_7_0;
    uvec2 global_ubo_0;
};


#line 22879
layout(binding = 0)
layout(std140) uniform block_GlobalParams_std140_0
{
    uvec2 global_var_7_0;
    uvec2 global_ubo_0;
}globalParams_0;

#line 12442
layout(location = 0)
out vec4 entryPointParam_main_var_32_0;


#line 12442
layout(location = 0)
in vec3 input_var_0_fragPos_0;


#line 12442
layout(location = 1)
in vec3 input_var_0_fragNormal_0;


#line 12442
layout(location = 2)
in vec2 input_var_0_fragTexCoord_0;


#line 12442
layout(location = 3)
in vec3 input_var_0_fragColor_0;


#line 28 2
struct fragment_output_0
{
    vec4 var_32_0;
};


#line 32
void main()
{

#line 33
    fragment_output_0 output_0;

#line 33
    uvec2 _S1 = globalParams_0.global_var_7_0;

#line 33
    uvec2 _S2 = globalParams_0.global_ubo_0;

#line 33
    vec3 var_1_0;

    if(((texture(sampler2D(_slang_resource_heap_0[globalParams_0.global_var_7_0.x],_slang_resource_heap_1[_slang_resource_heap_2[globalParams_0.global_ubo_0.x].global_var_9_0.x]), (input_var_0_fragTexCoord_0))).w) > 0.00999999977648258)
    {

#line 35
        var_1_0 = (texture(sampler2D(_slang_resource_heap_0[_S1.x],_slang_resource_heap_1[_slang_resource_heap_2[_S2.x].global_var_9_0.x]), (input_var_0_fragTexCoord_0))).xyz;

#line 35
    }
    else
    {

#line 35
        var_1_0 = input_var_0_fragColor_0;

#line 35
    }

#line 44
    vec3 var_4_0 = mix(vec3(0.03999999910593033, 0.03999999910593033, 0.03999999910593033), var_1_0, vec3(0.5));

#line 52
    vec3 _S3 = normalize(input_var_0_fragNormal_0);
    float var_13_0 = max(dot(_S3, normalize(_slang_resource_heap_2[_S2.x].global_var_4_0 - input_var_0_fragPos_0)), 0.0);

#line 58
    float var_18_0 = max(dot(_S3, normalize(_slang_resource_heap_2[_S2.x].global_var_6_0 - input_var_0_fragPos_0)), 0.0);

#line 64
    const vec3 var_24_0 = vec3(1.0, 1.0, 1.0);


    vec3 _S4 = var_24_0 - var_4_0;

#line 73
    output_0.var_32_0 = vec4(vec3(0.02999999932944775, 0.02999999932944775, 0.02999999932944775) * var_1_0 + ((var_24_0 - (var_4_0 + _S4 * pow(clamp(1.0 - clamp(dot(normalize(normalize(_slang_resource_heap_2[_S2.x].global_var_4_0 - input_var_0_fragPos_0) + normalize(_slang_resource_heap_2[_S2.x].global_var_6_0 - input_var_0_fragPos_0)), normalize(_slang_resource_heap_2[_S2.x].global_var_4_0 - input_var_0_fragPos_0)), 0.0, 1.0), 0.0, 1.0), 5.0))) * var_1_0 / 3.14159297943115234 + 0.0625 / (3.14159297943115234 * (max(dot(_S3, normalize(normalize(_slang_resource_heap_2[_S2.x].global_var_4_0 - input_var_0_fragPos_0) + normalize(_slang_resource_heap_2[_S2.x].global_var_6_0 - input_var_0_fragPos_0))), 0.0) * max(dot(_S3, normalize(normalize(_slang_resource_heap_2[_S2.x].global_var_4_0 - input_var_0_fragPos_0) + normalize(_slang_resource_heap_2[_S2.x].global_var_6_0 - input_var_0_fragPos_0))), 0.0) * -0.9375 + 1.0) * (max(dot(_S3, normalize(normalize(_slang_resource_heap_2[_S2.x].global_var_4_0 - input_var_0_fragPos_0) + normalize(_slang_resource_heap_2[_S2.x].global_var_6_0 - input_var_0_fragPos_0))), 0.0) * max(dot(_S3, normalize(normalize(_slang_resource_heap_2[_S2.x].global_var_4_0 - input_var_0_fragPos_0) + normalize(_slang_resource_heap_2[_S2.x].global_var_6_0 - input_var_0_fragPos_0))), 0.0) * -0.9375 + 1.0)) * (var_18_0 / (var_18_0 * 0.71875 + 0.28125) * (var_13_0 / (var_13_0 * 0.71875 + 0.28125))) * (var_4_0 + _S4 * pow(clamp(1.0 - clamp(dot(normalize(normalize(_slang_resource_heap_2[_S2.x].global_var_4_0 - input_var_0_fragPos_0) + normalize(_slang_resource_heap_2[_S2.x].global_var_6_0 - input_var_0_fragPos_0)), normalize(_slang_resource_heap_2[_S2.x].global_var_4_0 - input_var_0_fragPos_0)), 0.0, 1.0), 0.0, 1.0), 5.0)) / (4.0 * max(dot(_S3, normalize(_slang_resource_heap_2[_S2.x].global_var_4_0 - input_var_0_fragPos_0)), 0.0) * max(dot(_S3, normalize(_slang_resource_heap_2[_S2.x].global_var_6_0 - input_var_0_fragPos_0)), 0.0) + 0.00009999999747379)) * _slang_resource_heap_2[_S2.x].global_var_5_0 * max(dot(_S3, normalize(_slang_resource_heap_2[_S2.x].global_var_6_0 - input_var_0_fragPos_0)), 0.0), 1.0);

#line 73
    entryPointParam_main_var_32_0 = output_0.var_32_0;

#line 73
    return;
}

)"),},{"ComputeShader_D__Files_Code_Projects_Helicon_Examples_main_cpp", ShaderCodeModule(R"(#version 450
#extension GL_EXT_nonuniform_qualifier : require
layout(row_major) uniform;
layout(row_major) buffer;

#line 90 0
layout(rgba32f)
layout(binding = 2, set = 1)
uniform image2D  _slang_resource_heap_0[];


#line 22879 1
struct GlobalParams_std140_0
{
    uvec2 global_var_7_0;
};


#line 22879
layout(binding = 0)
layout(std140) uniform block_GlobalParams_std140_0
{
    uvec2 global_var_7_0;
}globalParams_0;

#line 7 2
layout(local_size_x = 8, local_size_y = 8, local_size_z = 1) in;
void main()
{

#line 7
    uvec2 _S1 = globalParams_0.global_var_7_0;

#line 13
    uint _S2 = globalParams_0.global_var_7_0.x;

#line 13
    ivec2 _S3 = ivec2(gl_GlobalInvocationID.xy);

#line 13
    vec4 _S4 = (imageLoad((_slang_resource_heap_0[globalParams_0.global_var_7_0.x]), (_S3)));

#line 13
    vec3 _S5 = _S4.xyz;

#line 13
    vec4 _S6 = (imageLoad((_slang_resource_heap_0[_S1.x]), (_S3)));

#line 13
    vec3 _S7 = _S5 * (0.02999999932944775 + 2.50999999046325684 * _S6.xyz);

#line 13
    vec4 _S8 = (imageLoad((_slang_resource_heap_0[_S1.x]), (_S3)));

#line 13
    vec3 _S9 = _S8.xyz;

#line 13
    vec4 _S10 = (imageLoad((_slang_resource_heap_0[_S1.x]), (_S3)));

#line 13
    const vec3 _S11 = vec3(0.0, 0.0, 0.0);

#line 13
    const vec3 _S12 = vec3(1.0, 1.0, 1.0);

#line 13
    imageStore((_slang_resource_heap_0[_S2]), (_S3), vec4(clamp(_S7 / (0.14000000059604645 + _S9 * (0.5899999737739563 + 2.43000006675720215 * _S10.xyz)), _S11, _S12), 1.0));

#line 19
    uint _S13 = _S1.x;

#line 19
    vec4 _S14 = (imageLoad((_slang_resource_heap_0[_S1.x]), (_S3)));

#line 19
    vec3 _S15 = _S14.xyz;

#line 19
    vec4 _S16 = (imageLoad((_slang_resource_heap_0[_S1.x]), (_S3)));

#line 19
    vec3 _S17 = _S15 * (0.02999999932944775 + 2.50999999046325684 * _S16.xyz);

#line 19
    vec4 _S18 = (imageLoad((_slang_resource_heap_0[_S1.x]), (_S3)));

#line 19
    vec3 _S19 = _S18.xyz;

#line 19
    vec4 _S20 = (imageLoad((_slang_resource_heap_0[_S1.x]), (_S3)));

#line 19
    imageStore((_slang_resource_heap_0[_S13]), (_S3), vec4(clamp(_S17 / (0.14000000059604645 + _S19 * (0.5899999737739563 + 2.43000006675720215 * _S20.xyz)), _S11, _S12), 1.0));
    return;
}

)"),},
};