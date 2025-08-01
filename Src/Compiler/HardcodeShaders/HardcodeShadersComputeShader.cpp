#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersComputeShader = {{"SpirV_D__Files_Code_Projects_Helicon_Examples_main_cpp", ShaderCodeModule(std::vector<uint32_t>{119734787,66816,2621440,126,0,131089,55,131089,56,131089,5302,131089,1,393227,73,1280527431,1685353262,808793134,0,196622,0,1,524303,5,2,1852399981,0,24,9,13,393232,2,17,8,8,1,196611,11,1,458757,10,1651469383,1632660577,1936548210,1685353311,3159089,458758,10,0,1651469415,1985965153,929002081,0,393221,13,1651469415,1632660577,1936548210,0,524293,24,1819500383,1600613985,1869833586,1701016181,1634035807,112,262149,34,1886216563,6579564,262149,41,1886216563,6579564,262149,53,1886216563,6579564,262149,59,1886216563,6579564,262149,86,1886216563,6579564,262149,92,1886216563,6579564,262149,102,1886216563,6579564,262149,108,1886216563,6579564,262149,2,1852399981,0,262215,9,11,28,196679,10,2,327752,10,0,35,0,262215,13,33,0,262215,13,34,0,262215,24,33,2,262215,24,34,1,131091,1,196641,3,1,262165,5,32,0,262167,6,5,3,262176,8,1,6,262167,11,5,2,196638,10,11,262176,12,2,10,262165,14,32,1,262187,14,15,0,262176,16,2,11,196630,21,32,589849,22,21,1,2,0,0,2,0,196637,20,22,262176,23,0,20,262176,25,0,22,262167,30,14,2,262167,33,21,4,262167,36,21,3,262187,21,45,1075880919,262187,21,47,1022739087,262187,21,63,1075545375,262187,21,65,1058474557,262187,21,69,1041194025,262187,21,75,0,393260,36,74,75,75,75,262187,21,77,1065353216,393260,36,76,77,77,77,262203,8,9,1,262203,12,13,2,262203,23,24,0,393260,36,123,47,47,47,393260,36,124,65,65,65,393260,36,125,69,69,69,327734,1,2,0,3,131320,4,262205,6,7,9,327746,16,17,13,15,262205,11,18,17,327761,5,19,18,0,327745,25,26,24,19,458831,11,27,7,7,0,1,327761,5,28,18,0,327745,25,29,24,28,262268,30,31,27,262205,22,32,29,327778,33,34,32,31,524367,36,37,34,34,0,1,2,327761,5,38,18,0,327745,25,39,24,38,262205,22,40,39,327778,33,41,40,31,524367,36,43,41,41,0,1,2,327822,36,44,43,45,327809,36,48,123,44,327813,36,49,37,48,327761,5,50,18,0,327745,25,51,24,50,262205,22,52,51,327778,33,53,52,31,524367,36,55,53,53,0,1,2,327761,5,56,18,0,327745,25,57,24,56,262205,22,58,57,327778,33,59,58,31,524367,36,61,59,59,0,1,2,327822,36,62,61,63,327809,36,66,124,62,327813,36,67,55,66,327809,36,70,125,67,327816,36,71,49,70,524300,36,72,73,43,71,74,76,327760,33,78,72,77,262205,22,79,26,262243,79,27,78,327761,5,81,18,0,327745,25,82,24,81,327761,5,83,18,0,327745,25,84,24,83,262205,22,85,84,327778,33,86,85,31,524367,36,88,86,86,0,1,2,327761,5,89,18,0,327745,25,90,24,89,262205,22,91,90,327778,33,92,91,31,524367,36,94,92,92,0,1,2,327822,36,95,94,45,327809,36,97,123,95,327813,36,98,88,97,327761,5,99,18,0,327745,25,100,24,99,262205,22,101,100,327778,33,102,101,31,524367,36,104,102,102,0,1,2,327761,5,105,18,0,327745,25,106,24,105,262205,22,107,106,327778,33,108,107,31,524367,36,110,108,108,0,1,2,327822,36,111,110,63,327809,36,113,124,111,327813,36,114,104,113,327809,36,116,125,114,327816,36,117,98,116,524300,36,118,73,43,117,74,76,327760,33,119,118,77,262205,22,120,82,262243,120,27,119,65789,65592,},{0,"",{{"GlobalParams_std140",{0,0,0,"GlobalParams_std140","uniform",1,8,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(3)}},}}),},{"GLSL_D__Files_Code_Projects_Helicon_Examples_main_cpp", ShaderCodeModule(R"(#version 450
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

)",{0,"",{{"GlobalParams_std140",{0,0,0,"GlobalParams_std140","uniform",1,8,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(3)}},}}),},{"HLSL_D__Files_Code_Projects_Helicon_Examples_main_cpp", ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 22879 "hlsl.meta.slang"
struct GlobalParams_0
{
    uint2 global_var_7_0;
};


#line 22879
cbuffer globalParams_0 : register(b0)
{
    GlobalParams_0 globalParams_0;
}

#line 2 "b766333db470cb507842e8f34c6b71704f6ebe5a"
struct compute_input_0
{
    uint3 dispatch_thread_id_input_0 : SV_DispatchThreadID;
};

