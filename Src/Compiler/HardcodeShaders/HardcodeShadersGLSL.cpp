#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersGLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_159_35",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 12 0
struct global_ubo_struct_std140_0
{
    vec4 global_var_1_0;
    uint global_var_2_0;
};


#line 2
layout(binding = 2)
layout(std140) uniform block_global_ubo_struct_std140_0
{
    vec4 global_var_1_0;
    uint global_var_2_0;
}global_ubo_0;

#line 1
layout(std430, binding = 3) buffer StructuredBuffer_vectorx3Cfloatx2C4x3E_t_0 {
    vec4 _data[];
} global_ubo_global_var_3_member_0;

layout(std430, binding = 1) buffer StructuredBuffer_Texture2D_t_0 {
    image2D _data[];
} global_var_5_0;

#line 4
layout(std430, binding = 0) buffer StructuredBuffer_vectorx3Cfloatx2C4x3E_t_1 {
    vec4 _data[];
} global_var_4_0;

#line 4305 1
layout(location = 0)
out vec4 entryPointParam_main_var_2_0;


#line 4305
layout(location = 0)
in vec4 input_var_0_pos_0;


#line 4305
layout(location = 1)
in vec4 input_var_0_color_0;


#line 6 0
struct aggregate_type_1_0
{
    vec4 pos_0;
    vec4 color_0;
};


#line 16
struct vertex_input_0
{
    aggregate_type_1_0 var_0_0;
};


#line 19
struct vertex_output_0
{
    vec4 position_output_0;
    vec4 var_2_0;
};


#line 24
void main()
{

#line 24
    aggregate_type_1_0 _S1 = { input_var_0_pos_0, input_var_0_color_0 };

#line 24
    vertex_input_0 _S2;

#line 24
    _S2.var_0_0 = _S1;

#line 24
    uint _S3 = global_ubo_0.global_var_2_0;

#line 24
    vec4 _S4 = global_ubo_0.global_var_1_0;

    imageStore((global_var_5_0._data[uint(global_ubo_0.global_var_2_0)]), (ivec2(uvec2(0U, 0U))), global_ubo_0.global_var_1_0);
    global_ubo_global_var_3_member_0._data[uint(_S3)] = _S4;
    global_var_4_0._data[uint(_S3)] = _S4;
    _S2.var_0_0.pos_0[0] = _S4.x;

#line 25
    vertex_output_0 output_0;

#line 30
    output_0.position_output_0 = _S2.var_0_0.pos_0;

    output_0.var_2_0 = _S2.var_0_0.color_0;
    vertex_output_0 _S5 = output_0;

#line 33
    gl_Position = output_0.position_output_0;

#line 33
    entryPointParam_main_var_2_0 = _S5.var_2_0;

#line 33
    return;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_160_34",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 16 0
layout(location = 0)
out vec4 entryPointParam_main_var_1_0;


#line 16
layout(location = 0)
in vec4 input_var_0_0;

struct fragment_output_0
{
    vec4 var_1_0;
};


#line 23
void main()
{

#line 24
    fragment_output_0 output_0;
    output_0.var_1_0 = input_var_0_0;

#line 25
    entryPointParam_main_var_1_0 = output_0.var_1_0;

#line 25
    return;
}

 )")
},
};