#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersHLSL = {{"ComputeShader_D__Files_Code_Projects_Helicon_Examples_main_cpp_203_32",
ShaderCodeModule(R"(#pragma pack_matrix(column_major)
#ifdef SLANG_HLSL_ENABLE_NVAPI
#include "nvHLSLExtns.h"
#endif

#ifndef __DXC_VERSION_MAJOR
// warning X3557: loop doesn't seem to do anything, forcing loop to unroll
#pragma warning(disable : 3557)
#endif


#line 6 "16729ac4897656f693f330b53315a505dd4765c0"
cbuffer input_0 : register(b1)
{
    float4 input_0;
}

#line 22815 "hlsl.meta.slang"
struct GlobalParams_0
{
    uint2 textures_0;
    uint2 output_0;
};


#line 22815
cbuffer globalParams_0 : register(b0)
{
    GlobalParams_0 globalParams_0;
}

#line 9 "16729ac4897656f693f330b53315a505dd4765c0"
[numthreads(1, 1, 1)]
void main()
{

#line 11
    RWStructuredBuffer<float4 > _S1 = RWStructuredBuffer<float4 >(ResourceDescriptorHeap[globalParams_0.output_0.x]);

#line 11
    Texture2D<float4 > _S2 = Texture2D<float4 >(ResourceDescriptorHeap[globalParams_0.textures_0.x]);

#line 11
    _S1[int(0)] = _S2.Load((int3)int(0));
    RWStructuredBuffer<float4 > _S3 = RWStructuredBuffer<float4 >(ResourceDescriptorHeap[globalParams_0.output_0.x]);

#line 12
    _S3[int(1)] = input_0;
    return;
}

 )")
},
};