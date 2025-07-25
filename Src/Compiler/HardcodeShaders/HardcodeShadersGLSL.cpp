#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersGLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_188_35",
ShaderCodeModule(R"(#version 450
#extension GL_EXT_samplerless_texture_functions : require
layout(row_major) uniform;
layout(row_major) buffer;

#line 90 0
layout(rgba32f)
layout(binding = 4)
uniform image2D global_ubo_global_var_3_member4_0;


#line 2 1
layout(std430, binding = 1) readonly buffer StructuredBuffer_Texture2D_t_0 {
    texture2D _data[];
} global_var_2_0;

#line 1
layout(rgba32f)
layout(binding = 0)
uniform image2D global_var_1_0;


#line 4138 2
layout(location = 0)
out vec4 entryPointParam_main_var_5_0;


#line 4138
layout(location = 1)
in vec4 input_var_0_color_0;


#line 20 1
struct vertex_output_0
{
    vec4 position_output_0;
    vec4 var_5_0;
};


#line 25
void main()
{
    const vec4 _S1 = vec4(1.0, 2.0, 3.0, 4.0);

#line 27
    vec4 var_1_0 = _S1;
    const uvec2 _S2 = uvec2(0U, 0U);

#line 28
    ivec2 _S3 = ivec2(_S2);

#line 28
    imageStore((global_ubo_global_var_3_member4_0), (_S3), _S1);



    var_1_0.xy = vec2(0.0, 0.0);

#line 39
    ;

#line 39
    ivec3 _S4 = ivec3(uvec3(_S2, 0U));

#line 39
    imageStore((global_var_1_0), (_S3), (texelFetch((global_var_2_0._data[uint(0)]), ((_S4)).xy, ((_S4)).z)));

#line 26
    vertex_output_0 output_0;

#line 40
    vec4 _S5 = (imageLoad((global_var_1_0), (ivec2(uvec2(ivec2(0, 0))))));

#line 40
    output_0.position_output_0 = _S5;

    output_0.var_5_0 = input_var_0_color_0;
    vertex_output_0 _S6 = output_0;

#line 43
    gl_Position = output_0.position_output_0;

#line 43
    entryPointParam_main_var_5_0 = _S6.var_5_0;

#line 43
    return;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_189_34",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 17 0
layout(location = 0)
out vec4 entryPointParam_main_var_7_0;


#line 17
layout(location = 0)
in vec4 input_var_0_0;

struct fragment_output_0
{
    vec4 var_7_0;
};


#line 24
void main()
{

#line 25
    fragment_output_0 output_0;

#line 37
    output_0.var_7_0 = input_var_0_0;

#line 37
    entryPointParam_main_var_7_0 = output_0.var_7_0;

#line 37
    return;
}

 )")
},
};