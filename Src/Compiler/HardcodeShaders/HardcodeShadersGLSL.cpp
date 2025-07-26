#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersGLSL = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_162_35",
ShaderCodeModule(R"(#version 450
layout(row_major) uniform;
layout(row_major) buffer;

#line 2 0
struct global_ubo_struct_std140_0
{
    vec4 global_var_1_0;
};


#line 22921 1
layout(binding = 2, set = 1)
layout(std140) uniform block_global_ubo_struct_std140_0
{
    vec4 global_var_1_0;
}_slang_resource_heap_0[];

#line 1 0
layout(std430, binding = 1) buffer StructuredBuffer_vectorx3Cfloatx2C4x3E_t_0 {
    vec4 _data[];
} global_var_2_0;

#line 22879 1
struct GlobalParams_std140_0
{
    uvec2 global_ubo_0;
};


#line 22879
layout(binding = 0)
layout(std140) uniform block_GlobalParams_std140_0
{
    uvec2 global_ubo_0;
}globalParams_0;

#line 15 0
layout(location = 0)
out vec4 entryPointParam_main_var_2_0;


#line 15
layout(location = 0)
in vec4 input_var_0_pos_0;


#line 15
layout(location = 1)
in vec4 input_var_0_color_0;


#line 2
struct aggregate_type_0_0
{
    vec4 pos_0;
    vec4 color_0;
};



struct vertex_input_0
{
    aggregate_type_0_0 var_0_0;
};


#line 13
struct vertex_output_0
{
    vec4 position_output_0;
    vec4 var_2_0;
};


#line 18
void main()
{

#line 18
    aggregate_type_0_0 _S1 = { input_var_0_pos_0, input_var_0_color_0 };

#line 18
    vertex_input_0 _S2;

#line 18
    _S2.var_0_0 = _S1;

#line 18
    uvec2 _S3 = globalParams_0.global_ubo_0;

    global_var_2_0._data[uint(0)] = _slang_resource_heap_0[globalParams_0.global_ubo_0.x].global_var_1_0;
    _S2.var_0_0.pos_0[0] = _slang_resource_heap_0[_S3.x].global_var_1_0.x;

#line 19
    vertex_output_0 output_0;


    output_0.position_output_0 = _S2.var_0_0.pos_0;

    output_0.var_2_0 = _S2.var_0_0.color_0;
    vertex_output_0 _S4 = output_0;

#line 25
    gl_Position = output_0.position_output_0;

#line 25
    entryPointParam_main_var_2_0 = _S4.var_2_0;

#line 25
    return;
}

 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_163_34",
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