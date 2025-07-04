#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersGLSL = {{"VertexShader_C__Github_Helicon_Examples_main_cpp_87_21",
ShaderCodeModule(R"(#version 460

layout(location = 0) in vec3 var_0;

void main()
{
    gl_Position = vec4(var_0, 1.0);
    gl_Position.x = 114.0;
}

 )")
},{"FragmentShader_C__Github_Helicon_Examples_main_cpp_88_21",
ShaderCodeModule(R"( )")
},
};