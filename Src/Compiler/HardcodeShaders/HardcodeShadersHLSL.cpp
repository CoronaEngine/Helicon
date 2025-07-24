#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersHLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_171_35",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 90 "core"
RWTexture2D<float4 > global_ubo_global_var_3_member4_0 : register(u2);


#line 2 "9d17fc789fc1a35db5f4c38bcaaeee9b99a34554"
RWStructuredBuffer<float4 > global_var_2_0 : register(u0);


#line 1
Texture2D<float4 > global_var_1_0 : register(t0);


#line 20
struct vertex_output_0
{
    float4 position_output_0 : SV_POSITION;
    float4 var_4_0 : LOCATION0;
};


#line 9
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

#line 25
    vertex_input_0 _S1 = input_0;

    float4 _S2 = float4(1.0f, 2.0f, 3.0f, 4.0f);

#line 27
    float4 var_1_0 = _S2;
    uint2 _S3 = uint2(0U, 0U);

#line 28
    global_ubo_global_var_3_member4_0[_S3] = _S2;


    var_1_0.xy = float2(0.0f, 0.0f);

#line 38
    global_var_2_0[int(0)] = global_var_1_0[_S3];

#line 26
    vertex_output_0 output_0;

#line 39
    output_0.position_output_0 = global_var_1_0[uint2(int2(int(0), int(0)))];

    output_0.var_4_0 = _S1.var_0_0.color_0;
    return output_0;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_172_34",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 20 "83ec4d2c5bb18e7dc36a7078d35cee08692c8e64"
struct fragment_output_0
{
    float4 var_1_0 : SV_TARGET0;
};


#line 17
struct fragment_input_0
{
    float4 var_0_0 : LOCATION0;
};



fragment_output_0 main(fragment_input_0 input_0)
{

#line 25
    fragment_output_0 output_0;
    output_0.var_1_0 = input_0.var_0_0;
    return output_0;
}

 )")
},
};