#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersGLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_164_32",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 6 0
layout(location = 0)
in vec3 input_var_0_0;

struct vertex_output_0
{
    vec4 position_output_0;
};


#line 13
void main()
{

#line 14
    vertex_output_0 output_0;
    output_0.position_output_0 = vec4(input_var_0_0, 1.0);

#line 15
    gl_Position = output_0.position_output_0;

#line 15
    return;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_165_31",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 6 0
struct global_ubo_struct_std140_0
{
    vec4 global_var_0_0;
};


#line 5
layout(binding = 0)
layout(std140) uniform block_global_ubo_struct_std140_0
{
    vec4 global_var_0_0;
}global_ubo_0;

#line 7
layout(location = 0)
out vec4 entryPointParam_main_var_0_0;


#line 6
struct fragment_output_0
{
    vec4 var_0_0;
};


#line 10
void main()
{

#line 11
    fragment_output_0 output_0;
    output_0.var_0_0 = global_ubo_0.global_var_0_0;

#line 12
    entryPointParam_main_var_0_0 = output_0.var_0_0;

#line 12
    return;
}

 )")
},
};