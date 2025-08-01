#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersFragmentShader = {{"SpirV_D__Files_Code_Projects_Helicon_Examples_main_cpp", ShaderCodeModule(std::vector<uint32_t>{119734787,66816,2621440,340,0,131089,5302,131089,1,393227,104,1280527431,1685353262,808793134,0,196622,0,1,917519,4,2,1852399981,0,42,69,59,331,19,21,25,27,32,196624,2,7,196611,11,1,262149,12,1601331574,49,262149,12,1601331574,49,458757,19,1970302569,1635135092,774922098,1734439526,7565136,524293,21,1970302569,1635135092,774922098,1734439526,1836216142,27745,589829,25,1970302569,1635135092,774922098,1734439526,1131963732,1685221231,0,524293,27,1970302569,1635135092,774922098,1734439526,1869377347,114,458757,28,1651469383,1632660577,1936548210,1685353311,3159089,458758,28,0,1651469415,1985965153,929002081,0,393222,28,1,1651469415,1969187937,28514,393221,32,1651469415,1632660577,1936548210,0,524293,42,1819500383,1600613985,1869833586,1701016181,1634035807,112,786437,52,1952533855,1400400242,1634889588,1717527911,1952542572,1597274164,1298952003,1919904353,828666995,12340,327686,52,0,1635017060,0,786437,55,1952533855,1400400242,1634889588,1717527911,1952542572,1597208627,1298952003,1919904353,828666995,12340,327686,55,0,1635017060,0,589829,51,1651469415,1969187937,1935634274,1668641396,1953718132,808726884,0,458758,51,0,1651469415,1985965153,811561569,0,458758,51,1,1651469415,1985965153,828338785,0,458758,51,2,1651469415,1985965153,845116001,0,458758,51,3,1651469415,1985965153,861893217,0,458758,51,4,1651469415,1985965153,878670433,0,458758,51,5,1651469415,1985965153,895447649,0,458758,51,6,1651469415,1985965153,912224865,0,458758,51,7,1651469415,1985965153,962556513,0,524293,59,1819500383,1600613985,1869833586,1701016181,1634035807,112,524293,69,1819500383,1600613985,1869833586,1701016181,1634035807,112,393221,75,1886216563,1231316332,1701273965,0,262149,76,1886216563,6579564,393221,96,1886216563,1231316332,1701273965,0,262149,97,1886216563,6579564,262149,188,1601331574,12849,262149,234,1601331574,14130,589829,331,1920233061,1768902777,1632662638,1601003890,1852399981,1918989870,3289951,262149,2,1852399981,0,262215,19,30,0,262215,21,30,1,262215,25,30,2,262215,27,30,3,196679,28,2,327752,28,0,35,0,327752,28,1,35,8,262215,32,33,0,262215,32,34,0,262215,42,33,2,262215,42,34,1,262215,53,6,16,327752,52,0,35,0,262215,56,6,16,327752,55,0,35,0,196679,51,2,327752,51,0,35,0,327752,51,1,35,64,327752,51,2,35,112,327752,51,3,35,176,327752,51,4,35,240,327752,51,5,35,256,327752,51,6,35,272,327752,51,7,35,288,262215,59,33,2,262215,59,34,1,262215,69,33,0,262215,69,34,1,262215,331,30,0,131091,1,196641,3,1,196630,6,32,262167,7,6,4,262167,10,6,3,262176,11,7,10,262176,18,1,10,262167,22,6,2,262176,24,1,22,262165,29,32,0,262167,30,29,2,262174,28,30,30,262176,31,2,28,262165,33,32,1,262187,33,34,0,262176,35,2,30,589849,40,6,1,2,0,0,1,0,196637,39,40,262176,41,0,39,262176,43,0,40,262187,33,46,1,262187,33,54,4,262172,53,7,54,196638,52,53,262187,33,57,3,262172,56,10,57,196638,55,56,655390,51,52,55,52,52,10,10,10,30,196637,50,51,262176,58,2,50,262176,60,2,51,262187,33,62,7,131098,67,196637,66,67,262176,68,0,66,262176,70,0,67,196635,74,40,131092,79,262187,6,81,1008981770,262187,6,106,1025758986,393260,10,105,106,106,106,262187,6,108,1056964608,393260,10,107,108,108,108,262176,113,2,10,262187,33,120,6,262187,6,129,0,262187,6,148,3211788288,262187,6,150,1065353216,262187,6,152,1078530012,393260,10,206,150,150,150,262187,6,232,1084227584,262187,6,241,1031798784,262187,6,243,1060634624,262187,6,245,1049624576,262187,6,289,1082130432,262187,6,300,953267991,262187,33,306,5,262187,6,324,1022739087,393260,10,323,324,324,324,262176,330,3,7,262203,18,19,1,262203,18,21,1,262203,24,25,1,262203,18,27,1,262203,31,32,2,262203,41,42,0,262203,58,59,2,262203,68,69,0,262203,330,331,3,262187,6,338,1050868098,393260,10,339,338,338,338,327734,1,2,0,3,131320,4,262203,11,12,7,262205,10,17,19,262205,10,20,21,262205,22,23,25,262205,10,26,27,327746,35,36,32,34,262205,30,37,36,327761,29,38,37,0,327745,43,44,42,38,327746,35,47,32,46,262205,30,48,47,327761,29,49,48,0,327745,60,61,59,49,327746,35,63,61,62,262205,30,64,63,327761,29,65,64,0,327745,70,71,69,65,262205,40,72,44,262205,67,73,71,327766,74,75,72,73,393303,7,76,75,23,0,327761,6,78,76,3,327866,79,80,78,81,196855,15,0,262394,80,14,13,131320,13,196670,12,26,131321,15,131320,14,327761,29,85,37,0,327745,43,86,42,85,327761,29,88,48,0,327745,60,89,59,88,327746,35,90,89,62,262205,30,91,90,327761,29,92,91,0,327745,70,93,69,92,262205,40,94,86,262205,67,95,93,327766,74,96,94,95,393303,7,97,96,23,0,524367,10,99,97,97,0,1,2,196670,12,99,131321,15,131320,15,262205,10,102,12,524300,10,103,104,46,105,102,107,393228,10,109,104,69,20,131321,16,131320,16,327761,29,111,48,0,327745,60,112,59,111,327746,113,114,112,54,262205,10,115,114,327811,10,116,115,17,393228,10,117,104,69,116,327761,29,118,48,0,327745,60,119,59,118,327746,113,121,119,120,262205,10,122,121,327811,10,123,122,17,393228,10,124,104,69,123,327809,10,125,117,124,393228,10,126,104,69,125,327828,6,127,109,126,458764,6,128,104,40,127,129,327761,29,130,48,0,327745,60,131,59,130,327746,113,132,131,54,262205,10,133,132,327811,10,134,133,17,393228,10,135,104,69,134,327761,29,136,48,0,327745,60,137,59,136,327746,113,138,137,120,262205,10,139,138,327811,10,140,139,17,393228,10,141,104,69,140,327809,10,142,135,141,393228,10,143,104,69,142,327828,6,144,109,143,458764,6,145,104,40,144,129,327813,6,146,128,145,327813,6,147,146,148,327809,6,149,147,150,327813,6,151,152,149,327761,29,153,48,0,327745,60,154,59,153,327746,113,155,154,54,262205,10,156,155,327811,10,157,156,17,393228,10,158,104,69,157,327761,29,159,48,0,327745,60,160,59,159,327746,113,161,160,120,262205,10,162,161,327811,10,163,162,17,393228,10,164,104,69,163,327809,10,165,158,164,393228,10,166,104,69,165,327828,6,167,109,166,458764,6,168,104,40,167,129,327761,29,169,48,0,327745,60,170,59,169,327746,113,171,170,54,262205,10,172,171,327811,10,173,172,17,393228,10,174,104,69,173,327761,29,175,48,0,327745,60,176,59,175,327746,113,177,176,120,262205,10,178,177,327811,10,179,178,17,393228,10,180,104,69,179,327809,10,181,174,180,393228,10,182,104,69,181,327828,6,183,109,182,458764,6,184,104,40,183,129,327813,6,185,168,184,327813,6,186,185,148,327809,6,187,186,150,327813,6,188,151,187,327761,29,189,48,0,327745,60,190,59,189,327746,113,191,190,54,262205,10,192,191,327811,10,193,192,17,393228,10,194,104,69,193,327828,6,195,109,194,458764,6,196,104,40,195,129,327761,29,197,48,0,327745,60,198,59,197,327746,113,199,198,120,262205,10,200,199,327811,10,201,200,17,393228,10,202,104,69,201,327828,6,203,109,202,458764,6,204,104,40,203,129,327811,10,205,206,103,327761,29,207,48,0,327745,60,208,59,207,327746,113,209,208,54,262205,10,210,209,327811,10,211,210,17,393228,10,212,104,69,211,327761,29,213,48,0,327745,60,214,59,213,327746,113,215,214,120,262205,10,216,215,327811,10,217,216,17,393228,10,218,104,69,217,327809,10,219,212,218,393228,10,220,104,69,219,327761,29,221,48,0,327745,60,222,59,221,327746,113,223,222,54,262205,10,224,223,327811,10,225,224,17,393228,10,226,104,69,225,327828,6,227,220,226,524300,6,228,104,43,227,129,150,327811,6,229,150,228,524300,6,230,104,43,229,129,150,458764,6,231,104,26,230,232,327822,10,233,205,231,327809,10,234,103,233,327811,10,235,206,234,262205,10,236,12,327813,10,237,235,236,327813,10,239,237,339,327816,6,240,241,188,327813,6,242,204,243,327809,6,244,242,245,327816,6,246,204,244,327813,6,247,196,243,327809,6,248,247,245,327816,6,249,196,248,327813,6,250,246,249,327813,6,251,240,250,327761,29,252,48,0,327745,60,253,59,252,327746,113,254,253,54,262205,10,255,254,327811,10,256,255,17,393228,10,257,104,69,256,327761,29,258,48,0,327745,60,259,59,258,327746,113,260,259,120,262205,10,261,260,327811,10,262,261,17,393228,10,263,104,69,262,327809,10,264,257,263,393228,10,265,104,69,264,327761,29,266,48,0,327745,60,267,59,266,327746,113,268,267,54,262205,10,269,268,327811,10,270,269,17,393228,10,271,104,69,270,327828,6,272,265,271,524300,6,273,104,43,272,129,150,327811,6,274,150,273,524300,6,275,104,43,274,129,150,458764,6,276,104,26,275,232,327822,10,277,205,276,327809,10,278,103,277,327822,10,279,278,251,327761,29,280,48,0,327745,60,281,59,280,327746,113,282,281,54,262205,10,283,282,327811,10,284,283,17,393228,10,285,104,69,284,327828,6,286,109,285,458764,6,287,104,40,286,129,327813,6,288,289,287,327761,29,290,48,0,327745,60,291,59,290,327746,113,292,291,120,262205,10,293,292,327811,10,294,293,17,393228,10,295,104,69,294,327828,6,296,109,295,458764,6,297,104,40,296,129,327813,6,298,288,297,327809,6,299,298,300,393296,10,301,299,299,299,327816,10,302,279,301,327809,10,303,239,302,327761,29,304,48,0,327745,60,305,59,304,327746,113,307,305,306,262205,10,308,307,327813,10,309,303,308,327761,29,310,48,0,327745,60,311,59,310,327746,113,312,311,120,262205,10,313,312,327811,10,314,313,17,393228,10,315,104,69,314,327828,6,316,109,315,458764,6,317,104,40,316,129,327822,10,318,309,317,327813,10,322,323,236,327809,10,325,322,318,327760,7,326,325,150,196670,331,326,65789,65592,},{0,"",{{"entryPointParam_main.var_32",{0,0,0,"entryPointParam_main.var_32","float",4,16,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(2)}},{"input.var_0.fragTexCoord",{0,0,2,"input.var_0.fragTexCoord","float",2,8,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(1)}},{"GlobalParams_std140",{0,0,0,"GlobalParams_std140","uniform",2,16,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(3)}},{"global_ubo_struct_std140",{1,2,0,"global_ubo_struct_std140","uniform",8,296,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(3)}},{"input.var_0.fragPos",{0,0,0,"input.var_0.fragPos","float",3,12,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(1)}},{"input.var_0.fragNormal",{0,0,1,"input.var_0.fragNormal","float",3,12,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(1)}},{"input.var_0.fragColor",{0,0,3,"input.var_0.fragColor","float",3,12,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(1)}},}}),},{"GLSL_D__Files_Code_Projects_Helicon_Examples_main_cpp", ShaderCodeModule(R"(#version 450
#extension GL_EXT_nonuniform_qualifier : require
layout(row_major) uniform;
layout(row_major) buffer;