[numthreads(8, 8, 1)]
void main(compute_input_0 input_0)
{

#line 7
    compute_input_0 _S1 = input_0;

#line 13
    RWTexture2D<float4 > _S2 = RWTexture2D<float4 >(ResourceDescriptorHeap[globalParams_0.global_var_7_0.x]);

#line 13
    uint2 _S3 = _S1.dispatch_thread_id_input_0.xy;

#line 13
    RWTexture2D<float4 > _S4 = RWTexture2D<float4 >(ResourceDescriptorHeap[globalParams_0.global_var_7_0.x]);

#line 13
    float4 _S5 = _S4[_S3];

#line 13
    float3 _S6 = _S5.xyz;

#line 13
    RWTexture2D<float4 > _S7 = RWTexture2D<float4 >(ResourceDescriptorHeap[globalParams_0.global_var_7_0.x]);

#line 13
    float4 _S8 = _S7[_S3];

#line 13
    float3 _S9 = _S6 * (0.02999999932944775f + 2.50999999046325684f * _S8.xyz);

#line 13
    RWTexture2D<float4 > _S10 = RWTexture2D<float4 >(ResourceDescriptorHeap[globalParams_0.global_var_7_0.x]);

#line 13
    float4 _S11 = _S10[_S3];

#line 13
    float3 _S12 = _S11.xyz;

#line 13
    RWTexture2D<float4 > _S13 = RWTexture2D<float4 >(ResourceDescriptorHeap[globalParams_0.global_var_7_0.x]);

#line 13
    float4 _S14 = _S13[_S3];

#line 13
    float3 _S15 = float3(0.0f, 0.0f, 0.0f);

#line 13
    float3 _S16 = float3(1.0f, 1.0f, 1.0f);

#line 13
    _S2[_S3] = float4(clamp(_S9 / (0.14000000059604645f + _S12 * (0.5899999737739563f + 2.43000006675720215f * _S14.xyz)), _S15, _S16), 1.0f);

#line 19
    RWTexture2D<float4 > _S17 = RWTexture2D<float4 >(ResourceDescriptorHeap[globalParams_0.global_var_7_0.x]);

#line 19
    RWTexture2D<float4 > _S18 = RWTexture2D<float4 >(ResourceDescriptorHeap[globalParams_0.global_var_7_0.x]);

#line 19
    float4 _S19 = _S18[_S3];

#line 19
    float3 _S20 = _S19.xyz;

#line 19
    RWTexture2D<float4 > _S21 = RWTexture2D<float4 >(ResourceDescriptorHeap[globalParams_0.global_var_7_0.x]);

#line 19
    float4 _S22 = _S21[_S3];

#line 19
    float3 _S23 = _S20 * (0.02999999932944775f + 2.50999999046325684f * _S22.xyz);

#line 19
    RWTexture2D<float4 > _S24 = RWTexture2D<float4 >(ResourceDescriptorHeap[globalParams_0.global_var_7_0.x]);

#line 19
    float4 _S25 = _S24[_S3];

#line 19
    float3 _S26 = _S25.xyz;

#line 19
    RWTexture2D<float4 > _S27 = RWTexture2D<float4 >(ResourceDescriptorHeap[globalParams_0.global_var_7_0.x]);

#line 19
    float4 _S28 = _S27[_S3];

#line 19
    _S17[_S3] = float4(clamp(_S23 / (0.14000000059604645f + _S26 * (0.5899999737739563f + 2.43000006675720215f * _S28.xyz)), _S15, _S16), 1.0f);
    return;
}

)",{0,"",{{"GlobalParams_std140",{0,0,0,"GlobalParams_std140","uniform",1,8,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(3)}},}}),},{"Slang_D__Files_Code_Projects_Helicon_Examples_main_cpp", ShaderCodeModule(R"(uniform RWTexture2D<float4>.Handle global_var_7;
struct compute_input {
	uint3 dispatch_thread_id_input : SV_DispatchThreadID;
}
[shader("compute")]
[numthreads(8,8,1)]
void main(compute_input input) {
	float var_0 = 2.510000;
	float var_1 = 0.030000;
	float var_2 = 2.430000;
	float var_3 = 0.590000;
	float var_4 = 0.140000;
	global_var_7[input.dispatch_thread_id_input.xy] = float4(clamp(((global_var_7[input.dispatch_thread_id_input.xy].xyz * (var_1 + (var_0 * global_var_7[input.dispatch_thread_id_input.xy].xyz))) / (var_4 + (global_var_7[input.dispatch_thread_id_input.xy].xyz * (var_3 + (var_2 * global_var_7[input.dispatch_thread_id_input.xy].xyz))))),float3(0.000000, 0.000000, 0.000000),float3(1.000000, 1.000000, 1.000000)),1.000000);
	float var_5 = 2.510000;
	float var_6 = 0.030000;
	float var_7 = 2.430000;
	float var_8 = 0.590000;
	float var_9 = 0.140000;
	global_var_7[input.dispatch_thread_id_input.xy] = float4(clamp(((global_var_7[input.dispatch_thread_id_input.xy].xyz * (var_6 + (var_5 * global_var_7[input.dispatch_thread_id_input.xy].xyz))) / (var_9 + (global_var_7[input.dispatch_thread_id_input.xy].xyz * (var_8 + (var_7 * global_var_7[input.dispatch_thread_id_input.xy].xyz))))),float3(0.000000, 0.000000, 0.000000),float3(1.000000, 1.000000, 1.000000)),1.000000);
}
)",{0,"",{{"GlobalParams_std140",{0,0,0,"GlobalParams_std140","uniform",1,8,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(3)}},}}),},
};