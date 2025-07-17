#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersHLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_96_32",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 10 "75c48d6a2e3773a30589ff3a4cc932c187462168"
struct vertex_output_0
{
    float4 position_output_0 : SV_POSITION;
};


#line 7
struct vertex_input_0
{
    float3 var_0_0 : LOCATION0;
};



vertex_output_0 main(vertex_input_0 input_0)
{

#line 15
    vertex_output_0 output_0;
    output_0.position_output_0 = float4(input_0.var_0_0, 1.0f);
    return output_0;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_97_31",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 2 "28bdf23f1fb5498dba39ee35ced10960b71a0499"
StructuredBuffer<float4 > global_var_1_0 : register(t0);




struct fragment_output_0
{
    float4 var_0_0 : SV_TARGET0;
};


#line 11
fragment_output_0 main()
{

#line 12
    fragment_output_0 output_0;

    output_0.var_0_0 = global_var_1_0.Load(int(0));
    return output_0;
}

 )")
},
};