#line 90 0
layout(binding = 2, set = 1)
uniform texture2D  _slang_resource_heap_0[];


#line 22921 1
layout(binding = 0, set = 1)
uniform sampler  _slang_resource_heap_1[];


#line 15 2
struct _MatrixStorage_float4x4_ColMajorstd140_0
{
    vec4  data_0[4];
};


#line 12399 1
struct _MatrixStorage_float3x3_ColMajorstd140_0
{
    vec3  data_1[3];
};


#line 22879
struct global_ubo_struct_std140_0
{
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_0_0;
    _MatrixStorage_float3x3_ColMajorstd140_0 global_var_1_0;
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_2_0;
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_3_0;
    vec3 global_var_4_0;
    vec3 global_var_5_0;
    vec3 global_var_6_0;
    uvec2 global_var_9_0;
};


#line 22921
layout(binding = 2, set = 1)
layout(std140) uniform block_global_ubo_struct_std140_0
{
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_0_0;
    _MatrixStorage_float3x3_ColMajorstd140_0 global_var_1_0;
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_2_0;
    _MatrixStorage_float4x4_ColMajorstd140_0 global_var_3_0;
    vec3 global_var_4_0;
    vec3 global_var_5_0;
    vec3 global_var_6_0;
    uvec2 global_var_9_0;
}_slang_resource_heap_2[];

