#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersSlang = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_96_32",
ShaderCodeModule(R"(struct vertex_input {
	float3 var_0 : LOCATION0;
	float4 var_1 : LOCATION1;
}
struct vertex_output {
	float4 var_2 : LOCATION0;
	float4 position_output : SV_POSITION;
}
[shader("vertex")]
vertex_output main(vertex_input input) {
	vertex_output output;
	output.position_output = float4(input.var_0,1.000000);
	output.var_2 = input.var_1;
	return output;
}
 )")
},
};