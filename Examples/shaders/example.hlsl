// Example HLSL shader for testing the Helicon auto-compile system
// This file will be compiled to SPIR-V and embedded as C++ code

struct VertexInput
{
    float3 position;
    float2 texCoord;
};

struct VertexOutput
{
    float4 position;
    float2 texCoord;
};

// Simple utility function - will be exposed as FunctionProxy in C++
float3 transformPosition(float3 pos, float3 offset)
{
    return pos + offset;
}

// Another utility function for testing
int3 addVectors(int a, int b, int c)
{
    return int3(a + 1, b + 2, c + 3);
}

// Compute a simple lighting value
float computeLighting(float3 normal, float3 lightDir)
{
    float3 n = normalize(normal);
    float3 l = normalize(lightDir);
    return max(dot(n, l), 0.0);
}
