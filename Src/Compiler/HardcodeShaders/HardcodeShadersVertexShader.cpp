#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersVertexShader = {{"SpirV_D__Files_Code_Projects_Helicon_Examples_main_cpp", ShaderCodeModule(std::vector<uint32_t>{119734787,66816,2621440,185,0,131089,5302,131089,1,196622,0,1,851983,0,2,1852399981,0,65,169,174,177,181,184,15,52,196611,11,1,524293,15,1970302569,1635135092,774922098,1867542121,1769236851,28271,458757,48,1651469383,1632660577,1936548210,1685353311,3159089,458758,48,0,1651469415,1985965153,929002081,0,393222,48,1,1651469415,1969187937,28514,393221,52,1651469415,1632660577,1936548210,0,786437,59,1952533855,1400400242,1634889588,1717527911,1952542572,1597274164,1298952003,1919904353,828666995,12340,327686,59,0,1635017060,0,786437,62,1952533855,1400400242,1634889588,1717527911,1952542572,1597208627,1298952003,1919904353,828666995,12340,327686,62,0,1635017060,0,589829,58,1651469415,1969187937,1935634274,1668641396,1953718132,808726884,0,458758,58,0,1651469415,1985965153,811561569,0,458758,58,1,1651469415,1985965153,828338785,0,458758,58,2,1651469415,1985965153,845116001,0,458758,58,3,1651469415,1985965153,861893217,0,458758,58,4,1651469415,1985965153,878670433,0,458758,58,5,1651469415,1985965153,895447649,0,458758,58,6,1651469415,1985965153,912224865,0,458758,58,7,1651469415,1985965153,962556513,0,524293,65,1819500383,1600613985,1869833586,1701016181,1634035807,112,720901,174,1920233061,1768902777,1632662638,1601003890,1852399981,1918989870,1714304607,1348952434,29551,786437,177,1920233061,1768902777,1632662638,1601003890,1852399981,1918989870,1714304607,1315398002,1634562671,108,786437,181,1920233061,1768902777,1632662638,1601003890,1852399981,1918989870,1714304607,1416061298,1866692709,6582895,786437,184,1920233061,1768902777,1632662638,1601003890,1852399981,1918989870,1714304607,1130848626,1919904879,0,262149,2,1852399981,0,262215,15,30,0,196679,48,2,327752,48,0,35,0,327752,48,1,35,8,262215,52,33,0,262215,52,34,0,262215,60,6,16,327752,59,0,35,0,262215,63,6,16,327752,62,0,35,0,196679,58,2,327752,58,0,35,0,327752,58,1,35,64,327752,58,2,35,112,327752,58,3,35,176,327752,58,4,35,240,327752,58,5,35,256,327752,58,6,35,272,327752,58,7,35,288,262215,65,33,2,262215,65,34,1,262215,169,11,0,262215,174,30,0,262215,177,30,1,262215,181,30,2,262215,184,30,3,131091,1,196641,3,1,196630,6,32,262167,7,6,4,262167,9,6,3,262167,10,6,2,262176,14,1,9,262165,26,32,1,262187,26,27,0,262187,26,31,1,262187,26,34,2,262187,26,38,3,262187,6,44,0,393260,9,43,44,44,44,327724,10,45,44,44,262165,49,32,0,262167,50,49,2,262174,48,50,50,262176,51,2,48,262176,53,2,50,262187,26,61,4,262172,60,7,61,196638,59,60,262172,63,9,38,196638,62,63,655390,58,59,62,59,59,9,9,9,50,196637,57,58,262176,64,2,57,262176,66,2,58,262176,68,2,59,262168,96,7,4,262187,6,161,1065353216,262176,168,3,7,262176,173,3,9,262176,180,3,10,262203,14,15,1,262203,51,52,2,262203,64,65,2,262203,168,169,3,262203,173,174,3,262203,173,177,3,262203,180,181,3,262203,173,184,3,327734,1,2,0,3,131320,4,262205,9,13,15,327746,53,54,52,31,262205,50,55,54,327761,49,56,55,0,327745,66,67,65,56,327746,68,69,67,38,262205,59,70,69,327761,60,71,70,0,327761,7,72,71,0,327761,6,73,72,0,327761,6,74,72,1,327761,6,75,72,2,327761,6,76,72,3,327761,7,77,71,1,327761,6,78,77,0,327761,6,79,77,1,327761,6,80,77,2,327761,6,81,77,3,327761,7,82,71,2,327761,6,83,82,0,327761,6,84,82,1,327761,6,85,82,2,327761,6,86,82,3,327761,7,87,71,3,327761,6,88,87,0,327761,6,89,87,1,327761,6,90,87,2,327761,6,91,87,3,458832,7,92,73,78,83,88,458832,7,93,74,79,84,89,458832,7,94,75,80,85,90,458832,7,95,76,81,86,91,458832,96,97,92,93,94,95,327761,49,98,55,0,327745,66,99,65,98,327746,68,100,99,34,262205,59,101,100,327761,60,102,101,0,327761,7,103,102,0,327761,6,104,103,0,327761,6,105,103,1,327761,6,106,103,2,327761,6,107,103,3,327761,7,108,102,1,327761,6,109,108,0,327761,6,110,108,1,327761,6,111,108,2,327761,6,112,108,3,327761,7,113,102,2,327761,6,114,113,0,327761,6,115,113,1,327761,6,116,113,2,327761,6,117,113,3,327761,7,118,102,3,327761,6,119,118,0,327761,6,120,118,1,327761,6,121,118,2,327761,6,122,118,3,458832,7,123,104,109,114,119,458832,7,124,105,110,115,120,458832,7,125,106,111,116,121,458832,7,126,107,112,117,122,458832,96,127,123,124,125,126,327826,96,128,127,97,327761,49,129,55,0,327745,66,130,65,129,327746,68,131,130,27,262205,59,132,131,327761,60,133,132,0,327761,7,134,133,0,327761,6,135,134,0,327761,6,136,134,1,327761,6,137,134,2,327761,6,138,134,3,327761,7,139,133,1,327761,6,140,139,0,327761,6,141,139,1,327761,6,142,139,2,327761,6,143,139,3,327761,7,144,133,2,327761,6,145,144,0,327761,6,146,144,1,327761,6,147,144,2,327761,6,148,144,3,327761,7,149,133,3,327761,6,150,149,0,327761,6,151,149,1,327761,6,152,149,2,327761,6,153,149,3,458832,7,154,135,140,145,150,458832,7,155,136,141,146,151,458832,7,156,137,142,147,152,458832,7,157,138,143,148,153,458832,96,158,154,155,156,157,327826,96,159,158,128,327760,7,160,13,161,327824,7,162,160,159,196670,169,162,196670,174,43,196670,177,43,196670,181,45,196670,184,43,65789,65592,}),},{"GLSL_D__Files_Code_Projects_Helicon_Examples_main_cpp", ShaderCodeModule(R"(#version 450
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

)"),},{"HLSL_D__Files_Code_Projects_Helicon_Examples_main_cpp", ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 14 "25ca870c7e98433c9a036eadc77fd7183776e110"
struct global_ubo_struct_0
{
    float4x4 global_var_0_0;
    float3x3 global_var_1_0;
    float4x4 global_var_2_0;
    float4x4 global_var_3_0;
    float3 global_var_4_0;
    float3 global_var_5_0;
    float3 global_var_6_0;
    uint2 global_var_9_0;
};


