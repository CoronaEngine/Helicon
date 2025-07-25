#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersSlang = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_188_35",
ShaderCodeModule(R"(Texture2D<float4> global_var_1;
RWStructuredBuffer<float4> global_var_2;
struct aggregate_type_0 {
	int member1;
	float4 member2;
	RWStructuredBuffer<float4> member3;
	RWTexture2D<float4> member4;
}
struct aggregate_type_1 {
	float4 pos;
	float4 color;
}
struct global_ubo_struct {
	aggregate_type_0 global_var_3;
}
ConstantBuffer<global_ubo_struct> global_ubo;
struct vertex_input {
	aggregate_type_1 var_0 : LOCATION0;
}
struct vertex_output {
	float4 position_output : SV_POSITION;
	float4 var_5 : LOCATION0;
}
[shader("vertex")]
vertex_output main(vertex_input input) {
	vertex_output output;
	float4 var_1 = float4(1.000000, 2.000000, 3.000000, 4.000000);
	global_ubo.global_var_3.member4[uint2(0, 0)] = var_1;
	float var_2 = 1.000000;
	float var_3 = 1.000000;
	(--var_2);
	var_1.xy = float2(0.000000, 0.000000);
	if (true) {
	}
	else if (false) {
	}
	else {
	}
	global_var_2[0] = global_var_1[uint2(0, 0)];
	output.position_output = global_var_1[int2(0, 0)];
	float4 var_4 = input.var_0.color;
	output.var_5 = var_4;
	return output;
}
 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_189_34",
ShaderCodeModule(R"(Texture2D<float4> global_var_1;
RWStructuredBuffer<float4> global_var_2;
struct aggregate_type_0 {
	int member1;
	float4 member2;
	RWStructuredBuffer<float4> member3;
	RWTexture2D<float4> member4;
}
struct aggregate_type_1 {
	float4 pos;
	float4 color;
}
struct global_ubo_struct {
	aggregate_type_0 global_var_3;
}
ConstantBuffer<global_ubo_struct> global_ubo;
struct fragment_input {
	float4 var_0 : LOCATION0;
}
struct fragment_output {
	float4 var_7 : SV_TARGET0;
}
[shader("fragment")]
fragment_output main(fragment_input input) {
	fragment_output output;
	float var_1 = 1.000000;
	float var_2 = 1.000000;
	var_1 = pow(var_1,var_2);
	var_1 = clamp(var_1,var_1,var_2);
	float4 var_3 = float4(0.000000, 0.000000, 0.000000, 0.000000);
	float4 var_4 = float4(0.000000, 0.000000, 0.000000, 0.000000);
	var_4 = normalize(var_3);
	float var_5 = 0.300000;
	var_1 = lerp(var_1,var_2,var_5);
	float4x4 var_6 = float4x4(float4(0.000000, 0.000000, 0.000000, 0.000000),float4(0.000000, 0.000000, 0.000000, 0.000000),float4(0.000000, 0.000000, 0.000000, 0.000000),float4(0.000000, 0.000000, 0.000000, 0.000000));
	var_6 = transpose(var_6);
	output.var_7 = input.var_0;
	return output;
}
 )")
},
};