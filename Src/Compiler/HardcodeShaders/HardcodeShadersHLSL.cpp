#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersHLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_170_35",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 90 "core"
RWStructuredBuffer<float4 > global_ubo_global_var_3_member3_0 : register(u1);


#line 2 "830a1d3750d8397a5452ddfd41e07c9ca138e859"
RWStructuredBuffer<float4 > global_var_2_0 : register(u0);


#line 1
Texture2D<float4 > global_var_1_0 : register(t0);


#line 19
struct vertex_output_0
{
    float4 position_output_0 : SV_POSITION;
    float4 var_4_0 : LOCATION0;
};


#line 8
struct aggregate_type_1_0
{
    float4 pos_0;
    float4 color_0;
};



struct vertex_input_0
{
    aggregate_type_1_0 var_0_0 : LOCATION0;
};




vertex_output_0 main(vertex_input_0 input_0)
{

#line 24
    vertex_input_0 _S1 = input_0;

    float4 _S2 = float4(1.0f, 2.0f, 3.0f, 4.0f);

#line 26
    float4 var_1_0 = _S2;
    global_ubo_global_var_3_member3_0[int(0)] = _S2;


    var_1_0.xy = float2(0.0f, 0.0f);

#line 37
    global_var_2_0[int(0)] = global_var_1_0[uint2(0U, 0U)];

#line 25
    vertex_output_0 output_0;

#line 38
    output_0.position_output_0 = global_var_1_0[uint2(int2(int(0), int(0)))];

    output_0.var_4_0 = _S1.var_0_0.color_0;
    return output_0;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_171_34",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 19 "5380c150fce6fcd34ebed640c89fe2d6c4f7a3e3"
struct fragment_output_0
{
    float4 var_1_0 : SV_TARGET0;
};


#line 16
struct fragment_input_0
{
    float4 var_0_0 : LOCATION0;
};



fragment_output_0 main(fragment_input_0 input_0)
{

#line 24
    fragment_output_0 output_0;
    output_0.var_1_0 = input_0.var_0_0;
    return output_0;
}

 )")
},
};