#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersHLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_155_35",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 2 "7d5c71ca6f213d5aa12b388c921e2ee0861a1bea"
RWStructuredBuffer<float4 > global_var_2_0 : register(u0);


#line 1
Texture2D<float4 > global_var_1_0 : register(t0);


#line 10
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


#line 7
struct vertex_input_0
{
    aggregate_type_0_0 var_0_0 : LOCATION0;
};




vertex_output_0 main(vertex_input_0 input_0)
{

#line 15
    vertex_input_0 _S1 = input_0;

#line 23
    float4 _S2 = global_var_1_0[uint2(int2(int(0), int(0)))];

#line 23
    global_var_2_0[int(0)] = _S2;

#line 16
    vertex_output_0 output_0;

#line 24
    output_0.position_output_0 = _S2;

    output_0.var_4_0 = _S1.var_0_0.color_0;
    return output_0;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_156_34",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 10 "dda71ed30ce88db4e1ae8d5d0b2545c769b203d4"
struct fragment_output_0
{
    float4 var_1_0 : SV_TARGET0;
};


#line 7
struct fragment_input_0
{
    float4 var_0_0 : LOCATION0;
};



fragment_output_0 main(fragment_input_0 input_0)
{

#line 15
    fragment_output_0 output_0;
    output_0.var_1_0 = input_0.var_0_0;
    return output_0;
}

 )")
},
};