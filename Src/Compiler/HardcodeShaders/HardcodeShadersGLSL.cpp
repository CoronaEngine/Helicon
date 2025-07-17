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
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_97_31",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 7 0
struct global_ubo_struct_std140_0
{
    vec4 global_var_0_0;
};


#line 6
layout(binding = 1)
layout(std140) uniform block_global_ubo_struct_std140_0
{
    vec4 global_var_0_0;
}global_ubo_0;

#line 2
layout(std430, binding = 0) readonly buffer StructuredBuffer_float_t_0 {
    float _data[];
} global_var_1_0;



layout(location = 0)
out vec4 entryPointParam_main_var_0_0;


#line 7
struct fragment_output_0
{
    vec4 var_0_0;
};


#line 11
void main()
{

#line 12
    fragment_output_0 output_0;
    output_0.var_0_0 = global_ubo_0.global_var_0_0;
    output_0.var_0_0[3] = global_var_1_0._data[uint(0)];

#line 14
    entryPointParam_main_var_0_0 = output_0.var_0_0;

#line 14
    return;
}

 )")
},
};