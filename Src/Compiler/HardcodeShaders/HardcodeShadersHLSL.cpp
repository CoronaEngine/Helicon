#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersHLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_96_32",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 10 "558e42128de5f471f7452917c0635fee119d825a"
struct vertex_output_0
{
    float4 position_output_0 : SV_POSITION;
};


#line 7
struct vertex_input_0
{
    float3 var_0_0 : LOCATION0;
};



vertex_output_0 main(vertex_input_0 input_0)
{

#line 15
    vertex_output_0 output_0;
    output_0.position_output_0 = float4(input_0.var_0_0, 1.0f);
    return output_0;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_97_31",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 3 "df56a762f3edbedcf000fecb8d3aa104b2cacf3d"
struct global_ubo_struct_0
{
    float4 global_var_0_0;
};


#line 6
cbuffer global_ubo_0 : register(b0)
{
    global_ubo_struct_0 global_ubo_0;
}

#line 2
StructuredBuffer<float > global_var_1_0 : register(t0);




struct fragment_output_0
{
    float4 var_0_0 : SV_TARGET0;
};


#line 11
fragment_output_0 main()
{

#line 12
    fragment_output_0 output_0;
    output_0.var_0_0 = global_ubo_0.global_var_0_0;
    output_0.var_0_0[int(3)] = global_var_1_0.Load(int(0));
    return output_0;
}

 )")
},
};