#line 22879
struct GlobalParams_std140_0
{
    uvec2 global_var_7_0;
    uvec2 global_ubo_0;
};


#line 22879
layout(binding = 0)
layout(std140) uniform block_GlobalParams_std140_0
{
    uvec2 global_var_7_0;
    uvec2 global_ubo_0;
}globalParams_0;

#line 12442
layout(location = 0)
out vec4 entryPointParam_main_var_32_0;


#line 12442
layout(location = 0)
in vec3 input_var_0_fragPos_0;


#line 12442
layout(location = 1)
in vec3 input_var_0_fragNormal_0;


#line 12442
layout(location = 2)
in vec2 input_var_0_fragTexCoord_0;


#line 12442
layout(location = 3)
in vec3 input_var_0_fragColor_0;


#line 28 2
struct fragment_output_0
{
    vec4 var_32_0;
};


#line 32
void main()
{

#line 33
    fragment_output_0 output_0;

#line 33
    uvec2 _S1 = globalParams_0.global_var_7_0;

#line 33
    uvec2 _S2 = globalParams_0.global_ubo_0;

#line 33
    vec3 var_1_0;

    if(((texture(sampler2D(_slang_resource_heap_0[globalParams_0.global_var_7_0.x],_slang_resource_heap_1[_slang_resource_heap_2[globalParams_0.global_ubo_0.x].global_var_9_0.x]), (input_var_0_fragTexCoord_0))).w) > 0.00999999977648258)
    {

#line 35
        var_1_0 = (texture(sampler2D(_slang_resource_heap_0[_S1.x],_slang_resource_heap_1[_slang_resource_heap_2[_S2.x].global_var_9_0.x]), (input_var_0_fragTexCoord_0))).xyz;

#line 35
    }
    else
    {

#line 35
        var_1_0 = input_var_0_fragColor_0;

#line 35
    }

#line 44
    vec3 var_4_0 = mix(vec3(0.03999999910593033, 0.03999999910593033, 0.03999999910593033), var_1_0, vec3(0.5));

#line 52
    vec3 _S3 = normalize(input_var_0_fragNormal_0);
    float var_13_0 = max(dot(_S3, normalize(_slang_resource_heap_2[_S2.x].global_var_4_0 - input_var_0_fragPos_0)), 0.0);

#line 58
    float var_18_0 = max(dot(_S3, normalize(_slang_resource_heap_2[_S2.x].global_var_6_0 - input_var_0_fragPos_0)), 0.0);

#line 64
    const vec3 var_24_0 = vec3(1.0, 1.0, 1.0);


    vec3 _S4 = var_24_0 - var_4_0;

#line 73
    output_0.var_32_0 = vec4(vec3(0.02999999932944775, 0.02999999932944775, 0.02999999932944775) * var_1_0 + ((var_24_0 - (var_4_0 + _S4 * pow(clamp(1.0 - clamp(dot(normalize(normalize(_slang_resource_heap_2[_S2.x].global_var_4_0 - input_var_0_fragPos_0) + normalize(_slang_resource_heap_2[_S2.x].global_var_6_0 - input_var_0_fragPos_0)), normalize(_slang_resource_heap_2[_S2.x].global_var_4_0 - input_var_0_fragPos_0)), 0.0, 1.0), 0.0, 1.0), 5.0))) * var_1_0 / 3.14159297943115234 + 0.0625 / (3.14159297943115234 * (max(dot(_S3, normalize(normalize(_slang_resource_heap_2[_S2.x].global_var_4_0 - input_var_0_fragPos_0) + normalize(_slang_resource_heap_2[_S2.x].global_var_6_0 - input_var_0_fragPos_0))), 0.0) * max(dot(_S3, normalize(normalize(_slang_resource_heap_2[_S2.x].global_var_4_0 - input_var_0_fragPos_0) + normalize(_slang_resource_heap_2[_S2.x].global_var_6_0 - input_var_0_fragPos_0))), 0.0) * -0.9375 + 1.0) * (max(dot(_S3, normalize(normalize(_slang_resource_heap_2[_S2.x].global_var_4_0 - input_var_0_fragPos_0) + normalize(_slang_resource_heap_2[_S2.x].global_var_6_0 - input_var_0_fragPos_0))), 0.0) * max(dot(_S3, normalize(normalize(_slang_resource_heap_2[_S2.x].global_var_4_0 - input_var_0_fragPos_0) + normalize(_slang_resource_heap_2[_S2.x].global_var_6_0 - input_var_0_fragPos_0))), 0.0) * -0.9375 + 1.0)) * (var_18_0 / (var_18_0 * 0.71875 + 0.28125) * (var_13_0 / (var_13_0 * 0.71875 + 0.28125))) * (var_4_0 + _S4 * pow(clamp(1.0 - clamp(dot(normalize(normalize(_slang_resource_heap_2[_S2.x].global_var_4_0 - input_var_0_fragPos_0) + normalize(_slang_resource_heap_2[_S2.x].global_var_6_0 - input_var_0_fragPos_0)), normalize(_slang_resource_heap_2[_S2.x].global_var_4_0 - input_var_0_fragPos_0)), 0.0, 1.0), 0.0, 1.0), 5.0)) / (4.0 * max(dot(_S3, normalize(_slang_resource_heap_2[_S2.x].global_var_4_0 - input_var_0_fragPos_0)), 0.0) * max(dot(_S3, normalize(_slang_resource_heap_2[_S2.x].global_var_6_0 - input_var_0_fragPos_0)), 0.0) + 0.00009999999747379)) * _slang_resource_heap_2[_S2.x].global_var_5_0 * max(dot(_S3, normalize(_slang_resource_heap_2[_S2.x].global_var_6_0 - input_var_0_fragPos_0)), 0.0), 1.0);

#line 73
    entryPointParam_main_var_32_0 = output_0.var_32_0;

#line 73
    return;
}

)",{0,"",{{"entryPointParam_main.var_32",{0,0,0,"entryPointParam_main.var_32","float",4,16,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(2)}},{"input.var_0.fragTexCoord",{0,0,2,"input.var_0.fragTexCoord","float",2,8,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(1)}},{"GlobalParams_std140",{0,0,0,"GlobalParams_std140","uniform",2,16,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(3)}},{"global_ubo_struct_std140",{1,2,0,"global_ubo_struct_std140","uniform",8,296,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(3)}},{"input.var_0.fragPos",{0,0,0,"input.var_0.fragPos","float",3,12,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(1)}},{"input.var_0.fragNormal",{0,0,1,"input.var_0.fragNormal","float",3,12,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(1)}},{"input.var_0.fragColor",{0,0,3,"input.var_0.fragColor","float",3,12,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(1)}},}}),},{"HLSL_D__Files_Code_Projects_Helicon_Examples_main_cpp", ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 14 "0b013cac2bbb006311909e1f8466712f91e3d97f"
struct global_ubo_struct_0
{
    float4x4 global_var_0_0;
    float3x3 global_var_1_0;
    float4x4 global_var_2_0;
    float4x4 global_var_3_0;
    float3 global_var_4_0;
    float3 global_var_5_0;
    float3 global_var_6_0;
    uint2 global_var_9_0;
};


