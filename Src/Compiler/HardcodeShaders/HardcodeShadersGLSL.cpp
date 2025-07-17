#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersGLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_96_32",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 1 0
layout(location = 0)
out vec4 entryPointParam_main_var_2_0;


#line 1
layout(location = 0)
in vec3 input_var_0_0;


#line 1
layout(location = 1)
in vec4 input_var_1_0;


struct vertex_output_0
{
    vec4 var_2_0;
    vec4 position_output_0;
};


#line 10
void main()
{

#line 11
    vertex_output_0 output_0;
    output_0.position_output_0 = vec4(input_var_0_0, 1.0);
    output_0.var_2_0 = input_var_1_0;
    vertex_output_0 _S1 = output_0;

#line 14
    entryPointParam_main_var_2_0 = output_0.var_2_0;

#line 14
    gl_Position = _S1.position_output_0;

#line 14
    return;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_97_31",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 1 0
layout(location = 0)
out vec4 entryPointParam_main_var_1_0;


#line 1
layout(location = 0)
in vec4 input_var_0_0;

struct fragment_output_0
{
    vec4 var_1_0;
};


#line 8
void main()
{

#line 9
    fragment_output_0 output_0;
    output_0.var_1_0 = input_var_0_0;

#line 10
    entryPointParam_main_var_1_0 = output_0.var_1_0;

#line 10
    return;
}

 )")
},
};