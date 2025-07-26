#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersHLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_50_35",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 6 "6b3e490b44fe9eab8dfccb70d8a3c5d1fa81e9cd"
struct global_ubo_struct_0
{
    uint2 global_var_1_0;
};


#line 22879 "hlsl.meta.slang"
struct GlobalParams_0
{
    uint2 global_var_0_0;
    uint2 global_ubo_0;
};


#line 22879
cbuffer globalParams_0 : register(b0)
{
    GlobalParams_0 globalParams_0;
}

#line 13 "6b3e490b44fe9eab8dfccb70d8a3c5d1fa81e9cd"
struct vertex_output_0
{
    float4 position_output_0 : SV_POSITION;
    float4 var_1_0 : LOCATION0;
};


#line 2
struct aggregate_type_0_0
{
    float4 pos_0;
    float2 texCoord_0;
};



struct vertex_input_0
{
    aggregate_type_0_0 var_0_0 : LOCATION0;
};




vertex_output_0 main(vertex_input_0 input_0)
{

#line 18
    vertex_input_0 _S1 = input_0;
    vertex_output_0 output_0;
    output_0.position_output_0 = input_0.var_0_0.pos_0;
    Texture2D<float4 > _S2 = Texture2D<float4 >(ResourceDescriptorHeap[globalParams_0.global_var_0_0.x]);

#line 21
    SamplerState _S3 = SamplerState(SamplerDescriptorHeap[ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_1_0.x]);

#line 21
    output_0.var_1_0 = _S2.Sample(_S3, _S1.var_0_0.texCoord_0);
    return output_0;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_51_34",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 13 "f292e04182f8ff43b49b85e443bfd21c59249380"
struct fragment_output_0
{
    float4 var_1_0 : SV_TARGET0;
};


#line 10
struct fragment_input_0
{
    float4 var_0_0 : LOCATION0;
};



fragment_output_0 main(fragment_input_0 input_0)
{

#line 18
    fragment_output_0 output_0;
    output_0.var_1_0 = input_0.var_0_0;
    return output_0;
}

 )")
},
};