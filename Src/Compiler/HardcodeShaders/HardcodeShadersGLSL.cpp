#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersGLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_144_35",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 1 0
layout(location = 0)
out vec4 entryPointParam_main_var_2_0;


#line 1
layout(location = 0)
in vec4 input_var_0_pos_0;


#line 1
layout(location = 1)
in vec4 input_var_0_color_0;


#line 8
struct vertex_output_0
{
    vec4 position_output_0;
    vec4 var_2_0;
};


#line 13
void main()
{

#line 14
    vertex_output_0 output_0;
    output_0.position_output_0 = input_var_0_pos_0;

    output_0.var_2_0 = input_var_0_color_0;
    vertex_output_0 _S1 = output_0;

#line 18
    gl_Position = output_0.position_output_0;

#line 18
    entryPointParam_main_var_2_0 = _S1.var_2_0;

#line 18
    return;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_145_34",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 5 0
layout(location = 0)
out vec4 entryPointParam_main_var_1_0;


#line 5
layout(location = 0)
in vec4 input_var_0_0;

struct fragment_output_0
{
    vec4 var_1_0;
};


#line 12
void main()
{

#line 13
    fragment_output_0 output_0;
    output_0.var_1_0 = input_var_0_0;

#line 14
    entryPointParam_main_var_1_0 = output_0.var_1_0;

#line 14
    return;
}

 )")
},
};