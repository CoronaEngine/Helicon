#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersHLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_164_32",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 9 "bba910d6dc18b279ed7ea64a0a11699a9cc4d5eb"
struct vertex_output_0
{
    float4 position_output_0 : SV_POSITION;
};


#line 6
struct vertex_input_0
{
    float3 var_0_0 : LOCATION0;
};



vertex_output_0 main(vertex_input_0 input_0)
{

#line 14
    vertex_output_0 output_0;
    output_0.position_output_0 = float4(input_0.var_0_0, 1.0f);
    return output_0;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_165_31",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 2 "400d25f700c88d1e7e2e4d8ea61ee6c58fb9dc61"
struct global_ubo_struct_0
{
    float4 global_var_0_0;
};


#line 5
cbuffer global_ubo_0 : register(b0)
{
    global_ubo_struct_0 global_ubo_0;
}

#line 6
struct fragment_output_0
{
    float4 var_0_0 : SV_TARGET0;
};


#line 10
fragment_output_0 main()
{

#line 11
    fragment_output_0 output_0;
    output_0.var_0_0 = global_ubo_0.global_var_0_0;
    return output_0;
}

 )")
},
};