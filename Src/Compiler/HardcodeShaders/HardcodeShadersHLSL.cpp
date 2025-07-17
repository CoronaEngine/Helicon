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


#line 10 "fc89bbb7ef65c3d6accd66f79086deba5741de58"
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
},
};