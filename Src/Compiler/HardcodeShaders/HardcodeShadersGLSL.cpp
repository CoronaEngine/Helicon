#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersGLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_100_32",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 7 0
struct global_ubo_struct_std140_0
{
    vec4 global_var_0_0;
    vec4 global_var_1_0;
    vec4 global_var_2_0;
};


#line 9
layout(binding = 0)
layout(std140) uniform block_global_ubo_struct_std140_0
{
    vec4 global_var_0_0;
    vec4 global_var_1_0;
    vec4 global_var_2_0;
}shader_ubo_0;

#line 15
layout(location = 0)
out vec4 entryPointParam_main_var_1_0;


#line 10
layout(location = 0)
in vec3 input_var_0_0;

struct vertex_output_0
{
    vec4 var_1_0;
    vec4 position_output_0;
};


#line 18
void main()
{

#line 19
    vertex_output_0 output_0;
    output_0.position_output_0 = vec4(input_var_0_0, 1.0);
    output_0.var_1_0 = shader_ubo_0.global_var_0_0;
    output_0.var_1_0 = shader_ubo_0.global_var_1_0;
    vertex_output_0 _S1 = output_0;

#line 23
    entryPointParam_main_var_1_0 = output_0.var_1_0;

#line 23
    gl_Position = _S1.position_output_0;

#line 23
    return;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_101_31",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 7 0
struct global_ubo_struct_std140_0
{
    vec4 global_var_0_0;
    vec4 global_var_1_0;
    vec4 global_var_2_0;
};


#line 9
layout(binding = 0)
layout(std140) uniform block_global_ubo_struct_std140_0
{
    vec4 global_var_0_0;
    vec4 global_var_1_0;
    vec4 global_var_2_0;
}shader_ubo_0;

#line 14
layout(location = 0)
out vec4 entryPointParam_main_var_1_0;


#line 13
struct fragment_output_0
{
    vec4 var_1_0;
};


#line 17
void main()
{

#line 18
    fragment_output_0 output_0;
    output_0.var_1_0 = shader_ubo_0.global_var_0_0;
    output_0.var_1_0 = shader_ubo_0.global_var_2_0;

#line 20
    entryPointParam_main_var_1_0 = output_0.var_1_0;

#line 20
    return;
}

 )")
},
};