#line 22879 "hlsl.meta.slang"
struct GlobalParams_0
{
    uint2 global_var_7_0;
    uint2 global_ubo_0;
};


#line 22879
cbuffer globalParams_0 : register(b0)
{
    GlobalParams_0 globalParams_0;
}

#line 28 "0b013cac2bbb006311909e1f8466712f91e3d97f"
struct fragment_output_0
{
    float4 var_32_0 : SV_TARGET0;
};


#line 8
struct aggregate_type_1_0
{
    float3 fragPos_0;
    float3 fragNormal_0;
    float2 fragTexCoord_0;
    float3 fragColor_0;
};


#line 25
struct fragment_input_0
{
    aggregate_type_1_0 var_0_0 : LOCATION0;
};



fragment_output_0 main(fragment_input_0 input_0)
{

#line 32
    fragment_input_0 _S1 = input_0;
    fragment_output_0 output_0;

    Texture2D<float4 > _S2 = Texture2D<float4 >(ResourceDescriptorHeap[globalParams_0.global_var_7_0.x]);

#line 35
    SamplerState _S3 = SamplerState(SamplerDescriptorHeap[ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_9_0.x]);

#line 35
    float3 var_1_0;

#line 35
    if((_S2.Sample(_S3, _S1.var_0_0.fragTexCoord_0).w) > 0.00999999977648258f)
    {

#line 36
        Texture2D<float4 > _S4 = Texture2D<float4 >(ResourceDescriptorHeap[globalParams_0.global_var_7_0.x]);

#line 36
        SamplerState _S5 = SamplerState(SamplerDescriptorHeap[ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_9_0.x]);

#line 36
        var_1_0 = _S4.Sample(_S5, _S1.var_0_0.fragTexCoord_0).xyz;

#line 35
    }
    else
    {

#line 35
        var_1_0 = _S1.var_0_0.fragColor_0;

#line 35
    }

#line 44
    float3 var_4_0 = lerp(float3(0.03999999910593033f, 0.03999999910593033f, 0.03999999910593033f), var_1_0, (float3)0.5f);

#line 52
    float3 _S6 = normalize(_S1.var_0_0.fragNormal_0);

#line 52
    float3 _S7 = normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0);

#line 52
    float _S8 = max(dot(_S6, normalize(_S7 + normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_6_0 - _S1.var_0_0.fragPos_0))), 0.0f);

#line 52
    float3 _S9 = normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0);

#line 52
    float _S10 = 3.14159297943115234f * (_S8 * max(dot(_S6, normalize(_S9 + normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_6_0 - _S1.var_0_0.fragPos_0))), 0.0f) * -0.9375f + 1.0f);

#line 52
    float3 _S11 = normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0);

#line 52
    float _S12 = max(dot(_S6, normalize(_S11 + normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_6_0 - _S1.var_0_0.fragPos_0))), 0.0f);

#line 52
    float3 _S13 = normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0);

#line 52
    float var_12_0 = _S10 * (_S12 * max(dot(_S6, normalize(_S13 + normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_6_0 - _S1.var_0_0.fragPos_0))), 0.0f) * -0.9375f + 1.0f);
    float var_13_0 = max(dot(_S6, normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0)), 0.0f);

#line 58
    float var_18_0 = max(dot(_S6, normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_6_0 - _S1.var_0_0.fragPos_0)), 0.0f);

#line 64
    float3 var_24_0 = float3(1.0f, 1.0f, 1.0f);


    float3 _S14 = var_24_0 - var_4_0;

#line 67
    float3 _S15 = normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0);

#line 67
    float3 _S16 = normalize(_S15 + normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_6_0 - _S1.var_0_0.fragPos_0));



    float3 _S17 = (var_24_0 - (var_4_0 + _S14 * pow(clamp(1.0f - clamp(dot(_S16, normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0)), 0.0f, 1.0f), 0.0f, 1.0f), 5.0f))) * var_1_0 / 3.14159297943115234f;

#line 71
    float _S18 = 0.0625f / var_12_0 * (var_18_0 / (var_18_0 * 0.71875f + 0.28125f) * (var_13_0 / (var_13_0 * 0.71875f + 0.28125f)));

#line 71
    float3 _S19 = normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0);

