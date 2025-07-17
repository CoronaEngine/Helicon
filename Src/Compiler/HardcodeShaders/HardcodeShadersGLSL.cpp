#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersGLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_97_32",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 6 0
struct vertex_ssbo_struct_std430_0
{
    vec4 global_var_0_0;
};


#line 5
layout(std430, binding = 0) buffer StructuredBuffer_vertex_ssbo_struct_std430_t_0 {
    vertex_ssbo_struct_std430_0 _data[];
} shader_ssbo_0;

#line 12
layout(location = 0)
out vec4 entryPointParam_main_var_2_0;


#line 6
layout(location = 0)
in vec3 input_var_0_0;


#line 6
layout(location = 1)
in vec4 input_var_1_0;


struct vertex_output_0
{
    vec4 var_2_0;
    vec4 position_output_0;
};


#line 15
void main()
{

#line 16
    vertex_output_0 output_0;
    output_0.position_output_0 = vec4(input_var_0_0, 1.0);
    output_0.var_2_0 = input_var_1_0;
    shader_ssbo_0._data[uint(0)].global_var_0_0 = input_var_1_0;
    vertex_output_0 _S1 = output_0;

#line 20
    entryPointParam_main_var_2_0 = output_0.var_2_0;

#line 20
    gl_Position = _S1.position_output_0;

#line 20
    return;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_98_31",
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