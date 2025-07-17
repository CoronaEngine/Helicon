#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersHLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_100_32",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 4 "e37193b17dd00fa889f29d26d20a6e3c50573eb2"
struct global_ubo_struct_0
{
    float4 global_var_0_0;
    float4 global_var_1_0;
    float4 global_var_2_0;
};


#line 9
cbuffer shader_ubo_0 : register(b0)
{
    global_ubo_struct_0 shader_ubo_0;
}
struct vertex_output_0
{
    float4 var_1_0 : LOCATION0;
    float4 position_output_0 : SV_POSITION;
};


#line 10
struct vertex_input_0
{
    float3 var_0_0 : LOCATION0;
};




vertex_output_0 main(vertex_input_0 input_0)
{

#line 19
    vertex_output_0 output_0;
    output_0.position_output_0 = float4(input_0.var_0_0, 1.0f);
    output_0.var_1_0 = shader_ubo_0.global_var_0_0;
    output_0.var_1_0 = shader_ubo_0.global_var_1_0;
    return output_0;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_101_31",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 4 "31182d3902e22ad3301d8961c11dce88f31f82a1"
struct global_ubo_struct_0
{
    float4 global_var_0_0;
    float4 global_var_1_0;
    float4 global_var_2_0;
};


#line 9
cbuffer shader_ubo_0 : register(b0)
{
    global_ubo_struct_0 shader_ubo_0;
}
struct fragment_output_0
{
    float4 var_1_0 : SV_TARGET0;
};


#line 10
struct fragment_input_0
{
    float4 var_0_0 : LOCATION0;
};



fragment_output_0 main(fragment_input_0 input_0)
{

#line 18
    fragment_output_0 output_0;
    output_0.var_1_0 = shader_ubo_0.global_var_0_0;
    output_0.var_1_0 = shader_ubo_0.global_var_2_0;
    return output_0;
}

 )")
},
};