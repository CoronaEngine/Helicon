#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersHLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_64_35",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 13 "8ef807d469f84383e57e892654752ee6cff1fc40"
struct global_ubo_struct_0
{
    float4x4 global_var_0_0;
    float4x4 global_var_1_0;
    float4x4 global_var_2_0;
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

#line 22 "8ef807d469f84383e57e892654752ee6cff1fc40"
struct vertex_output_0
{
    float4 position_output_0 : SV_POSITION;
};


#line 1
struct aggregate_type_0_0
{
    float3 inPosition_0;
    float3 inNormal_0;
    float2 inTexCoord_0;
    float3 inColor_0;
};


#line 19
struct vertex_input_0
{
    aggregate_type_0_0 var_0_0 : LOCATION0;
};



vertex_output_0 main(vertex_input_0 input_0)
{

#line 26
    vertex_input_0 _S1 = input_0;
    vertex_output_0 output_0;

    float4x4 _S2 = ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_2_0;

#line 29
    float4x4 _S3 = mul(_S2, ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_1_0);

#line 29
    output_0.position_output_0 = mul(mul(_S3, ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_0_0), float4(_S1.var_0_0.inPosition_0, 1.0f));
    return output_0;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_65_34",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 20 "aac38b2dcfd93ca5b7f04632034e5382d494904e"
void main()
{

#line 21
    return;
}

 )")
},
};