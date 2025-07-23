#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersSlang = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_155_35",
ShaderCodeModule(R"(Texture2D<float4> global_var_1;
RWStructuredBuffer<float4> global_var_2;
struct aggregate_type_0 {
	float4 pos;
	float4 color;
}
struct vertex_input {
	aggregate_type_0 var_0 : LOCATION0;
}
struct vertex_output {
	float4 position_output : SV_POSITION;
	float4 var_5 : LOCATION0;
}
[shader("vertex")]
vertex_output main(vertex_input input) {
	vertex_output output;
	float4x4 var_1 = float4x4(float4(1.000000, 2.000000, 3.000000, 4.000000),float4(5.000000, 6.000000, 7.000000, 8.000000),float4(9.000000, 10.000000, 11.000000, 12.000000),float4(13.000000, 14.000000, 15.000000, 16.000000));
	float4x4 var_2 = float4x4(float4(1.000000, 2.000000, 3.000000, 4.000000),float4(5.000000, 6.000000, 7.000000, 8.000000),float4(9.000000, 10.000000, 11.000000, 12.000000),float4(13.000000, 14.000000, 15.000000, 16.000000));
	var_1 = var_2;
	float4 var_3 = float4(1.000000, 2.000000, 3.000000, 4.000000);
	var_3.x = 1.000000;
	global_var_2[0] = global_var_1[int2(0, 0)];
	output.position_output = global_var_1[int2(0, 0)];
	float4 var_4 = input.var_0.color;
	output.var_5 = var_4;
	return output;
}
 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_156_34",
ShaderCodeModule(R"(Texture2D<float4> global_var_1;
RWStructuredBuffer<float4> global_var_2;
struct aggregate_type_0 {
	float4 pos;
	float4 color;
}
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