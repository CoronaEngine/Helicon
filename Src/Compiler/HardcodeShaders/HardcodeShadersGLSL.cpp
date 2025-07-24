#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersGLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_171_35",
ShaderCodeModule(R"(#version 450
#extension GL_EXT_samplerless_texture_functions : require
layout(row_major) uniform;
layout(row_major) buffer;

#line 90 0
layout(std430, binding = 3) readonly buffer StructuredBuffer_vectorx3Cfloatx2C4x3E_t_0 {
    vec4 _data[];
} global_ubo_global_var_4_member3_0;

#line 13 1
struct global_push_constant_struct_std430_0
{
    uint global_var_1_0;
};


#line 15
layout(push_constant)
layout(std430) uniform block_global_push_constant_struct_std430_0
{
    uint global_var_1_0;
}global_push_constant_0;

#line 2
layout(std430, binding = 1) buffer StructuredBuffer_vectorx3Cfloatx2C4x3E_t_1 {
    vec4 _data[];
} global_var_3_0;

#line 1
layout(binding = 0)
uniform texture2D global_var_2_0;


#line 3621 2
layout(location = 0)
out vec4 entryPointParam_main_var_5_0;


#line 3621
layout(location = 1)
in vec4 input_var_0_color_0;


#line 23 1
struct vertex_output_0
{
    vec4 position_output_0;
    vec4 var_5_0;
};


#line 28
void main()
{
    vec4 var_1_0 = global_ubo_global_var_4_member3_0._data[uint(0)];



    var_1_0.xy = vec2(0.0, 0.0);

#line 42
    const uvec2 _S1 = uvec2(0U, 0U);

#line 42
    ;

#line 42
    ivec3 _S2 = ivec3(uvec3(_S1, 0U));

#line 42
    global_var_3_0._data[uint(global_push_constant_0.global_var_1_0)] = (texelFetch((global_var_2_0), ((_S2)).xy, ((_S2)).z));

#line 29
    vertex_output_0 output_0;

#line 43
    const uvec2 _S3 = uvec2(ivec2(0, 0));

#line 43
    ;

#line 43
    ivec3 _S4 = ivec3(uvec3(_S3, 0U));

#line 43
    output_0.position_output_0 = (texelFetch((global_var_2_0), ((_S4)).xy, ((_S4)).z));

    output_0.var_5_0 = input_var_0_color_0;
    vertex_output_0 _S5 = output_0;

#line 46
    gl_Position = output_0.position_output_0;

#line 46
    entryPointParam_main_var_5_0 = _S5.var_5_0;

#line 46
    return;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_172_34",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 20 0
layout(location = 0)
out vec4 entryPointParam_main_var_1_0;


#line 20
layout(location = 0)
in vec4 input_var_0_0;

struct fragment_output_0
{
    vec4 var_1_0;
};


#line 27
void main()
{

#line 28
    fragment_output_0 output_0;
    output_0.var_1_0 = input_var_0_0;

#line 29
    entryPointParam_main_var_1_0 = output_0.var_1_0;

#line 29
    return;
}

 )")
},
};