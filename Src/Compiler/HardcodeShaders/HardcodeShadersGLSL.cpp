#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersGLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_95_32",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 9 0
struct vertex_ubo_struct_std140_0
{
    vec4 global_var_0_0;
};


#line 5
layout(binding = 0)
layout(std140) uniform block_vertex_ubo_struct_std140_0
{
    vec4 global_var_0_0;
}shader_ubo_0;

layout(location = 0)
out vec4 entryPointParam_main_var_1_0;


#line 6
layout(location = 0)
in vec3 input_var_0_0;

struct vertex_output_0
{
    vec4 var_1_0;
    vec4 position_output_0;
};


#line 14
void main()
{

#line 15
    vertex_output_0 output_0;
    output_0.position_output_0 = vec4(input_var_0_0, 1.0);
    output_0.var_1_0 = shader_ubo_0.global_var_0_0;
    vertex_output_0 _S1 = output_0;

#line 18
    entryPointParam_main_var_1_0 = output_0.var_1_0;

#line 18
    gl_Position = _S1.position_output_0;

#line 18
    return;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_96_31",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 2 0
layout(location = 0)
out vec4 entryPointParam_main_var_1_0;


#line 2
layout(location = 0)
in vec4 input_var_0_0;

struct fragment_output_0
{
    vec4 var_1_0;
};


#line 9
void main()
{

#line 10
    fragment_output_0 output_0;
    output_0.var_1_0 = input_var_0_0;

#line 11
    entryPointParam_main_var_1_0 = output_0.var_1_0;

#line 11
    return;
}

 )")
},
};