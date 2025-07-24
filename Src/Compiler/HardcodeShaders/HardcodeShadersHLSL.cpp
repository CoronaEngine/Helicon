#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersHLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_167_35",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 7 "04b192ea2cfb10f0f7fd015fa419c3a18a31c03c"
struct global_push_constant_struct_0
{
    uint global_var_1_0;
};


#line 10
cbuffer global_push_constant_0 : register(b0)
{
    global_push_constant_struct_0 global_push_constant_0;
}

#line 2
RWStructuredBuffer<float4 > global_var_3_0 : register(u0);


#line 1
Texture2D<float4 > global_var_2_0 : register(t0);


#line 14
struct vertex_output_0
{
    float4 position_output_0 : SV_POSITION;
    float4 var_4_0 : LOCATION0;
};


#line 3
struct aggregate_type_0_0
{
    float4 pos_0;
    float4 color_0;
};



struct vertex_input_0
{
    aggregate_type_0_0 var_0_0 : LOCATION0;
};




vertex_output_0 main(vertex_input_0 input_0)
{

#line 19
    vertex_input_0 _S1 = input_0;

    float4 var_1_0 = float4(1.0f, 2.0f, 3.0f, 4.0f);


    var_1_0.xy = float2(0.0f, 0.0f);

#line 31
    float4 _S2 = global_var_2_0[uint2(int2(int(0), int(0)))];

#line 31
    global_var_3_0[global_push_constant_0.global_var_1_0] = _S2;

#line 20
    vertex_output_0 output_0;

#line 32
    output_0.position_output_0 = _S2;

    output_0.var_4_0 = _S1.var_0_0.color_0;
    return output_0;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_168_34",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 14 "fb10d6831c46c74afed0902a07ddbe7c23a3d271"
struct fragment_output_0
{
    float4 var_1_0 : SV_TARGET0;
};


#line 11
struct fragment_input_0
{
    float4 var_0_0 : LOCATION0;
};



fragment_output_0 main(fragment_input_0 input_0)
{

#line 19
    fragment_output_0 output_0;
    output_0.var_1_0 = input_0.var_0_0;
    return output_0;
}

 )")
},
};