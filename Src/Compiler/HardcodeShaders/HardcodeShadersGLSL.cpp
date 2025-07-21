#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersGLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_146_35",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 1 0
layout(std430, binding = 0) readonly buffer StructuredBuffer_vectorx3Cfloatx2C4x3E_t_0 {
    vec4 _data[];
} global_var_1_0;

#line 11
layout(location = 0)
out vec4 entryPointParam_main_var_3_0;


#line 11
layout(location = 1)
in vec4 input_var_0_color_0;


#line 9
struct vertex_output_0
{
    vec4 position_output_0;
    vec4 var_3_0;
};


#line 14
void main()
{

#line 15
    vertex_output_0 output_0;

    output_0.position_output_0 = global_var_1_0._data[uint(1)];

    output_0.var_3_0 = input_var_0_color_0;
    vertex_output_0 _S1 = output_0;

#line 20
    gl_Position = output_0.position_output_0;

#line 20
    entryPointParam_main_var_3_0 = _S1.var_3_0;

#line 20
    return;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_147_34",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 6 0
layout(location = 0)
out vec4 entryPointParam_main_var_1_0;


#line 6
layout(location = 0)
in vec4 input_var_0_0;

struct fragment_output_0
{
    vec4 var_1_0;
};


#line 13
void main()
{

#line 14
    fragment_output_0 output_0;
    output_0.var_1_0 = input_var_0_0;

#line 15
    entryPointParam_main_var_1_0 = output_0.var_1_0;

#line 15
    return;
}

 )")
},
};