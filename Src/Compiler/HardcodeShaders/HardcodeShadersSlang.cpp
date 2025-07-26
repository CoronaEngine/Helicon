#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersSlang = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_146_35",
ShaderCodeModule(R"(uniform Texture2D<float4>.Handle global_var_1;
struct aggregate_type_0 {
	float4 pos;
	float2 texCoord;
}
struct global_ubo_struct {
	SamplerState.Handle global_var_2;
}
uniform ConstantBuffer<global_ubo_struct>.Handle global_ubo;
struct vertex_input {
	aggregate_type_0 var_0 : LOCATION0;
}
struct vertex_output {
	float4 position_output : SV_POSITION;
	float4 var_1 : LOCATION0;
}
[shader("vertex")]
vertex_output main(vertex_input input) {
	vertex_output output;
	output.position_output = input.var_0.pos;
	output.var_1 = global_var_1.Sample((*global_ubo).global_var_2,input.var_0.texCoord);
	return output;
}
 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_147_34",
ShaderCodeModule(R"(uniform Texture2D<float4>.Handle global_var_1;
struct aggregate_type_0 {
	float4 pos;
	float2 texCoord;
}
struct global_ubo_struct {
	SamplerState.Handle global_var_2;
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