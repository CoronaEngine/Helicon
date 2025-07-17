#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersGLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_96_32",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 7 0
layout(location = 0)
in vec3 input_var_0_0;

struct vertex_output_0
{
    vec4 position_output_0;
};


#line 14
void main()
{

#line 15
    vertex_output_0 output_0;
    output_0.position_output_0 = vec4(input_var_0_0, 1.0);

#line 16
    gl_Position = output_0.position_output_0;

#line 16
    return;
}

 )")
},
};