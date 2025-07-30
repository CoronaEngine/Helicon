## 框架设计
- 支持Embedded DSL（native C++，CUDA-like）编写Shader：
  - Embedded DSL生成Slang（Slang自带兼容各种奇怪的平台）
- 支持Slang、HLSL、GLSL、SPIRV语言的Shader输入，支持HLSL、GLSL、SPIRV三者转译
  - slang代码生成spirv，hlsl和glsl通过glslang生成spirv（vulkan），dx的hlsl通过dxc生成spirv，支持跨语言include
  - spirv通过spirv-cross生成hlsl、glsl等
  - 转译后的hlsl通过dxc编译成dxil
- 支持JIT（运行时编译）、支持Shader硬编码至c艹
