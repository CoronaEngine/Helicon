#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersHLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_165_35",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 1 "df203d9560894ad800022c6010592fad86841fbf"
Texture2D<float4 > global_var_2_0 : register(t0);


#line 9
struct vertex_output_0
{
    float4 position_output_0 : SV_POSITION;
    float4 var_4_0 : LOCATION0;
};


#line 2
struct aggregate_type_0_0
{
    float4 pos_0;
    float4 color_0;
};


#line 6
struct vertex_input_0
{
    aggregate_type_0_0 var_0_0 : LOCATION0;
};




vertex_output_0 main(vertex_input_0 input_0)
{
    float4 var_1_0 = float4(1.0f, 2.0f, 3.0f, 4.0f);


    var_1_0.xy = float2(0.0f, 0.0f);

#line 15
    vertex_output_0 output_0;

#line 26
    output_0.position_output_0 = global_var_2_0[uint2(int2(int(0), int(0)))];

    output_0.var_4_0 = input_0.var_0_0.color_0;
    return output_0;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_166_34",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 9 "8bcad02ce27b6c2790a26ee00035b11c27603603"
struct fragment_output_0
{
    float4 var_1_0 : SV_TARGET0;
};


#line 6
struct fragment_input_0
{
    float4 var_0_0 : LOCATION0;
};



fragment_output_0 main(fragment_input_0 input_0)
{

#line 14
    fragment_output_0 output_0;
    output_0.var_1_0 = input_0.var_0_0;
    return output_0;
}

 )")
},
};