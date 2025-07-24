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
StructuredBuffer<float4 > global_ubo_global_var_4_member3_0 : register(t1);


#line 12 "1c17a2d1c1c8652bd60f04555efef74e272bb666"
struct global_push_constant_struct_0
{
    uint global_var_1_0;
};


#line 15
cbuffer global_push_constant_0 : register(b0)
{
    global_push_constant_struct_0 global_push_constant_0;
}

#line 2
RWStructuredBuffer<float4 > global_var_3_0 : register(u0);


#line 1
Texture2D<float4 > global_var_2_0 : register(t0);


#line 23
struct vertex_output_0
{
    float4 position_output_0 : SV_POSITION;
    float4 var_5_0 : LOCATION0;
};


#line 8
struct aggregate_type_1_0
{
    float4 pos_0;
    float4 color_0;
};


#line 20
struct vertex_input_0
{
    aggregate_type_1_0 var_0_0 : LOCATION0;
};




vertex_output_0 main(vertex_input_0 input_0)
{

#line 28
    vertex_input_0 _S1 = input_0;

    float4 var_1_0 = global_ubo_global_var_4_member3_0.Load(int(0));



    var_1_0.xy = float2(0.0f, 0.0f);

#line 42
    global_var_3_0[global_push_constant_0.global_var_1_0] = global_var_2_0[uint2(0U, 0U)];

#line 29
    vertex_output_0 output_0;

#line 43
    output_0.position_output_0 = global_var_2_0[uint2(int2(int(0), int(0)))];

    output_0.var_5_0 = _S1.var_0_0.color_0;
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


#line 23 "4262acf2d87e0188b784da6350711c2a4db2769c"
struct fragment_output_0
{
    float4 var_1_0 : SV_TARGET0;
};


#line 20
struct fragment_input_0
{
    float4 var_0_0 : LOCATION0;
};



fragment_output_0 main(fragment_input_0 input_0)
{

#line 28
    fragment_output_0 output_0;
    output_0.var_1_0 = input_0.var_0_0;
    return output_0;
}

 )")
},
};