#line 71
    float3 _S20 = normalize(_S19 + normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_6_0 - _S1.var_0_0.fragPos_0));

#line 71
    float3 _S21 = _S18 * (var_4_0 + _S14 * pow(clamp(1.0f - clamp(dot(_S20, normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0)), 0.0f, 1.0f), 0.0f, 1.0f), 5.0f));

#line 71
    float _S22 = 4.0f * max(dot(_S6, normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_4_0 - _S1.var_0_0.fragPos_0)), 0.0f);

#line 71
    float3 _S23 = _S17 + _S21 / (_S22 * max(dot(_S6, normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_6_0 - _S1.var_0_0.fragPos_0)), 0.0f) + 0.00009999999747379f);

#line 71
    float3 _S24 = _S23 * ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_5_0;

    output_0.var_32_0 = float4(float3(0.02999999932944775f, 0.02999999932944775f, 0.02999999932944775f) * var_1_0 + _S24 * max(dot(_S6, normalize(ConstantBuffer<global_ubo_struct_0 >(ResourceDescriptorHeap[globalParams_0.global_ubo_0.x]).global_var_6_0 - _S1.var_0_0.fragPos_0)), 0.0f), 1.0f);
    return output_0;
}

)",{0,"",{{"entryPointParam_main.var_32",{0,0,0,"entryPointParam_main.var_32","float",4,16,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(2)}},{"input.var_0.fragTexCoord",{0,0,2,"input.var_0.fragTexCoord","float",2,8,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(1)}},{"GlobalParams_std140",{0,0,0,"GlobalParams_std140","uniform",2,16,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(3)}},{"global_ubo_struct_std140",{1,2,0,"global_ubo_struct_std140","uniform",8,296,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(3)}},{"input.var_0.fragPos",{0,0,0,"input.var_0.fragPos","float",3,12,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(1)}},{"input.var_0.fragNormal",{0,0,1,"input.var_0.fragNormal","float",3,12,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(1)}},{"input.var_0.fragColor",{0,0,3,"input.var_0.fragColor","float",3,12,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(1)}},}}),},{"Slang_D__Files_Code_Projects_Helicon_Examples_main_cpp", ShaderCodeModule(R"(uniform Texture2D<float4>.Handle global_var_7;
struct aggregate_type_0 {
	float3 inPosition;
	float3 inNormal;
	float2 inTexCoord;
	float3 inColor;
}
struct aggregate_type_1 {
	float3 fragPos;
	float3 fragNormal;
	float2 fragTexCoord;
	float3 fragColor;
}
struct global_ubo_struct {
	float4x4 global_var_0;
	float3x3 global_var_1;
	float4x4 global_var_2;
	float4x4 global_var_3;
	float3 global_var_4;
	float3 global_var_5;
	float3 global_var_6;
	SamplerState.Handle global_var_9;
}
uniform ConstantBuffer<global_ubo_struct>.Handle global_ubo;
struct fragment_input {
	aggregate_type_1 var_0 : LOCATION0;
}
struct fragment_output {
	float4 var_32 : SV_TARGET0;
}
[shader("fragment")]
fragment_output main(fragment_input input) {
	fragment_output output;
	float3 var_1 = float3(0.000000, 0.000000, 0.000000);
	if ((global_var_7.Sample((*global_ubo).global_var_9,input.var_0.fragTexCoord).w > 0.010000)) {
		var_1 = global_var_7.Sample((*global_ubo).global_var_9,input.var_0.fragTexCoord).xyz;
	}
	else {
		var_1 = input.var_0.fragColor;
	}
	float var_2 = 0.500000;
	float var_3 = 0.500000;
	float3 var_4 = float3(0.040000, 0.040000, 0.040000);
	var_4 = lerp(var_4,var_1,var_3);
	float3 var_5 = float3(0.000000, 0.000000, 0.000000);
	float var_6 = 1.000000;
	float var_7 = var_2;
	float var_8 = ((var_7 * var_7) * (var_7 * var_7));
	float var_9 = 1.000000;
	float var_10 = 1.000000;
	float var_11 = 3.141593;
	float var_12 = ((var_11 * (((max(dot(normalize(input.var_0.fragNormal),normalize((normalize(((*global_ubo).global_var_4 - input.var_0.fragPos)) + normalize(((*global_ubo).global_var_6 - input.var_0.fragPos))))),0.000000) * max(dot(normalize(input.var_0.fragNormal),normalize((normalize(((*global_ubo).global_var_4 - input.var_0.fragPos)) + normalize(((*global_ubo).global_var_6 - input.var_0.fragPos))))),0.000000)) * (((var_7 * var_7) * (var_7 * var_7)) - var_9)) + var_10)) * (((max(dot(normalize(input.var_0.fragNormal),normalize((normalize(((*global_ubo).global_var_4 - input.var_0.fragPos)) + normalize(((*global_ubo).global_var_6 - input.var_0.fragPos))))),0.000000) * max(dot(normalize(input.var_0.fragNormal),normalize((normalize(((*global_ubo).global_var_4 - input.var_0.fragPos)) + normalize(((*global_ubo).global_var_6 - input.var_0.fragPos))))),0.000000)) * (((var_7 * var_7) * (var_7 * var_7)) - var_9)) + var_10));
	float var_13 = max(dot(normalize(input.var_0.fragNormal),normalize(((*global_ubo).global_var_4 - input.var_0.fragPos))),0.000000);
	float var_14 = 1.000000;
	float var_15 = 8.000000;
	float var_16 = var_13;
	float var_17 = 1.000000;
	float var_18 = max(dot(normalize(input.var_0.fragNormal),normalize(((*global_ubo).global_var_6 - input.var_0.fragPos))),0.000000);
	float var_19 = 1.000000;
	float var_20 = 8.000000;
	float var_21 = var_18;
	float var_22 = 1.000000;
	float var_23 = 1.000000;
	float3 var_24 = float3(1.000000, 1.000000, 1.000000);
	float var_25 = 4.000000;
	float var_26 = 0.000100;
	float3 var_27 = (var_4 + ((var_24 - var_4) * pow(clamp((var_23 - clamp(dot(normalize((normalize(((*global_ubo).global_var_4 - input.var_0.fragPos)) + normalize(((*global_ubo).global_var_6 - input.var_0.fragPos)))),normalize(((*global_ubo).global_var_4 - input.var_0.fragPos))),0.000000,1.000000)),0.000000,1.000000),5.000000)));
	float3 var_28 = float3(1.000000, 1.000000, 1.000000);
	float var_29 = 1.000000;
	float var_30 = 3.141593;
	var_5 = (var_5 + ((((((var_28 - var_27) * var_1) / var_30) + ((((var_8 / var_12) * ((var_21 / ((var_18 * (var_22 - (((var_2 + var_19) * (var_2 + var_19)) / var_20))) + (((var_2 + var_19) * (var_2 + var_19)) / var_20))) * (var_16 / ((var_13 * (var_17 - (((var_2 + var_14) * (var_2 + var_14)) / var_15))) + (((var_2 + var_14) * (var_2 + var_14)) / var_15))))) * (var_4 + ((var_24 - var_4) * pow(clamp((var_23 - clamp(dot(normalize((normalize(((*global_ubo).global_var_4 - input.var_0.fragPos)) + normalize(((*global_ubo).global_var_6 - input.var_0.fragPos)))),normalize(((*global_ubo).global_var_4 - input.var_0.fragPos))),0.000000,1.000000)),0.000000,1.000000),5.000000)))) / (((var_25 * max(dot(normalize(input.var_0.fragNormal),normalize(((*global_ubo).global_var_4 - input.var_0.fragPos))),0.000000)) * max(dot(normalize(input.var_0.fragNormal),normalize(((*global_ubo).global_var_6 - input.var_0.fragPos))),0.000000)) + var_26))) * ((*global_ubo).global_var_5 * var_6)) * max(dot(normalize(input.var_0.fragNormal),normalize(((*global_ubo).global_var_6 - input.var_0.fragPos))),0.000000)));
	float3 var_31 = float3(0.030000, 0.030000, 0.030000);
	output.var_32 = float4(((var_31 * var_1) + var_5),1.000000);
	return output;
}
)",{0,"",{{"entryPointParam_main.var_32",{0,0,0,"entryPointParam_main.var_32","float",4,16,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(2)}},{"input.var_0.fragTexCoord",{0,0,2,"input.var_0.fragTexCoord","float",2,8,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(1)}},{"GlobalParams_std140",{0,0,0,"GlobalParams_std140","uniform",2,16,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(3)}},{"global_ubo_struct_std140",{1,2,0,"global_ubo_struct_std140","uniform",8,296,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(3)}},{"input.var_0.fragPos",{0,0,0,"input.var_0.fragPos","float",3,12,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(1)}},{"input.var_0.fragNormal",{0,0,1,"input.var_0.fragNormal","float",3,12,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(1)}},{"input.var_0.fragColor",{0,0,3,"input.var_0.fragColor","float",3,12,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(1)}},}}),},{"DXIL_D__Files_Code_Projects_Helicon_Examples_main_cpp", ShaderCodeModule(std::vector<uint32_t>{1128421444,3215982177,3231643864,3562646887,3718000539,1,5932,8,64,80,236,296,608,2688,2740,2768,810108499,8,100663296,0,826757961,148,4,8,0,136,0,0,3,0,1799,0,0,136,1,0,3,1,1799,0,0,136,2,0,3,2,771,0,0,136,3,0,3,3,1799,0,1094930252,1313818964,0,826757967,52,1,8,0,40,0,64,3,0,15,0,1415534163,1701278305,116,810963792,304,52,0,0,0,0,0,4294967295,0,67109124,1,0,0,0,37,1,24,2,0,0,0,13,0,44,1129270272,1330205761,1330380878,1230258499,1275088463,1413563215,5132105,1094930252,1313818964,1767992576,110,4,0,1,2,3,16,1,0,4390913,515,10,1,4391169,515,19,2,4325889,515,28,3,4391681,515,0,0,272891905,3,7,7,7,0,7,7,7,0,7,7,0,0,1,2,4,0,1413567571,2072,102,518,1279875140,262,16,2048,3737142082,3105,509,2130443,2,19,2435023111,1225050177,959582214,209977746,419956005,1653277726,38082688,1108054594,338825412,1259866168,2288136714,538218568,2777171523,1110579456,2416855268,1355031313,2357285185,2330297313,105263364,6225,8,4292906011,134217727,229114432,4294963332,537133055,4286984301,536870911,11012352,6217,3,1113621011,101207072,0,8329,73,159916594,75850784,2225349395,3810726660,345022852,2358004754,1287947275,146910224,167774528,149291110,9330880,272680489,1368408388,2283831308,2323914850,2680915579,4237330352,2240178192,1194492224,560108560,3869345288,670228904,2669945324,627222747,1840824102,818089028,371319316,2258870402,2276499403,2741927056,2090374538,1091679972,139527184,2584238217,2133727854,4064419522,2304393815,460206025,204522261,1646944580,409044569,3357049352,205572138,51130563,2283300193,205698177,1997549764,335114459,3214020854,1162056210,3460731138,1108558915,2283817032,3804507202,1892710353,284562425,3524444050,570635398,1244168712,3240169649,806369424,1460674700,155472713,1311641491,271133696,3556019201,1942693960,2148124044,2149713189,85622417,1092197670,41947596,0,3228701715,2271245447,2038917174,3228697448,1353649543,248540430,1829654650,813305600,127955463,1829183603,2691763856,119567111,2014220397,544409504,244346119,2047303793,3497133872,120645894,1929879666,2423064352,121665038,1946640506,283510480,127956487,1829183603,544411232,120617479,3859206258,2691958624,121665031,2014240877,1618020256,120617479,1980211314,2655192896,2048,0,2248146944,1050172,1,0,537950476,1024,0,888281088,262208,0,3828350976,402686081,0,1610612736,16856008,48,0,46633152,24578,0,253853696,4195334,0,1124073472,2148011294,0,0,270285958,256,0,1048120320,131104,0,4061659136,1048968,1,0,33124,22,412622386,2420904217,1193675148,574817478,1176019018,212077056,1242866122,2718566563,2688272956,2731148680,2301143056,673349649,69796483,269486930,3464695824,1732378649,723331072,954435706,2151211904,1082130659,27052064,0,6265,160,2420900634,1142096454,3966700687,604786157,1170671046,3332769446,67520101,3322293317,650587174,1130704006,135285776,876642918,2558624795,114167840,3223859393,270036429,2686490754,969939137,185826147,2466939747,4221266699,270571906,1355024079,404275990,1825588064,29360160,1348864038,3637408774,3636643038,3837979838,1623092926,872679462,161620033,273490178,1082288520,571480912,2861141138,1818702380,1818321519,1868723551,68366431,276880034,1414370456,2551737701,2619382603,543955073,909264264,2713144328,4086145072,2952923174,405854209,453382241,819474690,103833612,540312595,423693699,1259038864,4106363763,2504266804,1093985524,1107932712,2349362625,1305559561,2205092368,370887968,1087507715,226547213,3559929478,70651328,1080395459,55587971,2709741624,1882523149,3045133699,228888641,1762035083,3228698272,1478165254,453455978,583231746,2820293025,3249544513,445777616,3792093624,243327501,2496233708,2555713493,3709426140,653828356,1276642568,2204829712,2260856096,881049797,1345684424,202326403,226746421,409739073,2148516078,2216329737,12650177,402984325,1008714140,1279541409,208522286,2257480877,408673049,2164579549,3114555576,1305334221,3331065872,400153180,2164578587,2781636808,3519905181,2366115917,3726204168,1553718167,342230747,86528518,1409628243,1481966920,2853721605,3050942896,2509350073,156094905,2019830402,1919252014,1852795251,161612371,1569431065,2573048600,2831193308,854033987,1447433863,1190450982,624346710,3784362560,3449145529,2378814909,156093845,2019838620,1887007790,1852719461,1952543855,1936617321,208602195,3118567658,3717572056,3511521573,1301664133,245418505,2571869721,509386011,463100884,546626781,3784358420,3585969337,3382038969,1477004749,1,6265,81,478152755,1713168836,2285699348,3280222275,125846156,1929869433,3859575192,283971328,243332110,507644979,3458056642,811998369,1133001989,461603896,3359441868,59522371,2356726845,2064085108,1215891208,124809351,1979936890,544245624,298588551,244378638,1846489313,4041412400,240185358,499388467,3625722334,1640111393,2301650462,998489147,3023651792,2210151427,990086204,1981083852,1752893280,2271753991,923232370,2423293824,123760775,1980180598,2021000696,2273343367,1904674911,2557642520,2174253447,250670636,4111393006,820776640,2714264067,480371740,3827081676,1641815201,471976476,3390931396,2429945441,1137195331,960731193,3090760648,1133787331,990087224,3157246868,2197568643,990106683,3364668336,1887176481,2266001923,2063822963,1618544392,2278060167,2047322231,3829170584,1080954752,248571151,2172858608,3693019592,2716081216,492945948,3827056860,1,8305,51,2534228134,3493739759,1275383348,3274967108,872568898,4176723548,285266433,1840715750,4184922884,17556430,1413747797,307281978,2120228870,2958482289,1022334733,1162875070,61162561,6366476,3072583170,1893534573,199479033,1145831697,1120089096,1824756092,2367697736,1893335905,199479033,1145831697,1120089096,2227409276,2178478084,4089338931,3711140856,383480190,4019653936,14876220,3560757379,1840715748,4184920070,4973518,1602497779,1409922780,2403067331,1145982255,1358222496,3067895699,3854777377,894406459,3321463872,3238009709,215040,0,1313098825,44,2359296,876044899,808793185,845426736,842359605,1680892728,809055032,825778487,926430514,1650749486,0,1213415752,20,0,1352955083,1381814784,2424507788,2267382138,1279875140,3156,102,789,1279875140,262,16,3132,3737142082,3105,780,2130443,2,19,2435023111,1225050177,959582214,209977746,419956005,1653277726,38082688,1108054594,338825412,1259866168,2288136714,538218568,2777171523,1110579456,2416855268,1355031313,2357285185,2330297313,105263364,6225,8,4292906011,134217727,229114432,4294963332,537133055,4286984301,536870911,11012352,6217,3,1113621011,101207072,0,8329,73,159916594,75850784,2225349395,3810726660,345022852,2358004754,1287947275,146911248,167774528,149291110,9330880,272680489,1368408388,2283831308,2323914850,2680915579,4237330352,2240178192,1194492224,560108560,3869345288,670228904,2669945324,627222747,1840824102,818089028,371319316,2258870402,2276499403,2741927056,2090374538,1091679972,139527184,2584238217,2133727854,4064419522,2304393815,460206025,204522261,1646944580,409044569,3357049352,205572138,51130563,2283300193,205698177,1997549764,335114459,3214020854,1162056210,3460731138,1108558915,2283817032,3804507202,1892710353,284562425,3524444050,570635398,1244168712,3240169649,806369424,1460674700,155472713,1311641491,271133696,3556019201,1942693960,2148124044,2149713189,85622417,1092197670,3263173068,20,3228701715,2271245447,2038917174,3228697448,1353649543,248540430,1829654650,813305600,127955463,1829183603,2691763856,119567111,2014220397,544409504,244346119,2047303793,3497133872,120645894,1929879666,2423064352,121665038,1946640506,283510480,127956487,1829183603,544411232,120617479,3859206258,2691958624,121665031,2014240877,1618020256,120617479,1980211314,2655192896,0,0,2248146944,1050172,1,0,537950476,1024,0,888281088,262208,0,3828350976,402686081,0,1610612736,16856008,48,0,46633152,24578,0,253853696,4195334,0,1124073472,2148011294,0,0,270285958,256,0,1048120320,131104,0,4061659136,1048968,1,0,33124,17,345513522,2420904217,1193675148,574817478,1243127882,1084228706,2317131978,682114208,578818441,688030504,269177348,2198867984,2275586514,939757112,238551950,2181302272,6608,6265,96,2420900634,1142096454,3966700687,604786157,1170671046,3332769446,67520101,3322293317,650587174,1130704006,135285776,876642918,2558624795,114167840,3223859297,270036429,270571650,218170575,68354618,679533058,1126736651,2617797635,1006633997,220267712,876678584,301994049,1852399981,2258540612,2660411522,1158162076,2888319285,1093828877,1107930664,2282769793,1212187240,3683484699,1972709552,698407265,404862807,1698901046,1748393821,273536451,272853384,1837374214,1099215067,2422365541,1545099533,3626086499,1700473910,227566941,460682970,3356233480,1285033152,2236710233,3516243401,1820987469,325603458,551191044,1638951788,1254150225,3558534147,1624815936,453431363,57684870,111182432,2168522459,1153764739,118751677,3973634133,3369229530,2800278730,840253700,851121980,934590905,3506514359,3318680708,2932706350,1615490636,1942168020,587940761,2053870379,2606967587,3362070546,3403963632,3840597734,2800143046,840781572,3032160060,2988751794,3123755561,1413556658,2781809799,776900044,3442338319,1248751245,1808,6265,81,478152755,1713168836,2285699348,3280222275,125846156,1929869433,3859575192,283971328,243332110,507644979,3458056642,811998369,1133001989,461603896,3359441868,59522371,2356726845,2064085108,1215891208,124809351,1979936890,544245624,298588551,244378638,1846489313,4041412400,240185358,499388467,3625722334,1640111393,2301650462,998489147,3023651792,2210151427,990086204,1981083852,1752893280,2271753991,923232370,2423293824,123760775,1980180598,2021000696,2273343367,1904674911,2557642520,2174253447,250670636,4111393006,820776640,2714264067,480371740,3827081676,1641815201,471976476,3390931396,2429945441,1137195331,960731193,3090760648,1133787331,990087224,3157246868,2197568643,990106683,3364668336,1887176481,2266001923,2063822963,1618544392,2278060167,2047322231,3829170584,1080954752,248571151,2172858608,3693019592,2716081216,492945948,3827056860,1,8305,51,2534228134,3493739759,1275383348,3274967108,872568898,4176723548,285266433,1840715750,4184922884,17556430,1413747797,307281978,2120228870,2958482289,1022334733,1162875070,61162561,6366476,3072583170,1893534573,199479033,1145831697,1120089096,1824756092,2367697736,1893335905,199479033,1145831697,1120089096,2227409276,2178478084,4089338931,3711140856,383480190,4019653936,14876220,3560757379,1840715748,4184920070,4973518,1602497779,1409922780,2403067331,1145982255,1358222496,3067895699,3854777377,894406459,3321463872,3238009709,215040,8289,338,742589459,16,48,146855108,1076172032,1268033860,1901991049,323045652,3376686228,1766986766,692120852,247549076,1074581908,3646657569,1883648209,1926819299,136316003,2350393474,136347665,18407138,178291208,537158406,938967560,2751184966,415334988,4177489793,73598472,2728353322,2181056055,1669240864,3255312388,4031133683,2063266002,3944875107,1178069655,2062602992,704930687,934453086,545390662,73629448,2996788778,2348862511,136347665,581602,1795715961,1277283584,2961649768,2268096262,2232354384,4090433651,92,525859,102785154,2164670626,2294396959,545259969,4037311512,1099482629,404783106,4191202840,2179213313,9462327,3322284064,276789291,2381344778,134226968,184648066,2189961247,2294382622,545260097,11606040,170950406,587599996,2181040390,1120428128,688029720,2350416332,134226968,187793794,2768928866,811796448,536907874,755369480,2552906124,3247447362,2147631496,3038255136,1890190912,105938698,591395,3630194818,44046658,427983914,2365580,1904312840,177235467,1728544937,9462320,101058592,713137198,2687009448,29460673,1276649600,3422970037,69635114,33654976,873996416,1090977977,2294412319,545259969,3769859096,2587164934,102959168,1619132424,482537680,167813124,460323,3656409218,3590593602,2147598728,3159103520,515966672,3221497484,2147615112,3761510432,692127600,3246965392,404783105,122731132,4032968257,101195776,42217430,403852306,3626860928,3246398722,204489320,543884359,2165093244,203852816,285370560,3256100492,1345356076,503388209,2199192320,805429265,18362704,2822111262,1483504641,3235444739,3249664006,3278103565,113756187,227512376,455016562,910033126,1182532048,67114508,126025921,822286418,271680264,823668867,68157488,1411255555,211857441,423781348,847693768,3246968720,404783105,176224320,646724124,2187902980,203852816,275320194,550640415,1101280830,369903228,12649472,408422371,2182111364,197393,4174393409,721557185,559479042,1099614152,117842750,6324736,2687304849,646723905,2187902980,203852816,276106626,552213279,1104426558,369903228,12649472,408815939,2182111364,197393,1355821121,721558594,559479042,1099614152,4030477886,2407653809,1182535437,67114508,159580353,1619269746,51479056,809566211,490889424,4177668866,3351781720,591282570,2181040902,1154842720,411143226,69255556,460323,3519045762,3053730628,522207584,1044498443,2084638310,4178002028,4043583256,3482345649,2147664264,1029707808,2691370769,2045798662,29460701,1880629376,2165264700,739806255,25298944,3505591286,112225286,411907349,2181562396,4145276673,2642640912,3351518659,3792626128,124840291,1479612913,50597888,1106259084,674439306,823669251,68157496,4163661315,294070305,1090519939,1657331760,812876324,870451316,536899682,1503397384,243287036,460323,2646630530,3926149509,6316592,1510344736,1615117402,1741176449,1073791172,3048475664,46172560,807812678,2441196018,2084781455,1675762156,2065633487,2408611077,209486853,1044510742,2985432086,4178047064,3351797848,2409865810,522265449,1040337419,2985559494,1675896015,3351267841,2409636034,746358545,3043222544,1791476048,3582952097,589235522,827914502,1099745224,956737086,3523944225,4027989568,147618820,1082549224,4194710303,3351355608,910036102,823783520,68157496,3359016963,1666195202,1174413620,878740499,506204257,373179002,522272271,2426374027,544745871,4178447135,4060586712,2408644785,522222641,1492718091,2294792337,607534596,1211177456,50597888,586562756,910389815,75698566,1076904192,1915708364,1129330467,4731160,3288531984,925038140,2184586098,295697,3426758721,594685795,742613047,16,0,},{0,"",{{"entryPointParam_main.var_32",{0,0,0,"entryPointParam_main.var_32","float",4,16,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(2)}},{"input.var_0.fragTexCoord",{0,0,2,"input.var_0.fragTexCoord","float",2,8,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(1)}},{"GlobalParams_std140",{0,0,0,"GlobalParams_std140","uniform",2,16,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(3)}},{"global_ubo_struct_std140",{1,2,0,"global_ubo_struct_std140","uniform",8,296,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(3)}},{"input.var_0.fragPos",{0,0,0,"input.var_0.fragPos","float",3,12,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(1)}},{"input.var_0.fragNormal",{0,0,1,"input.var_0.fragNormal","float",3,12,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(1)}},{"input.var_0.fragColor",{0,0,3,"input.var_0.fragColor","float",3,12,0,static_cast<ShaderCodeModule::ShaderResources::BindType>(1)}},}}),},
};