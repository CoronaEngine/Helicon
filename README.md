## 框架设计
- edsl生成slang，slang自带兼容各种奇怪的平台
- slang代码生成spirv，hlsl和glsl通过glslang生成spirv（vulkan），dx的hlsl通过dxc生成spirv，支持跨语言include
- spirv通过spirv-cross生成hlsl、glsl等
- 转译后的hlsl通过dxc编译成dxil
