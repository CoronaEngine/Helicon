#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersGLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_165_35",
ShaderCodeModule(R"(#version 450
#extension GL_EXT_samplerless_texture_functions : require
layout(row_major) uniform;
layout(row_major) buffer;

#line 1 0
layout(binding = 0)
uniform texture2D global_var_2_0;


#line 3621 1
layout(location = 0)
out vec4 entryPointParam_main_var_4_0;


#line 3621
layout(location = 1)
in vec4 input_var_0_color_0;


#line 9 0
struct vertex_output_0
{
    vec4 position_output_0;
    vec4 var_4_0;
};


#line 14
void main()
{
    vec4 var_1_0 = vec4(1.0, 2.0, 3.0, 4.0);


    var_1_0.xy = vec2(0.0, 0.0);

#line 15
    vertex_output_0 output_0;

#line 26
    const uvec2 _S1 = uvec2(ivec2(0, 0));

#line 26
    ;

#line 26
    ivec3 _S2 = ivec3(uvec3(_S1, 0U));

#line 26
    output_0.position_output_0 = (texelFetch((global_var_2_0), ((_S2)).xy, ((_S2)).z));

    output_0.var_4_0 = input_var_0_color_0;
    vertex_output_0 _S3 = output_0;

#line 29
    gl_Position = output_0.position_output_0;

#line 29
    entryPointParam_main_var_4_0 = _S3.var_4_0;

#line 29
    return;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_166_34",
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