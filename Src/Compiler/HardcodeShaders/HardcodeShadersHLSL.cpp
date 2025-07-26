#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersHLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_153_35",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 14 "6b070ed213366967f26d8bd7e12bbb7b85c2a924"
struct global_ubo_struct_0
{
    float4x4 global_var_0_0;
    float3x3 global_var_1_0;
    float4x4 global_var_2_0;
    float4x4 global_var_3_0;
    float3 global_var_4_0;
    float3 global_var_5_0;
    float3 global_var_6_0;
    uint2 global_var_8_0;
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

#line 8 "6b070ed213366967f26d8bd7e12bbb7b85c2a924"
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
    aggregate_type_1_0 var_2_0 : LOCATION0;
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
    float4 _S6 = float4(_S2.var_0_0.inPosition_0, 1.0f);

#line 36
    output_0.position_output_0 = mul(mul(_S5, ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_0_0), _S6);
    var_1_0.fragPos_0 = mul(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_0_0, _S6).xyz;
    var_1_0.fragNormal_0 = normalize(mul(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_1_0, _S2.var_0_0.inNormal_0));
    var_1_0.fragColor_0 = _S2.var_0_0.inColor_0;
    var_1_0.fragTexCoord_0 = _S2.var_0_0.inTexCoord_0;
    output_0.var_2_0 = var_1_0;
    return output_0;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_154_34",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 14 "1037be7d401d0a6364d3aa9c062b6216ee3fb974"
struct global_ubo_struct_0
{
    float4x4 global_var_0_0;
    float3x3 global_var_1_0;
    float4x4 global_var_2_0;
    float4x4 global_var_3_0;
    float3 global_var_4_0;
    float3 global_var_5_0;
    float3 global_var_6_0;
    uint2 global_var_8_0;
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

#line 28 "1037be7d401d0a6364d3aa9c062b6216ee3fb974"
struct fragment_output_0
{
    float4 var_54_0 : SV_TARGET0;
};


#line 8
struct aggregate_type_1_0
{
    float3 fragPos_0;
    float3 fragNormal_0;
    float2 fragTexCoord_0;
    float3 fragColor_0;
};


#line 25
struct fragment_input_0
{
    aggregate_type_1_0 var_0_0 : LOCATION0;
};



fragment_output_0 main(fragment_input_0 input_0)
{

#line 32
    fragment_input_0 _S1 = input_0;
    fragment_output_0 output_0;

    Texture2D<float4 > _S2 = Texture2D<float4 >(ResourceDescriptorHeap[globalParams_0.global_var_7_0.x]);

#line 35
    SamplerState _S3 = SamplerState(SamplerDescriptorHeap[ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_8_0.x]);

#line 35
    float3 var_1_0;

#line 35
    if((_S2.Sample(_S3, _S1.var_0_0.fragTexCoord_0).w) > 0.00999999977648258f)
    {

#line 36
        Texture2D<float4 > _S4 = Texture2D<float4 >(ResourceDescriptorHeap[globalParams_0.global_var_7_0.x]);

#line 36
        SamplerState _S5 = SamplerState(SamplerDescriptorHeap[ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_8_0.x]);

#line 36
        var_1_0 = _S4.Sample(_S5, _S1.var_0_0.fragTexCoord_0).xyz;

#line 35
    }
    else
    {

#line 35
        var_1_0 = _S1.var_0_0.fragColor_0;

#line 35
    }

#line 47
    float3 var_7_0 = lerp(float3(0.03999999910593033f, 0.03999999910593033f, 0.03999999910593033f), var_1_0, (float3)0.5f);



    float3 _S6 = normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0);

#line 51
    float3 var_11_0 = normalize(_S6 + normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_6_0 - _S1.var_0_0.fragPos_0));
    float3 var_12_0 = normalize(_S1.var_0_0.fragNormal_0);

#line 59
    float3 var_19_0 = normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_6_0 - _S1.var_0_0.fragPos_0);

#line 65
    float var_25_0 = max(dot(var_12_0, normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0)), 0.0f);

#line 71
    float var_31_0 = max(dot(var_12_0, var_19_0), 0.0f);

#line 83
    float3 var_43_0 = float3(1.0f, 1.0f, 1.0f);

#line 88
    float3 _S7 = var_43_0 - var_7_0;

#line 88
    float3 _S8 = normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0);

#line 88
    float3 _S9 = normalize(_S8 + normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_6_0 - _S1.var_0_0.fragPos_0));

#line 93
    float3 _S10 = (var_43_0 - (var_7_0 + _S7 * pow(clamp(1.0f - clamp(dot(_S9, normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0)), 0.0f, 1.0f), 0.0f, 1.0f), 5.0f))) * var_1_0 / 3.14159297943115234f;

#line 93
    float _S11 = max(dot(var_12_0, var_11_0), 0.0f);

#line 93
    float _S12 = _S11 * _S11 * -0.9375f + 1.0f;

#line 93
    float _S13 = 0.0625f / (3.14159297943115234f * _S12 * _S12) * (var_31_0 / (var_31_0 * 0.71875f + 0.28125f) * (var_25_0 / (var_25_0 * 0.71875f + 0.28125f)));

#line 93
    float3 _S14 = normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0);

#line 93
    float3 _S15 = normalize(_S14 + normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_6_0 - _S1.var_0_0.fragPos_0));

#line 93
    float3 _S16 = _S13 * (var_7_0 + _S7 * pow(clamp(1.0f - clamp(dot(_S15, normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0)), 0.0f, 1.0f), 0.0f, 1.0f), 5.0f));

#line 93
    float _S17 = 4.0f * max(dot(var_12_0, normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0)), 0.0f);

#line 93
    float3 _S18 = _S10 + _S16 / (_S17 * max(dot(var_12_0, normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_6_0 - _S1.var_0_0.fragPos_0)), 0.0f) + 0.00009999999747379f);

#line 93
    float3 _S19 = _S18 * ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_5_0;

    output_0.var_54_0 = float4(float3(0.02999999932944775f, 0.02999999932944775f, 0.02999999932944775f) * var_1_0 + _S19 * max(dot(var_12_0, normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_6_0 - _S1.var_0_0.fragPos_0)), 0.0f), 1.0f);
    return output_0;
}

 )")
},
};