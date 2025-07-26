#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersHLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_70_35",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 13 "37eed35b6c7013249d202cc4397060097772f508"
struct global_ubo_struct_0
{
    float4x4 global_var_0_0;
    float3x3 global_var_1_0;
    float4x4 global_var_2_0;
    float4x4 global_var_3_0;
};


#line 22879 "hlsl.meta.slang"
struct GlobalParams_0
{
    uint2 global_ubo_0;
};


#line 22879
cbuffer globalParams_0 : register(b0)
{
    GlobalParams_0 globalParams_0;
}

#line 7 "37eed35b6c7013249d202cc4397060097772f508"
struct aggregate_type_1_0
{
    float3 fragPos_0;
    float3 fragNormal_0;
    float2 fragTexCoord_0;
    float3 fragColor_0;
};


#line 7
aggregate_type_1_0 aggregate_type_1_x24init_0(float3 fragPos_1, float3 fragNormal_1, float2 fragTexCoord_1, float3 fragColor_1)
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


#line 23
struct vertex_output_0
{
    float4 position_output_0 : SV_POSITION;
    aggregate_type_1_0 var_2_0 : LOCATION0;
};


#line 1
struct aggregate_type_0_0
{
    float3 inPosition_0;
    float3 inNormal_0;
    float2 inTexCoord_0;
    float3 inColor_0;
};


#line 20
struct vertex_input_0
{
    aggregate_type_0_0 var_0_0 : LOCATION0;
};




vertex_output_0 main(vertex_input_0 input_0)
{

#line 28
    vertex_input_0 _S2 = input_0;

#line 8
    float3 _S3 = float3(0.0f, 0.0f, 0.0f);

#line 30
    aggregate_type_1_0 var_1_0 = aggregate_type_1_x24init_0(_S3, _S3, float2(0.0f, 0.0f), _S3);

#line 29
    vertex_output_0 output_0;

    float4x4 _S4 = ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_3_0;

#line 31
    float4x4 _S5 = mul(_S4, ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_2_0);

#line 31
    float4 _S6 = float4(_S2.var_0_0.inPosition_0, 1.0f);

#line 31
    output_0.position_output_0 = mul(mul(_S5, ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_0_0), _S6);
    var_1_0.fragPos_0 = mul(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_0_0, _S6).xyz;
    var_1_0.fragNormal_0 = normalize(mul(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_1_0, _S2.var_0_0.inNormal_0));
    var_1_0.fragColor_0 = _S2.var_0_0.inColor_0;
    var_1_0.fragTexCoord_0 = _S2.var_0_0.inTexCoord_0;
    output_0.var_2_0 = var_1_0;
    return output_0;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_71_34",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 7 "60b065aef3e9467cac0e7dff193123873a1dd052"
struct aggregate_type_1_0
{
    float3 fragPos_0;
    float3 fragNormal_0;
    float2 fragTexCoord_0;
    float3 fragColor_0;
};


#line 20
struct fragment_input_0
{
    aggregate_type_1_0 var_0_0 : LOCATION0;
};


#line 24
void main(fragment_input_0 input_0)
{

#line 25
    return;
}

 )")
},
};