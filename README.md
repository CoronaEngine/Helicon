## 功能介绍
- 支持Embedded DSL（native C艹，CUDA-like）编写Shader：
  - Embedded DSL生成Slang（Slang自带兼容各种奇怪的平台）
- 支持Slang、HLSL、GLSL、SPIRV语言的Shader输入，支持HLSL、GLSL、SPIRV三者转译
  - Slang代码生成SPIRV
  - HLSL、GLSL通过glslang生成SPIRV
  - SPIRV通过spirv-cross生成HLSL、GLSL等
  - （开发中）SPIRV转译后的HLSL，通过DXC编译成DXIL、DXBC
  - （开发中）支持跨语言include
- 支持JIT（运行时编译）、支持Shader硬编码至c艹