#line 22879 "hlsl.meta.slang"
struct GlobalParams_0
{
    uint2 global_var_7_0;
    uint2 global_ubo_0;
};


#line 22879
cbuffer globalParams_0 : register(b0)
{
    GlobalParams_0 globalParams_0;
}

#line 8 "25ca870c7e98433c9a036eadc77fd7183776e110"
struct aggregate_type_1_0
{
    float3 fragPos_0;
    float3 fragNormal_0;
    float2 fragTexCoord_0;
    float3 fragColor_0;
};


#line 8
aggregate_type_1_0 aggregate_type_1_x24init_0(float3 fragPos_1, float3 fragNormal_1, float2 fragTexCoord_1, float3 fragColor_1)
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


#line 28
struct vertex_output_0
{
    float4 position_output_0 : SV_POSITION;
    aggregate_type_1_0 var_6_0 : LOCATION0;
};


#line 2
struct aggregate_type_0_0
{
    float3 inPosition_0;
    float3 inNormal_0;
    float2 inTexCoord_0;
    float3 inColor_0;
};


#line 25
struct vertex_input_0
{
    aggregate_type_0_0 var_0_0 : LOCATION0;
};




vertex_output_0 main(vertex_input_0 input_0)
{

#line 33
    vertex_input_0 _S2 = input_0;

#line 9
    float3 _S3 = float3(0.0f, 0.0f, 0.0f);

#line 35
    aggregate_type_1_0 var_1_0 = aggregate_type_1_x24init_0(_S3, _S3, float2(0.0f, 0.0f), _S3);

#line 34
    vertex_output_0 output_0;

    float4x4 _S4 = ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_3_0;

#line 36
    float4x4 _S5 = mul(_S4, ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_2_0);

#line 36
    output_0.position_output_0 = mul(mul(_S5, ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_0_0), float4(_S2.var_0_0.inPosition_0, 1.0f));

#line 41
    output_0.var_6_0 = var_1_0;
    return output_0;
}

)"),},{"Slang_D__Files_Code_Projects_Helicon_Examples_main_cpp", ShaderCodeModule(R"(uniform Texture2D<float4>.Handle global_var_7;
struct aggregate_type_0 {
	float3 inPosition;
	float3 inNormal;
	float2 inTexCoord;
	float3 inColor;
}
struct aggregate_type_1 {
	float3 fragPos;
	float3 fragNormal;
	float2 fragTexCoord;
	float3 fragColor;
}
struct global_ubo_struct {
	float4x4 global_var_0;
	float3x3 global_var_1;
	float4x4 global_var_2;
	float4x4 global_var_3;
	float3 global_var_4;
	float3 global_var_5;
	float3 global_var_6;
	SamplerState.Handle global_var_9;
}
uniform ConstantBuffer<global_ubo_struct>.Handle global_ubo;
struct vertex_input {
	aggregate_type_0 var_0 : LOCATION0;
}
struct vertex_output {
	float4 position_output : SV_POSITION;
	aggregate_type_1 var_6 : LOCATION0;
}
[shader("vertex")]
vertex_output main(vertex_input input) {
	vertex_output output;
	aggregate_type_1 var_1 = {};
	output.position_output = mul(mul(mul((*global_ubo).global_var_3,(*global_ubo).global_var_2),(*global_ubo).global_var_0),float4(input.var_0.inPosition,1.000000));
	float3 var_2 = mul((*global_ubo).global_var_0,float4(input.var_0.inPosition,1.000000)).xyz;
	float3 var_3 = normalize(mul((*global_ubo).global_var_1,input.var_0.inNormal));
	float3 var_4 = input.var_0.inColor;
	float2 var_5 = input.var_0.inTexCoord;
	output.var_6 = var_1;
	return output;
}
)"),},
};