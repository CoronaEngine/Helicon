#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersSlang = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_163_35",
ShaderCodeModule(R"(uniform RWStructuredBuffer<float4>.Handle global_var_3;
struct aggregate_type_0 {
	float4 pos;
	float4 color;
}
struct global_ubo_struct {
	float4 global_var_1;
	uint global_var_2;
}
uniform ConstantBuffer<global_ubo_struct>.Handle global_ubo;
struct vertex_input {
	aggregate_type_0 var_0 : LOCATION0;
}
struct vertex_output {
	float4 position_output : SV_POSITION;
	float4 var_3 : LOCATION0;
}
[shader("vertex")]
vertex_output main(vertex_input input) {
	vertex_output output;
	uint var_1 = (*global_ubo).global_var_2;
	global_var_3[var_1] = (*global_ubo).global_var_1;
	input.var_0.pos.x = (*global_ubo).global_var_1.x;
	output.position_output = input.var_0.pos;
	float4 var_2 = input.var_0.color;
	output.var_3 = var_2;
	return output;
}
 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_164_34",
ShaderCodeModule(R"(uniform RWStructuredBuffer<float4>.Handle global_var_3;
struct aggregate_type_0 {
	float4 pos;
	float4 color;
}
struct global_ubo_struct {
	float4 global_var_1;
	uint global_var_2;
}
uniform ConstantBuffer<global_ubo_struct>.Handle global_ubo;
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