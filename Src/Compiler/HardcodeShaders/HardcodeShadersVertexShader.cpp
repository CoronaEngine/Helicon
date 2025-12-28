#include"HardcodeShaders.h"
std::unordered_map<std::string, std::variant<EmbeddedShader::ShaderCodeModule::ShaderResources,std::variant<std::vector<uint32_t>,std::string>>> EmbeddedShader::HardcodeShaders::hardcodeShadersVertexShader = {{"SpirV_D__Files_Code_Projects_Helicon_Scripts_main_cpp_line_22_column_29", std::vector<uint32_t>{119734787,67072,524299,6,0,131089,1,393227,1,1280527431,1685353262,808793134,0,196622,0,1,327695,0,4,1852399981,0,196611,5,500,262149,4,1852399981,0,131091,2,196641,3,2,327734,2,4,0,3,131320,5,65789,65592,}},{"SpirV_Reflection_D__Files_Code_Projects_Helicon_Scripts_main_cpp_line_22_column_29", ShaderCodeModule::ShaderResources{0,"",{}}},{"HLSL_D__Files_Code_Projects_Helicon_Scripts_main_cpp_line_22_column_29", R"(
	int3 merge(int a, int b,int c)
	{
		return int3(a,b,c);
	}
)"},{"HLSL_Reflection_D__Files_Code_Projects_Helicon_Scripts_main_cpp_line_22_column_29", ShaderCodeModule::ShaderResources{0,"",{}}},
};