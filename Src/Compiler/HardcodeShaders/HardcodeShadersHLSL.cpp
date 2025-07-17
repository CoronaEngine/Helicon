#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersHLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_97_32",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 2 "e92e5a63867107341d46e0639cfe65776bec3a1a"
struct vertex_ssbo_struct_0
{
    float4 global_var_0_0;
};


#line 5
RWStructuredBuffer<vertex_ssbo_struct_0 > shader_ssbo_0 : register(u0);




struct vertex_output_0
{
    float4 var_2_0 : LOCATION0;
    float4 position_output_0 : SV_POSITION;
};


#line 6
struct vertex_input_0
{
    float3 var_0_0 : LOCATION0;
    float4 var_1_0 : LOCATION1;
};




vertex_output_0 main(vertex_input_0 input_0)
{

#line 16
    vertex_output_0 output_0;
    output_0.position_output_0 = float4(input_0.var_0_0, 1.0f);
    output_0.var_2_0 = input_0.var_1_0;
    shader_ssbo_0[int(0)].global_var_0_0 = input_0.var_1_0;
    return output_0;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_98_31",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 5 "0284b115b16b718b8abda5504f784b4eb816be66"
struct fragment_output_0
{
    float4 var_1_0 : SV_TARGET0;
};


#line 2
struct fragment_input_0
{
    float4 var_0_0 : LOCATION0;
};



fragment_output_0 main(fragment_input_0 input_0)
{

#line 10
    fragment_output_0 output_0;
    output_0.var_1_0 = input_0.var_0_0;
    return output_0;
}

 )")
},
};