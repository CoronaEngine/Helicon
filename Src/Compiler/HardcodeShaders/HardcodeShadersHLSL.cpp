#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersHLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_94_32",
ShaderCodeModule(R"(static float4 gl_Position;
static float3 var_0;

struct SPIRV_Cross_Input
{
    float3 var_0 : TEXCOORD0;
};

struct SPIRV_Cross_Output
{
    float4 gl_Position : SV_Position;
};

void vert_main()
{
    gl_Position = float4(var_0, 1.0f);
    gl_Position.x = 114.0f;
}

SPIRV_Cross_Output main(SPIRV_Cross_Input stage_input)
{
    var_0 = stage_input.var_0;
    vert_main();
    SPIRV_Cross_Output stage_output;
    stage_output.gl_Position = gl_Position;
    return stage_output;
}
 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_95_31",
ShaderCodeModule(R"( )")
},
};