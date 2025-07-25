#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersHLSL = {{"ComputeShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_197_32",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 22815 "hlsl.meta.slang"
struct GlobalParams_0
{
    uint2 output_0;
    uint2 buffer_0;
};


#line 22815
cbuffer globalParams_0 : register(b0)
{
    GlobalParams_0 globalParams_0;
}

#line 4 "f9e5e22c2a0c5539f7aa2872b27ec3b69d9728db"
[numthreads(1, 1, 1)]
void main()
{

#line 5
    RWStructuredBuffer<float4 > _S1 = RWStructuredBuffer<float4 >(ResourceDescriptorHeap[globalParams_0.output_0.x]);

#line 5
    _S1[int(0)] = ConstantBuffer<float4 >(ResourceDescriptorHeap[globalParams_0.buffer_0.x]);
    return;
}

 )")
},
};