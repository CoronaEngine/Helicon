#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersSlang = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_64_35",
ShaderCodeModule(R"(struct aggregate_type_0 {
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
	float4x4 global_var_1;
	float4x4 global_var_2;
}
uniform ConstantBuffer<global_ubo_struct>.Handle global_ubo;
struct vertex_input {
	aggregate_type_0 var_0 : LOCATION0;
}
struct vertex_output {
	float4 position_output : SV_POSITION;
}
[shader("vertex")]
vertex_output main(vertex_input input) {
	vertex_output output;
	aggregate_type_1 var_1 = {};
	float4(output.position_output) = float4(mul(mul(mul((*global_ubo).global_var_2,(*global_ubo).global_var_1),(*global_ubo).global_var_0),float4(input.var_0.inPosition,1.000000)));
	return output;
}
 )")
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_65_34",
ShaderCodeModule(R"(struct aggregate_type_0 {
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
	float4x4 global_var_1;
	float4x4 global_var_2;
}
uniform ConstantBuffer<global_ubo_struct>.Handle global_ubo;
[shader("fragment")]
void main() {
}
 )")
},
};