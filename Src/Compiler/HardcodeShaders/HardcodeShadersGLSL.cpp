#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersGLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_152_35",
ShaderCodeModule(R"(#version 450
#extension GL_EXT_samplerless_texture_functions : require
layout(row_major) uniform;
layout(row_major) buffer;

#line 2 0
layout(std430, binding = 1) buffer StructuredBuffer_vectorx3Cfloatx2C4x3E_t_0 {
    vec4 _data[];
} global_var_2_0;

#line 1
layout(binding = 0)
uniform texture2D global_var_1_0;


#line 3621 1
layout(location = 0)
out vec4 entryPointParam_main_var_4_0;


#line 3621
layout(location = 1)
in vec4 input_var_0_color_0;


#line 10 0
struct vertex_output_0
{
    vec4 position_output_0;
    vec4 var_4_0;
};


#line 15
void main()
{



    const uvec2 _S1 = uvec2(ivec2(0, 0));

#line 20
    ;

#line 20
    ivec3 _S2 = ivec3(uvec3(_S1, 0U));

#line 20
    vec4 _S3 = (texelFetch((global_var_1_0), ((_S2)).xy, ((_S2)).z));

#line 20
    global_var_2_0._data[uint(0)] = _S3;

#line 16
    vertex_output_0 output_0;

#line 21
    ;

#line 21
    output_0.position_output_0 = _S3;

    output_0.var_4_0 = input_var_0_color_0;
    vertex_output_0 _S4 = output_0;

#line 24
    gl_Position = output_0.position_output_0;

#line 24
    entryPointParam_main_var_4_0 = _S4.var_4_0;

#line 24
    return;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_153_34",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 7 0
layout(location = 0)
out vec4 entryPointParam_main_var_1_0;


#line 7
layout(location = 0)
in vec4 input_var_0_0;

struct fragment_output_0
{
    vec4 var_1_0;
};


#line 14
void main()
{

#line 15
    fragment_output_0 output_0;
    output_0.var_1_0 = input_var_0_0;

#line 16
    entryPointParam_main_var_1_0 = output_0.var_1_0;

#line 16
    return;
}

 )")
},
};