#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersSlang = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_100_32",
ShaderCodeModule(R"(


struct global_ubo_struct {
	float4 global_var_0;
	float4 global_var_1;
	float4 global_var_2;
}
ConstantBuffer<global_ubo_struct> shader_ubo;
struct vertex_input {
	float3 var_0 : LOCATION0;
}
struct vertex_output {
	float4 var_1 : LOCATION0;
	float4 position_output : SV_POSITION;
}
[shader("vertex")]
vertex_output main(vertex_input input) {
	vertex_output output;
	output.position_output = float4(input.var_0,1.000000);
	output.var_1 = shader_ubo.global_var_0;
	output.var_1 = shader_ubo.global_var_1;
	return output;
}
 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_101_31",
ShaderCodeModule(R"(


struct global_ubo_struct {
	float4 global_var_0;
	float4 global_var_1;
	float4 global_var_2;
}
ConstantBuffer<global_ubo_struct> shader_ubo;
struct fragment_input {
	float4 var_0 : LOCATION0;
}
struct fragment_output {
	float4 var_1 : SV_TARGET0;
}
[shader("fragment")]
fragment_output main(fragment_input input) {
	fragment_output output;
	output.var_1 = shader_ubo.global_var_0;
	output.var_1 = shader_ubo.global_var_2;
	return output;
}
 )")
},
};