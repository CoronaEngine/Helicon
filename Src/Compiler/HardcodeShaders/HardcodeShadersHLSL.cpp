#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersHLSL = {{"VertexShader_D__Files_Code_Projects_EDSL_Examples_main_cpp_91_32",
ShaderCodeModule(R"( )")
},{"FragmentShader_D__Files_Code_Projects_EDSL_Examples_main_cpp_92_31",
ShaderCodeModule(R"(static float4 var_0;

struct SPIRV_Cross_Output
{
    float4 var_0 : SV_Target0;
};

void frag_main()
{
}

SPIRV_Cross_Output main()
{
    frag_main();
    SPIRV_Cross_Output stage_output;
    stage_output.var_0 = var_0;
    return stage_output;
}
 )")
},
};