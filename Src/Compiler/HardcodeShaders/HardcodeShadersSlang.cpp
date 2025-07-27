#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersSlang = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_155_32",
ShaderCodeModule(R"(uniform Texture2D<float4>.Handle global_var_7;
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
	SamplerState.Handle global_var_8;
}
uniform ConstantBuffer<global_ubo_struct>.Handle global_ubo;
struct vertex_input {
	aggregate_type_0 var_0 : LOCATION0;
}
struct vertex_output {
	float4 position_output : SV_POSITION;
	aggregate_type_1 var_6 : LOCATION0;
}
[shader("vertex")]
vertex_output main(vertex_input input) {
	vertex_output output;
	aggregate_type_1 var_1 = {};
	output.position_output = mul(mul(mul((*global_ubo).global_var_3,(*global_ubo).global_var_2),(*global_ubo).global_var_0),float4(input.var_0.inPosition,1.000000));
	float3 var_2 = mul((*global_ubo).global_var_0,float4(input.var_0.inPosition,1.000000)).xyz;
	float3 var_3 = normalize(mul((*global_ubo).global_var_1,input.var_0.inNormal));
	float3 var_4 = input.var_0.inColor;
	float2 var_5 = input.var_0.inTexCoord;
	output.var_6 = var_1;
	return output;
}
 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_156_34",
ShaderCodeModule(R"(uniform Texture2D<float4>.Handle global_var_7;
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
	SamplerState.Handle global_var_8;
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
	if ((global_var_7.Sample((*global_ubo).global_var_8,input.var_0.fragTexCoord).w > 0.010000)) {
		var_1 = global_var_7.Sample((*global_ubo).global_var_8,input.var_0.fragTexCoord).xyz;
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
 )")
},
};