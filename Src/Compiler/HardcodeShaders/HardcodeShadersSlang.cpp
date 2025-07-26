#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersSlang = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_159_35",
ShaderCodeModule(R"(struct aggregate_type_0 {
	RWStructuredBuffer<float4> member;
}
RWStructuredBuffer<float4> global_var_4;
RWStructuredBuffer<RWTexture2D<float4>> global_var_5;
struct aggregate_type_1 {
	float4 pos;
	float4 color;
}
struct global_ubo_struct {
	float4 global_var_1;
	uint global_var_2;
	aggregate_type_0 global_var_3;
}
ConstantBuffer<global_ubo_struct> global_ubo;
struct vertex_input {
	aggregate_type_1 var_0 : LOCATION0;
}
struct vertex_output {
	float4 position_output : SV_POSITION;
	float4 var_2 : LOCATION0;
}
[shader("vertex")]
vertex_output main(vertex_input input) {
	vertex_output output;
	global_var_5[global_ubo.global_var_2][uint2(0, 0)] = global_ubo.global_var_1;
	global_ubo.global_var_3.member[global_ubo.global_var_2] = global_ubo.global_var_1;
	global_var_4[global_ubo.global_var_2] = global_ubo.global_var_1;
	input.var_0.pos.x = global_ubo.global_var_1.x;
	output.position_output = input.var_0.pos;
	float4 var_1 = input.var_0.color;
	output.var_2 = var_1;
	return output;
}
 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_160_34",
ShaderCodeModule(R"(struct aggregate_type_0 {
	RWStructuredBuffer<float4> member;
}
RWStructuredBuffer<float4> global_var_4;
RWStructuredBuffer<RWTexture2D<float4>> global_var_5;
struct aggregate_type_1 {
	float4 pos;
	float4 color;
}
struct global_ubo_struct {
	float4 global_var_1;
	uint global_var_2;
	aggregate_type_0 global_var_3;
}
ConstantBuffer<global_ubo_struct> global_ubo;
struct fragment_input {
	float4 var_0 : LOCATION0;
}
struct fragment_output {
	float4 var_1 : SV_TARGET0;
}
[shader("fragment")]
fragment_output main(fragment_input input) {
	fragment_output output;
	output.var_1 = input.var_0;
	return output;
}
 )")
},
};