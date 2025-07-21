#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersHLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_144_35",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 8 "9889df514d8714fb3f27bbb9b7907a320995b1f4"
struct vertex_output_0
{
    float4 position_output_0 : SV_POSITION;
    float4 var_2_0 : LOCATION0;
};


#line 1
struct aggregate_type_0_0
{
    float4 pos_0;
    float4 color_0;
};


#line 5
struct vertex_input_0
{
    aggregate_type_0_0 var_0_0 : LOCATION0;
};




vertex_output_0 main(vertex_input_0 input_0)
{

#line 14
    vertex_output_0 output_0;
    output_0.position_output_0 = input_0.var_0_0.pos_0;

    output_0.var_2_0 = input_0.var_0_0.color_0;
    return output_0;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_145_34",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 8 "112cc4e9d2780d8d08b56927430d0024dd3ea1d3"
struct fragment_output_0
{
    float4 var_1_0 : SV_TARGET0;
};


#line 5
struct fragment_input_0
{
    float4 var_0_0 : LOCATION0;
};



fragment_output_0 main(fragment_input_0 input_0)
{

#line 13
    fragment_output_0 output_0;
    output_0.var_1_0 = input_0.var_0_0;
    return output_0;
}

 )")
},
};