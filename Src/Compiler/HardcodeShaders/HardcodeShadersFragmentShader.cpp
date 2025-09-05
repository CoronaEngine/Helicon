#include"HardcodeShaders.h"
std::unordered_map<std::string, std::variant<EmbeddedShader::ShaderCodeModule::ShaderResources,std::variant<std::vector<uint32_t>,std::string>>> EmbeddedShader::HardcodeShaders::hardcodeShadersFragmentShader = {{"Reflection_C__Users_47226_Documents_Github_Helicon_Examples_main_cpp", ShaderCodeModule::ShaderResources{0,"",{{"global_ubo_struct_std140",{0,0,0,"global_ubo_struct_std140","uniform",7,284,0,static_cast<EmbeddedShader::ShaderCodeModule::ShaderResources::BindType>(3)}},{"global_ubo.global_var_7.texture",{0,1,0,"global_ubo.global_var_7.texture","sampler2D",0,0,0,static_cast<EmbeddedShader::ShaderCodeModule::ShaderResources::BindType>(4)}},{"input.var_0.fragPos",{0,0,0,"input.var_0.fragPos","float",3,12,0,static_cast<EmbeddedShader::ShaderCodeModule::ShaderResources::BindType>(1)}},{"input.var_0.fragNormal",{0,0,1,"input.var_0.fragNormal","float",3,12,0,static_cast<EmbeddedShader::ShaderCodeModule::ShaderResources::BindType>(1)}},{"entryPointParam_main.var_32",{0,0,0,"entryPointParam_main.var_32","float",4,16,0,static_cast<EmbeddedShader::ShaderCodeModule::ShaderResources::BindType>(2)}},{"input.var_0.fragTexCoord",{0,0,2,"input.var_0.fragTexCoord","float",2,8,0,static_cast<EmbeddedShader::ShaderCodeModule::ShaderResources::BindType>(1)}},{"input.var_0.fragColor",{0,0,3,"input.var_0.fragColor","float",3,12,0,static_cast<EmbeddedShader::ShaderCodeModule::ShaderResources::BindType>(1)}},}}},{"SpirV_C__Users_47226_Documents_Github_Helicon_Examples_main_cpp", std::vector<uint32_t>{119734787,66816,2621440,204,0,131089,1,393227,49,1280527431,1685353262,808793134,0,196622,0,1,786447,4,2,1852399981,0,64,31,195,18,20,24,26,196624,2,7,196611,11,1,262149,12,1601331574,49,262149,12,1601331574,49,458757,18,1970302569,1635135092,774922098,1734439526,7565136,524293,20,1970302569,1635135092,774922098,1734439526,1836216142,27745,589829,24,1970302569,1635135092,774922098,1734439526,1131963732,1685221231,0,524293,26,1970302569,1635135092,774922098,1734439526,1869377347,114,655365,31,1651469415,1969187937,1731096418,1633841004,1635147628,775380850,1954047348,6648437,262149,32,1886216563,6579564,262149,42,1886216563,6579564,786437,56,1952533855,1400400242,1634889588,1717527911,1952542572,1597274164,1298952003,1919904353,828666995,12340,327686,56,0,1635017060,0,786437,60,1952533855,1400400242,1634889588,1717527911,1952542572,1597208627,1298952003,1919904353,828666995,12340,327686,60,0,1635017060,0,589829,55,1651469415,1969187937,1935634274,1668641396,1953718132,808726884,0,458758,55,0,1651469415,1985965153,811561569,0,458758,55,1,1651469415,1985965153,828338785,0,458758,55,2,1651469415,1985965153,845116001,0,458758,55,3,1651469415,1985965153,861893217,0,458758,55,4,1651469415,1985965153,878670433,0,458758,55,5,1651469415,1985965153,895447649,0,458758,55,6,1651469415,1985965153,912224865,0,327685,64,1651469415,1969187937,28514,262149,108,1601331574,12849,262149,129,1601331574,14130,589829,195,1920233061,1768902777,1632662638,1601003890,1852399981,1918989870,3289951,262149,2,1852399981,0,262215,18,30,0,262215,20,30,1,262215,24,30,2,262215,26,30,3,262215,31,33,1,262215,31,34,0,262215,57,6,16,327752,56,0,35,0,262215,61,6,16,327752,60,0,35,0,196679,55,2,327752,55,0,35,0,327752,55,1,35,64,327752,55,2,35,112,327752,55,3,35,176,327752,55,4,35,240,327752,55,5,35,256,327752,55,6,35,272,262215,64,33,0,262215,64,34,0,262215,195,30,0,131091,1,196641,3,1,196630,6,32,262167,7,6,4,262167,10,6,3,262176,11,7,10,262176,17,1,10,262167,21,6,2,262176,23,1,21,589849,27,6,1,2,0,0,1,0,196635,28,27,262176,30,0,28,131092,35,262187,6,37,1008981770,262187,6,51,1025758986,393260,10,50,51,51,51,262187,6,53,1056964608,393260,10,52,53,53,53,262165,58,32,1,262187,58,59,4,262172,57,7,59,196638,56,57,262187,58,62,3,262172,61,10,62,196638,60,61,589854,55,56,60,56,56,10,10,10,262176,63,2,55,262176,65,2,10,262187,58,70,6,262187,6,79,0,262187,6,88,3211788288,262187,6,90,1065353216,262187,6,92,1078530012,393260,10,116,90,90,90,262187,6,127,1084227584,262187,6,136,1031798784,262187,6,138,1060634624,262187,6,140,1049624576,262187,6,164,1082130432,262187,6,170,953267991,262187,58,174,5,262187,6,188,1022739087,393260,10,187,188,188,188,262176,194,3,7,262203,17,18,1,262203,17,20,1,262203,23,24,1,262203,17,26,1,262203,30,31,0,262203,63,64,2,262203,194,195,3,262187,6,202,1050868098,393260,10,203,202,202,202,327734,1,2,0,3,131320,4,262203,11,12,7,262205,10,16,18,262205,10,19,20,262205,21,22,24,262205,10,25,26,262205,28,29,31,393303,7,32,29,22,0,327761,6,34,32,3,327866,35,36,34,37,196855,15,0,262394,36,14,13,131320,13,196670,12,25,131321,15,131320,14,262205,28,41,31,393303,7,42,41,22,0,524367,10,44,42,42,0,1,2,196670,12,44,131321,15,131320,15,262205,10,47,12,524300,10,48,49,46,50,47,52,393228,10,54,49,69,19,327746,65,66,64,59,262205,10,67,66,327811,10,68,67,16,393228,10,69,49,69,68,327746,65,71,64,70,262205,10,72,71,327811,10,73,72,16,393228,10,74,49,69,73,327809,10,75,69,74,393228,10,76,49,69,75,327828,6,77,54,76,458764,6,78,49,40,77,79,393228,10,80,49,69,68,393228,10,81,49,69,73,327809,10,82,80,81,393228,10,83,49,69,82,327828,6,84,54,83,458764,6,85,49,40,84,79,327813,6,86,78,85,327813,6,87,86,88,327809,6,89,87,90,327813,6,91,92,89,393228,10,93,49,69,68,393228,10,94,49,69,73,327809,10,95,93,94,393228,10,96,49,69,95,327828,6,97,54,96,458764,6,98,49,40,97,79,393228,10,99,49,69,68,393228,10,100,49,69,73,327809,10,101,99,100,393228,10,102,49,69,101,327828,6,103,54,102,458764,6,104,49,40,103,79,327813,6,105,98,104,327813,6,106,105,88,327809,6,107,106,90,327813,6,108,91,107,393228,10,109,49,69,68,327828,6,110,54,109,458764,6,111,49,40,110,79,393228,10,112,49,69,73,327828,6,113,54,112,458764,6,114,49,40,113,79,327811,10,115,116,48,393228,10,117,49,69,68,393228,10,118,49,69,73,327809,10,119,117,118,393228,10,120,49,69,119,393228,10,121,49,69,68,327828,6,122,120,121,524300,6,123,49,43,122,79,90,327811,6,124,90,123,524300,6,125,49,43,124,79,90,458764,6,126,49,26,125,127,327822,10,128,115,126,327809,10,129,48,128,327811,10,130,116,129,327813,10,132,130,47,327813,10,134,132,203,327816,6,135,136,108,327813,6,137,114,138,327809,6,139,137,140,327816,6,141,114,139,327813,6,142,111,138,327809,6,143,142,140,327816,6,144,111,143,327813,6,145,141,144,327813,6,146,135,145,393228,10,147,49,69,68,393228,10,148,49,69,73,327809,10,149,147,148,393228,10,150,49,69,149,393228,10,151,49,69,68,327828,6,152,150,151,524300,6,153,49,43,152,79,90,327811,6,154,90,153,524300,6,155,49,43,154,79,90,458764,6,156,49,26,155,127,327822,10,157,115,156,327809,10,158,48,157,327822,10,159,158,146,393228,10,160,49,69,68,327828,6,161,54,160,458764,6,162,49,40,161,79,327813,6,163,164,162,393228,10,165,49,69,73,327828,6,166,54,165,458764,6,167,49,40,166,79,327813,6,168,163,167,327809,6,169,168,170,393296,10,171,169,169,169,327816,10,172,159,171,327809,10,173,134,172,327746,65,175,64,174,262205,10,176,175,327813,10,177,173,176,393228,10,178,49,69,73,327828,6,179,54,178,458764,6,180,49,40,179,79,327822,10,181,177,180,327813,10,186,187,47,327809,10,189,186,181,327760,7,190,189,90,196670,195,190,65789,65592,}},{"HLSL_C__Users_47226_Documents_Github_Helicon_Examples_main_cpp", R"()"},{"Slang_C__Users_47226_Documents_Github_Helicon_Examples_main_cpp", R"(struct aggregate_type_0 {
	Sampler2D<float4> texture;
}
struct aggregate_type_1 {
	float3 inPosition;
	float3 inNormal;
	float2 inTexCoord;
	float3 inColor;
}
struct aggregate_type_2 {
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
	aggregate_type_0 global_var_7;
}
ConstantBuffer<global_ubo_struct> global_ubo;
struct fragment_input {
	aggregate_type_2 var_0 : LOCATION0;
}
struct fragment_output {
	float4 var_32 : SV_TARGET0;
}
[shader("fragment")]
fragment_output main(fragment_input input) {
	fragment_output output;
	float3 var_1 = float3(0.000000, 0.000000, 0.000000);
	if ((global_ubo.global_var_7.texture.Sample(input.var_0.fragTexCoord).w > 0.010000)) {
		var_1 = global_ubo.global_var_7.texture.Sample(input.var_0.fragTexCoord).xyz;
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
	float var_12 = ((var_11 * (((max(dot(normalize(input.var_0.fragNormal),normalize((normalize((global_ubo.global_var_4 - input.var_0.fragPos)) + normalize((global_ubo.global_var_6 - input.var_0.fragPos))))),0.000000) * max(dot(normalize(input.var_0.fragNormal),normalize((normalize((global_ubo.global_var_4 - input.var_0.fragPos)) + normalize((global_ubo.global_var_6 - input.var_0.fragPos))))),0.000000)) * (((var_7 * var_7) * (var_7 * var_7)) - var_9)) + var_10)) * (((max(dot(normalize(input.var_0.fragNormal),normalize((normalize((global_ubo.global_var_4 - input.var_0.fragPos)) + normalize((global_ubo.global_var_6 - input.var_0.fragPos))))),0.000000) * max(dot(normalize(input.var_0.fragNormal),normalize((normalize((global_ubo.global_var_4 - input.var_0.fragPos)) + normalize((global_ubo.global_var_6 - input.var_0.fragPos))))),0.000000)) * (((var_7 * var_7) * (var_7 * var_7)) - var_9)) + var_10));
	float var_13 = max(dot(normalize(input.var_0.fragNormal),normalize((global_ubo.global_var_4 - input.var_0.fragPos))),0.000000);
	float var_14 = 1.000000;
	float var_15 = 8.000000;
	float var_16 = var_13;
	float var_17 = 1.000000;
	float var_18 = max(dot(normalize(input.var_0.fragNormal),normalize((global_ubo.global_var_6 - input.var_0.fragPos))),0.000000);
	float var_19 = 1.000000;
	float var_20 = 8.000000;
	float var_21 = var_18;
	float var_22 = 1.000000;
	float var_23 = 1.000000;
	float3 var_24 = float3(1.000000, 1.000000, 1.000000);
	float var_25 = 4.000000;
	float var_26 = 0.000100;
	float3 var_27 = (var_4 + ((var_24 - var_4) * pow(clamp((var_23 - clamp(dot(normalize((normalize((global_ubo.global_var_4 - input.var_0.fragPos)) + normalize((global_ubo.global_var_6 - input.var_0.fragPos)))),normalize((global_ubo.global_var_4 - input.var_0.fragPos))),0.000000,1.000000)),0.000000,1.000000),5.000000)));
	float3 var_28 = float3(1.000000, 1.000000, 1.000000);
	float var_29 = 1.000000;
	float var_30 = 3.141593;
	var_5 = (var_5 + ((((((var_28 - var_27) * var_1) / var_30) + ((((var_8 / var_12) * ((var_21 / ((var_18 * (var_22 - (((var_2 + var_19) * (var_2 + var_19)) / var_20))) + (((var_2 + var_19) * (var_2 + var_19)) / var_20))) * (var_16 / ((var_13 * (var_17 - (((var_2 + var_14) * (var_2 + var_14)) / var_15))) + (((var_2 + var_14) * (var_2 + var_14)) / var_15))))) * (var_4 + ((var_24 - var_4) * pow(clamp((var_23 - clamp(dot(normalize((normalize((global_ubo.global_var_4 - input.var_0.fragPos)) + normalize((global_ubo.global_var_6 - input.var_0.fragPos)))),normalize((global_ubo.global_var_4 - input.var_0.fragPos))),0.000000,1.000000)),0.000000,1.000000),5.000000)))) / (((var_25 * max(dot(normalize(input.var_0.fragNormal),normalize((global_ubo.global_var_4 - input.var_0.fragPos))),0.000000)) * max(dot(normalize(input.var_0.fragNormal),normalize((global_ubo.global_var_6 - input.var_0.fragPos))),0.000000)) + var_26))) * (global_ubo.global_var_5 * var_6)) * max(dot(normalize(input.var_0.fragNormal),normalize((global_ubo.global_var_6 - input.var_0.fragPos))),0.000000)));
	float3 var_31 = float3(0.030000, 0.030000, 0.030000);
	output.var_32 = float4(((var_31 * var_1) + var_5),1.000000);
	return output;
}
)"},
};