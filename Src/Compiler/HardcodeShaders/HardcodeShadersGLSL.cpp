#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersGLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_168_35",
ShaderCodeModule(R"(#version 450
#extension GL_EXT_samplerless_texture_functions : require
layout(row_major) uniform;
layout(row_major) buffer;

#line 8 0
struct global_push_constant_struct_std430_0
{
    uint global_var_1_0;
};


#line 10
layout(push_constant)
layout(std430) uniform block_global_push_constant_struct_std430_0
{
    uint global_var_1_0;
}global_push_constant_0;

#line 2
layout(std430, binding = 1) buffer StructuredBuffer_vectorx3Cfloatx2C4x3E_t_0 {
    vec4 _data[];
} global_var_3_0;

#line 1
layout(binding = 0)
uniform texture2D global_var_2_0;


#line 3621 1
layout(location = 0)
out vec4 entryPointParam_main_var_5_0;


#line 3621
layout(location = 1)
in vec4 input_var_0_color_0;


#line 14 0
struct vertex_output_0
{
    vec4 position_output_0;
    vec4 var_5_0;
};


#line 19
void main()
{
    vec4 var_1_0 = vec4(1.0, 2.0, 3.0, 4.0);


    var_1_0.xy = vec2(0.0, 0.0);

#line 32
    const uvec2 _S1 = uvec2(0U, 0U);

#line 32
    ;

#line 32
    ivec3 _S2 = ivec3(uvec3(_S1, 0U));

#line 32
    global_var_3_0._data[uint(global_push_constant_0.global_var_1_0)] = (texelFetch((global_var_2_0), ((_S2)).xy, ((_S2)).z));

#line 20
    vertex_output_0 output_0;

#line 33
    const uvec2 _S3 = uvec2(ivec2(0, 0));

#line 33
    ;

#line 33
    ivec3 _S4 = ivec3(uvec3(_S3, 0U));

#line 33
    output_0.position_output_0 = (texelFetch((global_var_2_0), ((_S4)).xy, ((_S4)).z));

    output_0.var_5_0 = input_var_0_color_0;
    vertex_output_0 _S5 = output_0;

#line 36
    gl_Position = output_0.position_output_0;

#line 36
    entryPointParam_main_var_5_0 = _S5.var_5_0;

#line 36
    return;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_169_34",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 11 0
layout(location = 0)
out vec4 entryPointParam_main_var_1_0;


#line 11
layout(location = 0)
in vec4 input_var_0_0;

struct fragment_output_0
{
    vec4 var_1_0;
};


#line 18
void main()
{

#line 19
    fragment_output_0 output_0;
    output_0.var_1_0 = input_var_0_0;

#line 20
    entryPointParam_main_var_1_0 = output_0.var_1_0;

#line 20
    return;
}

 )")
},
};