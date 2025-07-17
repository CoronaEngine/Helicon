#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersSlang = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_96_32",
ShaderCodeModule(R"(
Buffer<float> global_var_1;
struct global_ubo_struct {
	float4 global_var_0;
}
ConstantBuffer<global_ubo_struct> global_ubo;
struct vertex_input {
	float3 var_0 : LOCATION0;
}
struct vertex_output {
	float4 position_output : SV_POSITION;
}
[shader("vertex")]
vertex_output main(vertex_input input) {
	vertex_output output;
	output.position_output = float4(input.var_0,1.000000);
	return output;
}
 )")
},
};