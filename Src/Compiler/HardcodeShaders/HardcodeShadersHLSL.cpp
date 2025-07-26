#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersHLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_147_35",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 90 "core"
SamplerState global_ubo_global_var_2_0 : register(s0);


#line 1 "44e5f8a4f727c4f4bc8708636a53240e98f023fc"
Texture2D<float4 > global_var_1_0 : register(t0);


#line 13
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

#line 19
    vertex_output_0 output_0;
    output_0.position_output_0 = input_0.var_0_0.pos_0;
    output_0.var_1_0 = global_var_1_0.Sample(global_ubo_global_var_2_0, input_0.var_0_0.texCoord_0);
    return output_0;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_148_34",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 13 "2cdce097c0bd0542b3081e28db7c0c62bb33a6b0"
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