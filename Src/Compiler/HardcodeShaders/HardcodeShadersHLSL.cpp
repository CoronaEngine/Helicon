#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersHLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_159_35",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 10 "e5fd720cf8f2f2f05b873bdceb27d8d578744b4f"
struct global_ubo_struct_0
{
    float4 global_var_1_0;
    uint global_var_2_0;
};


#line 2
cbuffer global_ubo_0 : register(b0)
{
    global_ubo_struct_0 global_ubo_0;
}

#line 1
RWStructuredBuffer<float4 > global_ubo_global_var_3_member_0 : register(u2);



RWStructuredBuffer<RWTexture2D<float4 > > global_var_5_0 : register(u1);


#line 4
RWStructuredBuffer<float4 > global_var_4_0 : register(u0);


#line 19
struct vertex_output_0
{
    float4 position_output_0 : SV_POSITION;
    float4 var_2_0 : LOCATION0;
};


#line 6
struct aggregate_type_1_0
{
    float4 pos_0;
    float4 color_0;
};


#line 16
struct vertex_input_0
{
    aggregate_type_1_0 var_0_0 : LOCATION0;
};




vertex_output_0 main(vertex_input_0 input_0)
{

#line 24
    vertex_input_0 _S1 = input_0;

    global_var_5_0[global_ubo_0.global_var_2_0][uint2(0U, 0U)] = global_ubo_0.global_var_1_0;
    global_ubo_global_var_3_member_0[global_ubo_0.global_var_2_0] = global_ubo_0.global_var_1_0;
    global_var_4_0[global_ubo_0.global_var_2_0] = global_ubo_0.global_var_1_0;
    _S1.var_0_0.pos_0[int(0)] = global_ubo_0.global_var_1_0.x;

#line 25
    vertex_output_0 output_0;

#line 30
    output_0.position_output_0 = _S1.var_0_0.pos_0;

    output_0.var_2_0 = _S1.var_0_0.color_0;
    return output_0;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_160_34",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 19 "d4568c6bc93eb3f2ca30979cb2cb8a9904a80efc"
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