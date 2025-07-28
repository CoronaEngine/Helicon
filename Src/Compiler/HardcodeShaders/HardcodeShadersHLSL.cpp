#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersHLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_185_32",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
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

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_186_34",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 14 "0b013cac2bbb006311909e1f8466712f91e3d97f"
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

#line 28 "0b013cac2bbb006311909e1f8466712f91e3d97f"
struct fragment_output_0
{
    float4 var_32_0 : SV_TARGET0;
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
    SamplerState _S3 = SamplerState(SamplerDescriptorHeap[ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_9_0.x]);

#line 35
    float3 var_1_0;

#line 35
    if((_S2.Sample(_S3, _S1.var_0_0.fragTexCoord_0).w) > 0.00999999977648258f)
    {

#line 36
        Texture2D<float4 > _S4 = Texture2D<float4 >(ResourceDescriptorHeap[globalParams_0.global_var_7_0.x]);

#line 36
        SamplerState _S5 = SamplerState(SamplerDescriptorHeap[ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_9_0.x]);

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

#line 44
    float3 var_4_0 = lerp(float3(0.03999999910593033f, 0.03999999910593033f, 0.03999999910593033f), var_1_0, (float3)0.5f);

#line 52
    float3 _S6 = normalize(_S1.var_0_0.fragNormal_0);

#line 52
    float3 _S7 = normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0);

#line 52
    float _S8 = max(dot(_S6, normalize(_S7 + normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_6_0 - _S1.var_0_0.fragPos_0))), 0.0f);

#line 52
    float3 _S9 = normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0);

#line 52
    float _S10 = 3.14159297943115234f * (_S8 * max(dot(_S6, normalize(_S9 + normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_6_0 - _S1.var_0_0.fragPos_0))), 0.0f) * -0.9375f + 1.0f);

#line 52
    float3 _S11 = normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0);

#line 52
    float _S12 = max(dot(_S6, normalize(_S11 + normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_6_0 - _S1.var_0_0.fragPos_0))), 0.0f);

#line 52
    float3 _S13 = normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0);

#line 52
    float var_12_0 = _S10 * (_S12 * max(dot(_S6, normalize(_S13 + normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_6_0 - _S1.var_0_0.fragPos_0))), 0.0f) * -0.9375f + 1.0f);
    float var_13_0 = max(dot(_S6, normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0)), 0.0f);

#line 58
    float var_18_0 = max(dot(_S6, normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_6_0 - _S1.var_0_0.fragPos_0)), 0.0f);

#line 64
    float3 var_24_0 = float3(1.0f, 1.0f, 1.0f);


    float3 _S14 = var_24_0 - var_4_0;

#line 67
    float3 _S15 = normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0);

#line 67
    float3 _S16 = normalize(_S15 + normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_6_0 - _S1.var_0_0.fragPos_0));



    float3 _S17 = (var_24_0 - (var_4_0 + _S14 * pow(clamp(1.0f - clamp(dot(_S16, normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0)), 0.0f, 1.0f), 0.0f, 1.0f), 5.0f))) * var_1_0 / 3.14159297943115234f;

#line 71
    float _S18 = 0.0625f / var_12_0 * (var_18_0 / (var_18_0 * 0.71875f + 0.28125f) * (var_13_0 / (var_13_0 * 0.71875f + 0.28125f)));

#line 71
    float3 _S19 = normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0);

#line 71
    float3 _S20 = normalize(_S19 + normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_6_0 - _S1.var_0_0.fragPos_0));

#line 71
    float3 _S21 = _S18 * (var_4_0 + _S14 * pow(clamp(1.0f - clamp(dot(_S20, normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0)), 0.0f, 1.0f), 0.0f, 1.0f), 5.0f));

#line 71
    float _S22 = 4.0f * max(dot(_S6, normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0)), 0.0f);

#line 71
    float3 _S23 = _S17 + _S21 / (_S22 * max(dot(_S6, normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_6_0 - _S1.var_0_0.fragPos_0)), 0.0f) + 0.00009999999747379f);

#line 71
    float3 _S24 = _S23 * ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_5_0;

    output_0.var_32_0 = float4(float3(0.02999999932944775f, 0.02999999932944775f, 0.02999999932944775f) * var_1_0 + _S24 * max(dot(_S6, normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_6_0 - _S1.var_0_0.fragPos_0)), 0.0f), 1.0f);
    return output_0;
}

 )")
},{"ComputeShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_187_34",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
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

 )")
},
};