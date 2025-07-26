#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersGLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_50_35",
ShaderCodeModule(R"(#version 450
#extension GL_EXT_nonuniform_qualifier : require
layout(row_major) uniform;
layout(row_major) buffer;

#line 90 0
layout(binding = 2, set = 1)
uniform texture2D  _slang_resource_heap_0[];


#line 22921 1
layout(binding = 0, set = 1)
uniform sampler  _slang_resource_heap_1[];


#line 22879
struct global_ubo_struct_std140_0
{
    uvec2 global_var_1_0;
};


#line 22921
layout(binding = 2, set = 1)
layout(std140) uniform block_global_ubo_struct_std140_0
{
    uvec2 global_var_1_0;
}_slang_resource_heap_2[];

#line 22879
struct GlobalParams_std140_0
{
    uvec2 global_var_0_0;
    uvec2 global_ubo_0;
};


#line 22879
layout(binding = 0)
layout(std140) uniform block_GlobalParams_std140_0
{
    uvec2 global_var_0_0;
    uvec2 global_ubo_0;
}globalParams_0;

#line 1875
layout(location = 0)
out vec4 entryPointParam_main_var_1_0;


#line 1875
layout(location = 0)
in vec4 input_var_0_pos_0;


#line 1875
layout(location = 1)
in vec2 input_var_0_texCoord_0;


#line 13 2
struct vertex_output_0
{
    vec4 position_output_0;
    vec4 var_1_0;
};


#line 18
void main()
{

#line 19
    vertex_output_0 output_0;
    output_0.position_output_0 = input_var_0_pos_0;
    output_0.var_1_0 = (texture(sampler2D(_slang_resource_heap_0[globalParams_0.global_var_0_0.x],_slang_resource_heap_1[_slang_resource_heap_2[globalParams_0.global_ubo_0.x].global_var_1_0.x]), (input_var_0_texCoord_0)));
    vertex_output_0 _S1 = output_0;

#line 22
    gl_Position = output_0.position_output_0;

#line 22
    entryPointParam_main_var_1_0 = _S1.var_1_0;

#line 22
    return;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_51_34",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 10 0
layout(location = 0)
out vec4 entryPointParam_main_var_1_0;


#line 10
layout(location = 0)
in vec4 input_var_0_0;

struct fragment_output_0
{
    vec4 var_1_0;
};


#line 17
void main()
{

#line 18
    fragment_output_0 output_0;
    output_0.var_1_0 = input_var_0_0;

#line 19
    entryPointParam_main_var_1_0 = output_0.var_1_0;

#line 19
    return;
}

 )")
},
};