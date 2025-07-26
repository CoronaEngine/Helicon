#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersSlang = {{"VertexShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_70_35",
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
	float3x3 global_var_1;
	float4x4 global_var_2;
	float4x4 global_var_3;
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
},{"FragmentShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_71_34",
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
	float3x3 global_var_1;
	float4x4 global_var_2;
	float4x4 global_var_3;
}
uniform ConstantBuffer<global_ubo_struct>.Handle global_ubo;
struct fragment_input {
	aggregate_type_1 var_0 : LOCATION0;
}
[shader("fragment")]
void main(fragment_input input) {
}
 )")
},
};