## 功能介绍
- 支持Embedded DSL（native C艹，CUDA-like）编写Shader：
  - Embedded DSL生成Slang（Slang自带兼容各种奇怪的平台）
- 支持Slang、HLSL、GLSL、SPIRV语言的Shader输入，支持HLSL、GLSL、SPIRV三者转译
  - Slang代码生成SPIRV
  - HLSL、GLSL通过glslang生成SPIRV
  - SPIRV通过spirv-cross生成HLSL、GLSL等
  - （开发中）SPIRV转译后的HLSL，通过DXC编译成DXIL、DXBC
  - （开发中）支持跨语言include
- 支持运行时编译JIT、支持Shader反射
  - 支持spirv-cross的JIT和反射
  - （开发中）支持Slang的JIT和反射
  - （开发中）支持glslang的JIT和反射
  - （开发中）支持DXC的JIT和反射
- 支持Shader硬编码至c艹
  - 支持Slang、HLSL、GLSL、SPIRV、DXIL、DXBC硬编码
  - （开发中）支持Shader反射信息硬编码

## TODO LIST
- SPIRV转译后的HLSL，通过DXC编译成DXIL、DXBC，支持DXIL、DXBC的Shader硬编码
- 支持Slang、glslang、DXC的JIT和反射
- 支持Shader反射信息硬编码
- 支持跨语言include
- EDSL：for和if中调用函数
