#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersSlang = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_153_35",
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
	aggregate_type_1 var_2 : LOCATION0;
}
[shader("vertex")]
vertex_output main(vertex_input input) {
	vertex_output output;
	aggregate_type_1 var_1 = {};
	output.position_output = mul(mul(mul((*global_ubo).global_var_3,(*global_ubo).global_var_2),(*global_ubo).global_var_0),float4(input.var_0.inPosition,1.000000));
	var_1.fragPos = mul((*global_ubo).global_var_0,float4(input.var_0.inPosition,1.000000)).xyz;
	var_1.fragNormal = normalize(mul((*global_ubo).global_var_1,input.var_0.inNormal));
	var_1.fragColor = input.var_0.inColor;
	var_1.fragTexCoord = input.var_0.inTexCoord;
	output.var_2 = var_1;
	return output;
}
 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_154_34",
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
	float4 var_54 : SV_TARGET0;
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
	float3 var_4 = var_1;
	float3 var_5 = input.var_0.fragNormal;
	float3 var_6 = input.var_0.fragPos;
	float3 var_7 = float3(0.040000, 0.040000, 0.040000);
	var_7 = lerp(var_7,var_4,var_3);
	float3 var_8 = float3(0.000000, 0.000000, 0.000000);
	float var_9 = 1.000000;
	float var_10 = var_2;
	float3 var_11 = normalize((normalize(((*global_ubo).global_var_4 - var_6)) + normalize(((*global_ubo).global_var_6 - var_6))));
	float3 var_12 = normalize(var_5);
	float var_13 = 0.000000;
	float var_14 = ((var_10 * var_10) * (var_10 * var_10));
	float var_15 = 1.000000;
	float var_16 = 1.000000;
	float var_17 = 3.141593;
	float var_18 = var_2;
	float3 var_19 = normalize(((*global_ubo).global_var_6 - var_6));
	float3 var_20 = normalize(((*global_ubo).global_var_4 - var_6));
	float3 var_21 = normalize(var_5);
	float var_22 = 0.000000;
	float var_23 = 0.000000;
	float var_24 = var_18;
	float var_25 = max(dot(var_21,var_20),var_22);
	float var_26 = 1.000000;
	float var_27 = 8.000000;
	float var_28 = var_25;
	float var_29 = 1.000000;
	float var_30 = var_18;
	float var_31 = max(dot(var_21,var_19),var_23);
	float var_32 = 1.000000;
	float var_33 = 8.000000;
	float var_34 = var_31;
	float var_35 = 1.000000;
	float3 var_36 = var_7;
	float var_37 = 1.000000;
	float var_38 = 0.000000;
	float var_39 = 5.000000;
	float var_40 = 1.000000;
	float var_41 = 0.000000;
	float var_42 = 1.000000;
	float3 var_43 = float3(1.000000, 1.000000, 1.000000);
	float var_44 = 0.000000;
	float var_45 = 4.000000;
	float var_46 = 0.000000;
	float var_47 = 0.000100;
	float3 var_48 = (var_36 + ((var_43 - var_36) * pow(clamp((var_42 - clamp(dot(normalize((normalize(((*global_ubo).global_var_4 - var_6)) + normalize(((*global_ubo).global_var_6 - var_6)))),normalize(((*global_ubo).global_var_4 - var_6))),var_38,var_37)),var_41,var_40),var_39)));
	float3 var_49 = float3(1.000000, 1.000000, 1.000000);
	float var_50 = 1.000000;
	float var_51 = 0.000000;
	float var_52 = 3.141593;
	var_8 = (var_8 + ((((((var_49 - var_48) * var_4) / var_52) + ((((var_14 / ((var_17 * (((max(dot(var_12,var_11),var_13) * max(dot(var_12,var_11),var_13)) * (((var_10 * var_10) * (var_10 * var_10)) - var_15)) + var_16)) * (((max(dot(var_12,var_11),var_13) * max(dot(var_12,var_11),var_13)) * (((var_10 * var_10) * (var_10 * var_10)) - var_15)) + var_16))) * ((var_34 / ((var_31 * (var_35 - (((var_30 + var_32) * (var_30 + var_32)) / var_33))) + (((var_30 + var_32) * (var_30 + var_32)) / var_33))) * (var_28 / ((var_25 * (var_29 - (((var_24 + var_26) * (var_24 + var_26)) / var_27))) + (((var_24 + var_26) * (var_24 + var_26)) / var_27))))) * (var_36 + ((var_43 - var_36) * pow(clamp((var_42 - clamp(dot(normalize((normalize(((*global_ubo).global_var_4 - var_6)) + normalize(((*global_ubo).global_var_6 - var_6)))),normalize(((*global_ubo).global_var_4 - var_6))),var_38,var_37)),var_41,var_40),var_39)))) / (((var_45 * max(dot(normalize(var_5),normalize(((*global_ubo).global_var_4 - var_6))),var_44)) * max(dot(normalize(var_5),normalize(((*global_ubo).global_var_6 - var_6))),var_46)) + var_47))) * ((*global_ubo).global_var_5 * var_9)) * max(dot(normalize(var_5),normalize(((*global_ubo).global_var_6 - var_6))),var_51)));
	float3 var_53 = float3(0.030000, 0.030000, 0.030000);
	output.var_54 = float4(((var_53 * var_4) + var_8),1.000000);
	return output;
}
 )")
},
};