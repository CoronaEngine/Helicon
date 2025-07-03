#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersHLSL = {{"VertexShader__SourceCode_CabbageGlobalContext_h_192_63",
ShaderCodeModule(R"(ByteAddressBuffer bonesMatrix[] : register(t2, space0);
struct UniformBufferObject_1
{
    row_major float4x4 viewProjMatrix;
};

ConstantBuffer<UniformBufferObject_1> uniformBufferObjects[] : register(b0, space0);
cbuffer PushConsts
{
    uint pushConsts_textureIndex : packoffset(c0);
    uint pushConsts_boneIndex : packoffset(c0.y);
    uint pushConsts_uniformBufferIndex : packoffset(c0.z);
    row_major float4x4 pushConsts_modelMatrix : packoffset(c1);
};


static float4 gl_Position;
static float4 jointWeights;
static uint4 boneIndexes;
static float3 inPosition;
static float3 fragPos;
static float2 fragTexCoord;
static float2 inTexCoord;
static float3 fragNormal;
static float3 inNormal;
static float2 fragMotionVector;

struct SPIRV_Cross_Input
{
    float3 inPosition : TEXCOORD0;
    float3 inNormal : TEXCOORD1;
    float2 inTexCoord : TEXCOORD2;
    uint4 boneIndexes : TEXCOORD3;
    float4 jointWeights : TEXCOORD4;
};

struct SPIRV_Cross_Output
{
    float3 fragPos : TEXCOORD0;
    float3 fragNormal : TEXCOORD1;
    float2 fragTexCoord : TEXCOORD2;
    float2 fragMotionVector : TEXCOORD3;
    float4 gl_Position : SV_Position;
};

void vert_main()
{
    float4 totalPosition = 0.0f.xxxx;
    if (dot(jointWeights, 1.0f.xxxx) > 0.001000000047497451305389404296875f)
    {
        for (int i = 0; i < 4; i++)
        {
            float4x4 _59 = float4x4(bonesMatrix[pushConsts_boneIndex].Load<float4>(boneIndexes[i] * 64 + 0), bonesMatrix[pushConsts_boneIndex].Load<float4>(boneIndexes[i] * 64 + 16), bonesMatrix[pushConsts_boneIndex].Load<float4>(boneIndexes[i] * 64 + 32), bonesMatrix[pushConsts_boneIndex].Load<float4>(boneIndexes[i] * 64 + 48));
            float4 localPosition = mul(float4(inPosition, 1.0f), _59);
            totalPosition += (localPosition * jointWeights[i]);
        }
    }
    else
    {
        totalPosition = float4(inPosition, 1.0f);
    }
    float4 worldPos = mul(totalPosition, pushConsts_modelMatrix);
    fragPos = worldPos.xyz;
    gl_Position = mul(worldPos, uniformBufferObjects[pushConsts_uniformBufferIndex].viewProjMatrix);
    fragTexCoord = inTexCoord;
    fragNormal = inNormal;
    fragMotionVector = 0.0f.xx;
}

SPIRV_Cross_Output main(SPIRV_Cross_Input stage_input)
{
    jointWeights = stage_input.jointWeights;
    boneIndexes = stage_input.boneIndexes;
    inPosition = stage_input.inPosition;
    inTexCoord = stage_input.inTexCoord;
    inNormal = stage_input.inNormal;
    vert_main();
    SPIRV_Cross_Output stage_output;
    stage_output.gl_Position = gl_Position;
    stage_output.fragPos = fragPos;
    stage_output.fragTexCoord = fragTexCoord;
    stage_output.fragNormal = fragNormal;
    stage_output.fragMotionVector = fragMotionVector;
    return stage_output;
}
 )")
},{"FragmentShader__SourceCode_CabbageGlobalContext_h_192_63",
ShaderCodeModule(R"(struct UniformBufferObject_1
{
    row_major float4x4 viewProjMatrix;
};

ConstantBuffer<UniformBufferObject_1> uniformBufferObjects[1] : register(b0, space0);
cbuffer PushConsts
{
    uint pushConsts_textureIndex : packoffset(c0);
    uint pushConsts_boneIndex : packoffset(c0.y);
    uint pushConsts_uniformBufferIndex : packoffset(c0.z);
    row_major float4x4 pushConsts_modelMatrix : packoffset(c1);
};

Texture2D<float4> textures[] : register(t1, space0);
SamplerState _textures_sampler[] : register(s1, space0);

static float4 gbufferBaseColor;
static float2 fragTexCoord;
static float3 gbufferNormal;
static float3 fragNormal;
static float3 gbufferPostion;
static float3 fragPos;
static float2 gbufferMotionVector;
static float2 fragMotionVector;

struct SPIRV_Cross_Input
{
    float3 fragPos : TEXCOORD0;
    float3 fragNormal : TEXCOORD1;
    float2 fragTexCoord : TEXCOORD2;
    float2 fragMotionVector : TEXCOORD3;
};

struct SPIRV_Cross_Output
{
    float3 gbufferPostion : SV_Target0;
    float3 gbufferNormal : SV_Target1;
    float4 gbufferBaseColor : SV_Target2;
    float2 gbufferMotionVector : SV_Target3;
};

void frag_main()
{
    gbufferBaseColor = float4(float3(textures[pushConsts_textureIndex].Sample(_textures_sampler[pushConsts_textureIndex], fragTexCoord).xyz), 1.0f);
    gbufferNormal = fragNormal;
    gbufferPostion = fragPos;
    gbufferMotionVector = fragMotionVector;
}

SPIRV_Cross_Output main(SPIRV_Cross_Input stage_input)
{
    fragTexCoord = stage_input.fragTexCoord;
    fragNormal = stage_input.fragNormal;
    fragPos = stage_input.fragPos;
    fragMotionVector = stage_input.fragMotionVector;
    frag_main();
    SPIRV_Cross_Output stage_output;
    stage_output.gbufferBaseColor = gbufferBaseColor;
    stage_output.gbufferNormal = gbufferNormal;
    stage_output.gbufferPostion = gbufferPostion;
    stage_output.gbufferMotionVector = gbufferMotionVector;
    return stage_output;
}
 )")
},{"VertexShader__SourceCode_CabbageGlobalContext_h_199_61",
ShaderCodeModule(R"(ByteAddressBuffer bonesMatrix[] : register(t2, space0);
struct UniformBufferObject_1
{
    row_major float4x4 viewProjMatrix;
};

ConstantBuffer<UniformBufferObject_1> uniformBufferObjects[] : register(b0, space0);
cbuffer PushConsts
{
    uint pushConsts_textureIndex : packoffset(c0);
    uint pushConsts_boneIndex : packoffset(c0.y);
    uint pushConsts_uniformBufferIndex : packoffset(c0.z);
    row_major float4x4 pushConsts_modelMatrix : packoffset(c1);
};


static float4 gl_Position;
static float4 jointWeights;
static uint4 boneIndexes;
static float3 inPosition;
static float3 fragPos;
static float2 fragTexCoord;
static float2 inTexCoord;
static float3 fragNormal;
static float3 inNormal;
static float2 fragMotionVector;

struct SPIRV_Cross_Input
{
    float3 inPosition : TEXCOORD0;
    float3 inNormal : TEXCOORD1;
    float2 inTexCoord : TEXCOORD2;
    uint4 boneIndexes : TEXCOORD3;
    float4 jointWeights : TEXCOORD4;
};

struct SPIRV_Cross_Output
{
    float3 fragPos : TEXCOORD0;
    float3 fragNormal : TEXCOORD1;
    float2 fragTexCoord : TEXCOORD2;
    float2 fragMotionVector : TEXCOORD3;
    float4 gl_Position : SV_Position;
};

void vert_main()
{
    float4 totalPosition = 0.0f.xxxx;
    if (dot(jointWeights, 1.0f.xxxx) > 0.001000000047497451305389404296875f)
    {
        for (int i = 0; i < 4; i++)
        {
            float4x4 _59 = float4x4(bonesMatrix[pushConsts_boneIndex].Load<float4>(boneIndexes[i] * 64 + 0), bonesMatrix[pushConsts_boneIndex].Load<float4>(boneIndexes[i] * 64 + 16), bonesMatrix[pushConsts_boneIndex].Load<float4>(boneIndexes[i] * 64 + 32), bonesMatrix[pushConsts_boneIndex].Load<float4>(boneIndexes[i] * 64 + 48));
            float4 localPosition = mul(float4(inPosition, 1.0f), _59);
            totalPosition += (localPosition * jointWeights[i]);
        }
    }
    else
    {
        totalPosition = float4(inPosition, 1.0f);
    }
    float4 worldPos = mul(totalPosition, pushConsts_modelMatrix);
    fragPos = worldPos.xyz;
    gl_Position = mul(worldPos, uniformBufferObjects[pushConsts_uniformBufferIndex].viewProjMatrix);
    fragTexCoord = inTexCoord;
    fragNormal = inNormal;
    fragMotionVector = 0.0f.xx;
}

SPIRV_Cross_Output main(SPIRV_Cross_Input stage_input)
{
    jointWeights = stage_input.jointWeights;
    boneIndexes = stage_input.boneIndexes;
    inPosition = stage_input.inPosition;
    inTexCoord = stage_input.inTexCoord;
    inNormal = stage_input.inNormal;
    vert_main();
    SPIRV_Cross_Output stage_output;
    stage_output.gl_Position = gl_Position;
    stage_output.fragPos = fragPos;
    stage_output.fragTexCoord = fragTexCoord;
    stage_output.fragNormal = fragNormal;
    stage_output.fragMotionVector = fragMotionVector;
    return stage_output;
}
 )")
},{"FragmentShader__SourceCode_CabbageGlobalContext_h_199_61",
ShaderCodeModule(R"(struct UniformBufferObject_1
{
    row_major float4x4 viewProjMatrix;
};

ConstantBuffer<UniformBufferObject_1> uniformBufferObjects[1] : register(b0, space0);
cbuffer PushConsts
{
    uint pushConsts_textureIndex : packoffset(c0);
    uint pushConsts_boneIndex : packoffset(c0.y);
    uint pushConsts_uniformBufferIndex : packoffset(c0.z);
    row_major float4x4 pushConsts_modelMatrix : packoffset(c1);
};

Texture2D<float4> textures[] : register(t1, space0);
SamplerState _textures_sampler[] : register(s1, space0);

static float4 gbufferBaseColor;
static float2 fragTexCoord;
static float3 gbufferNormal;
static float3 fragNormal;
static float3 gbufferPostion;
static float3 fragPos;
static float2 gbufferMotionVector;
static float2 fragMotionVector;

struct SPIRV_Cross_Input
{
    float3 fragPos : TEXCOORD0;
    float3 fragNormal : TEXCOORD1;
    float2 fragTexCoord : TEXCOORD2;
    float2 fragMotionVector : TEXCOORD3;
};

struct SPIRV_Cross_Output
{
    float3 gbufferPostion : SV_Target0;
    float3 gbufferNormal : SV_Target1;
    float4 gbufferBaseColor : SV_Target2;
    float2 gbufferMotionVector : SV_Target3;
};

void frag_main()
{
    gbufferBaseColor = float4(float3(textures[pushConsts_textureIndex].Sample(_textures_sampler[pushConsts_textureIndex], fragTexCoord).xyz), 1.0f);
    gbufferNormal = fragNormal;
    gbufferPostion = fragPos;
    gbufferMotionVector = fragMotionVector;
}

SPIRV_Cross_Output main(SPIRV_Cross_Input stage_input)
{
    fragTexCoord = stage_input.fragTexCoord;
    fragNormal = stage_input.fragNormal;
    fragPos = stage_input.fragPos;
    fragMotionVector = stage_input.fragMotionVector;
    frag_main();
    SPIRV_Cross_Output stage_output;
    stage_output.gbufferBaseColor = gbufferBaseColor;
    stage_output.gbufferNormal = gbufferNormal;
    stage_output.gbufferPostion = gbufferPostion;
    stage_output.gbufferMotionVector = gbufferMotionVector;
    return stage_output;
}
 )")
},{"ComputeShader__SourceCode_CabbageGlobalContext_h_208_53",
ShaderCodeModule(R"(struct UniformBufferObject_1_1
{
    float3 lightPostion;
    row_major float4x4 lightViewMatrix;
    row_major float4x4 lightProjMatrix;
    float3 eyePosition;
    float3 eyeDir;
    row_major float4x4 eyeViewMatrix;
    row_major float4x4 eyeProjMatrix;
};

ConstantBuffer<UniformBufferObject_1_1> uniformBufferObjects[] : register(b0, space0);
cbuffer PushConsts
{
    uint2 pushConsts_gbufferSize : packoffset(c0);
    uint pushConsts_gbufferPostionImage : packoffset(c0.z);
    uint pushConsts_gbufferBaseColorImage : packoffset(c0.w);
    uint pushConsts_gbufferNormalImage : packoffset(c1);
    uint pushConsts_gbufferDepthImage : packoffset(c1.y);
    uint2 pushConsts_shadowMapSize : packoffset(c1.z);
    uint pushConsts_shadowMapDepthImage : packoffset(c2);
    float3 pushConsts_lightColor : packoffset(c3);
    float3 pushConsts_sun_dir : packoffset(c4);
    float pushConsts_camera_near : packoffset(c4.w);
    float pushConsts_camera_far : packoffset(c5);
    uint pushConsts_finalOutputImage : packoffset(c5.y);
    uint pushConsts_uniformBufferIndex : packoffset(c5.z);
    uint pushConsts_mutiviewImageIndex : packoffset(c5.w);
    uint pushConsts_time : packoffset(c6);
};

Texture2D<float4> textures[] : register(t1, space0);
SamplerState _textures_sampler[] : register(s1, space0);
RWTexture2D<unorm float4> inputImageRGBA16[] : register(u3, space0);
RWTexture2D<uint> inputImageRGBA8[1] : register(u3, space0);
RWTexture2DArray<unorm float4> inputImage2DArray[1] : register(u3, space0);

static uint3 gl_GlobalInvocationID;
struct SPIRV_Cross_Input
{
    uint3 gl_GlobalInvocationID : SV_DispatchThreadID;
};

float DistributionGGX(float3 N, float3 H, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0f);
    float NdotH2 = NdotH * NdotH;
    float nom = a2;
    float denom = (NdotH2 * (a2 - 1.0f)) + 1.0f;
    denom = (3.1415927410125732421875f * denom) * denom;
    return nom / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = roughness + 1.0f;
    float k = (r * r) / 8.0f;
    float nom = NdotV;
    float denom = (NdotV * (1.0f - k)) + k;
    return nom / denom;
}

float GeometrySmith(float3 N, float3 V, float3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0f);
    float NdotL = max(dot(N, L), 0.0f);
    float param = NdotV;
    float param_1 = roughness;
    float ggx2 = GeometrySchlickGGX(param, param_1);
    float param_2 = NdotL;
    float param_3 = roughness;
    float ggx1 = GeometrySchlickGGX(param_2, param_3);
    return ggx1 * ggx2;
}

float3 fresnelSchlick(float cosTheta, float3 F0)
{
    return F0 + ((1.0f.xxx - F0) * pow(clamp(1.0f - cosTheta, 0.0f, 1.0f), 5.0f));
}

float3 calculateColor(float3 WorldPos, float3 Normal, float3 lightPos, float3 lightColor, float3 albedo, float metallic, float roughness)
{
    float3 N = normalize(Normal);
    float3 V = normalize(uniformBufferObjects[pushConsts_uniformBufferIndex].eyePosition - WorldPos);
    float3 F0 = 0.039999999105930328369140625f.xxx;
    F0 = lerp(F0, albedo, metallic.xxx);
    float3 Lo = 0.0f.xxx;
    float3 L = normalize(pushConsts_sun_dir);
    float3 H = normalize(V + L);
    float attenuation = 1.0f;
    float3 radiance = lightColor * attenuation;
    float3 param = N;
    float3 param_1 = H;
    float param_2 = roughness;
    float NDF = DistributionGGX(param, param_1, param_2);
    float3 param_3 = N;
    float3 param_4 = V;
    float3 param_5 = L;
    float param_6 = roughness;
    float G = GeometrySmith(param_3, param_4, param_5, param_6);
    float param_7 = clamp(dot(H, V), 0.0f, 1.0f);
    float3 param_8 = F0;
    float3 F = fresnelSchlick(param_7, param_8);
    float3 numerator = F * (NDF * G);
    float denominator = ((4.0f * max(dot(N, V), 0.0f)) * max(dot(N, L), 0.0f)) + 9.9999997473787516355514526367188e-05f;
    float3 specular = numerator / denominator.xxx;
    float3 kS = F;
    float3 kD = 1.0f.xxx - kS;
    kD *= (1.0f - metallic);
    float NdotL = max(dot(N, L), 0.0f);
    Lo += (((((kD * albedo) / 3.1415927410125732421875f.xxx) + specular) * radiance) * NdotL);
    float3 ambient = 0.02999999932944774627685546875f.xxx * albedo;
    return ambient + Lo;
}

bool intersectWithEarth(float3 rayOrigin, float3 rayDir, inout float t0, inout float t1)
{
    float3 rc = -rayOrigin;
    float radius2 = 41873842372608.0f;
    float tca = dot(rc, rayDir);
    float d2 = dot(rc, rc) - (tca * tca);
    if (d2 > radius2)
    {
        return false;
    }
    float thc = sqrt(radius2 - d2);
    t0 = tca - thc;
    t1 = tca + thc;
    return true;
}

float rayleighPhase(float mu)
{
    return (3.0f * (1.0f + (mu * mu))) / 50.26548004150390625f;
}

float HenyeyGreensteinPhase(float mu)
{
    return 0.422399997711181640625f / (7.141592502593994140625f * pow(1.577600002288818359375f - (1.519999980926513671875f * mu), 1.5f));
}

float approx_air_column_density_ratio_through_atmosphere(float a, float b, float z2, float r0)
{
    float x0 = sqrt(max((r0 * r0) - z2, 9.9999996826552253889678874634872e-21f));
    bool _395 = a < x0;
    bool _402;
    if (_395)
    {
        _402 = (-x0) < b;
    }
    else
    {
        _402 = _395;
    }
    bool _410;
    if (_402)
    {
        _410 = z2 < (r0 * r0);
    }
    else
    {
        _410 = _402;
    }
    if (_410)
    {
        return 100000002004087734272.0f;
    }
    float abs_a = abs(a);
    float abs_b = abs(b);
    float z = sqrt(z2);
    float sqrt_z = sqrt(z);
    float ra = sqrt((a * a) + z2);
    float rb = sqrt((b * b) + z2);
    float ch0 = (((1.0f - (1.0f / (2.0f * r0))) * 1.25331413745880126953125f) * sqrt_z) + (0.60000002384185791015625f * x0);
    float cha = (((1.0f - (1.0f / (2.0f * ra))) * 1.25331413745880126953125f) * sqrt_z) + (0.60000002384185791015625f * abs_a);
    float chb = (((1.0f - (1.0f / (2.0f * rb))) * 1.25331413745880126953125f) * sqrt_z) + (0.60000002384185791015625f * abs_b);
    float s0 = min(exp(r0 - z), 1.0f) / ((x0 / r0) + (1.0f / ch0));
    float sa = exp(r0 - ra) / max((abs_a / ra) + (1.0f / cha), 0.00999999977648258209228515625f);
    float sb = exp(r0 - rb) / max((abs_b / rb) + (1.0f / chb), 0.00999999977648258209228515625f);
    return max((sign(b) * (s0 - sb)) - (sign(a) * (s0 - sa)), 0.0f);
}

float approx_air_column_density_ratio_along_3d_ray_for_curved_world(float3 P, float3 V, float x, float r, float H)
{
    float xz = dot(-P, V);
    float z2 = dot(P, P) - (xz * xz);
    float param = 0.0f - xz;
    float param_1 = x - xz;
    float param_2 = z2;
    float param_3 = r / H;
    return approx_air_column_density_ratio_through_atmosphere(param, param_1, param_2, param_3);
}

float3 getAtmosphericSky(float3 rayOrigin, float3 rayDir, float3 sun_dir, float sun_power)
{
    int samplesCount = 16;
    float3 betaR = float3(5.5000000429572537541389465332031e-06f, 1.2999999853491317480802536010742e-05f, 2.2399999579647555947303771972656e-05f);
    float3 betaM = 2.0999999833293259143829345703125e-05f.xxx;
    float3 param = rayOrigin;
    float3 param_1 = rayDir;
    float t0;
    float param_2 = t0;
    float t1;
    float param_3 = t1;
    bool _583 = intersectWithEarth(param, param_1, param_2, param_3);
    t0 = param_2;
    t1 = param_3;
    if (!_583)
    {
        return 0.0f.xxx;
    }
    float march_step = t1 / float(samplesCount);
    float mu = dot(rayDir, sun_dir);
    float param_4 = mu;
    float phaseR = rayleighPhase(param_4);
    float param_5 = mu;
    float phaseM = HenyeyGreensteinPhase(param_5);
    float optical_depthR = 0.0f;
    float optical_depthM = 0.0f;
    float3 sumR = 0.0f.xxx;
    float3 sumM = 0.0f.xxx;
    float march_pos = 0.0f;
    float t0_1;
    float t1_1;
    for (int i = 0; i < samplesCount; i++)
    {
        float3 s = rayOrigin + (rayDir * (march_pos + (0.5f * march_step)));
        float height = length(s) - 6371000.0f;
        float hr = exp((-height) / 7994.0f) * march_step;
        float hm = exp((-height) / 1200.0f) * march_step;
        optical_depthR += hr;
        optical_depthM += hm;
        float3 param_6 = s;
        float3 param_7 = sun_dir;
        float param_8 = t0_1;
        float param_9 = t1_1;
        bool _669 = intersectWithEarth(param_6, param_7, param_8, param_9);
        t0_1 = param_8;
        t1_1 = param_9;
        float3 param_10 = s;
        float3 param_11 = sun_dir;
        float param_12 = t1_1;
        float param_13 = 6371000.0f;
        float param_14 = 7994.0f;
        float optical_depth_lightR = approx_air_column_density_ratio_along_3d_ray_for_curved_world(param_10, param_11, param_12, param_13, param_14);
        float3 param_15 = s;
        float3 param_16 = sun_dir;
        float param_17 = t1_1;
        float param_18 = 6371000.0f;
        float param_19 = 1200.0f;
        float optical_depth_lightM = approx_air_column_density_ratio_along_3d_ray_for_curved_world(param_15, param_16, param_17, param_18, param_19);
        float3 tau = (betaR * (optical_depthR + optical_depth_lightR)) + ((betaM * 1.10000002384185791015625f) * (optical_depthM + optical_depth_lightM));
        float3 attenuation = exp(-tau);
        sumR += (attenuation * hr);
        sumM += (attenuation * hm);
        march_pos += march_step;
    }
    return (((sumR * phaseR) * betaR) + ((sumM * phaseM) * betaM)) * sun_power;
}

void comp_main()
{
    float2 screenUV = float2(float(gl_GlobalInvocationID.x) / float(pushConsts_gbufferSize.x), float(gl_GlobalInvocationID.y) / float(pushConsts_gbufferSize.y));
    float gbufferDepth = textures[pushConsts_gbufferDepthImage].SampleLevel(_textures_sampler[pushConsts_gbufferDepthImage], screenUV, 0.0f).x;
    float3 renderResult = 0.0f.xxx;
    if (gbufferDepth < 0.999000012874603271484375f)
    {
        float4 gbufferPostion = inputImageRGBA16[pushConsts_gbufferPostionImage][int2(gl_GlobalInvocationID.xy)];
        float4 gbufferBaseColor = inputImageRGBA16[pushConsts_gbufferBaseColorImage][int2(gl_GlobalInvocationID.xy)];
        float4 gbufferNormal = inputImageRGBA16[pushConsts_gbufferNormalImage][int2(gl_GlobalInvocationID.xy)];
        float3 param = gbufferPostion.xyz;
        float3 param_1 = gbufferNormal.xyz;
        float3 param_2 = uniformBufferObjects[pushConsts_uniformBufferIndex].lightPostion;
        float3 param_3 = pushConsts_lightColor;
        float3 param_4 = gbufferBaseColor.xyz;
        float param_5 = 0.5f;
        float param_6 = 0.5f;
        renderResult = calculateColor(param, param_1, param_2, param_3, param_4, param_5, param_6);
    }
    else
    {
        float2 aspect_ratio = float2(float(pushConsts_gbufferSize.x) / float(pushConsts_gbufferSize.y), 1.0f);
        float fov = 1.0f;
        float2 point_ndc = float2(float(gl_GlobalInvocationID.x) / float(pushConsts_gbufferSize.x), float(gl_GlobalInvocationID.y) / float(pushConsts_gbufferSize.y));
        float3 cam_local_point = float3((((2.0f * point_ndc.x) - 1.0f) * aspect_ratio.x) * fov, ((1.0f - (2.0f * point_ndc.y)) * aspect_ratio.y) * fov, -1.0f);
        float3 cam_origin = float3(0.0f, 6371001.0f, 0.0f) + uniformBufferObjects[pushConsts_uniformBufferIndex].eyePosition;
        float3 cam_look_at = float3(0.0f, 6371001.0f, 0.0f) + uniformBufferObjects[pushConsts_uniformBufferIndex].eyeDir;
        float3 fwd = normalize(cam_look_at - cam_origin);
        float3 up = float3(0.0f, 1.0f, 0.0f);
        float3 right = cross(up, fwd);
        up = cross(fwd, right);
        float3 rayOrigin = cam_origin;
        float3 rayDir = normalize((fwd + (up * cam_local_point.y)) + (right * cam_local_point.x));
        float3 param_7 = rayOrigin;
        float3 param_8 = rayDir;
        float3 param_9 = pushConsts_sun_dir;
        float param_10 = 20.0f;
        renderResult = getAtmosphericSky(param_7, param_8, param_9, param_10);
    }
    inputImageRGBA16[pushConsts_finalOutputImage][int2(gl_GlobalInvocationID.xy)] = float4(renderResult, 1.0f);
}

[numthreads(8, 8, 1)]
void main(SPIRV_Cross_Input stage_input)
{
    gl_GlobalInvocationID = stage_input.gl_GlobalInvocationID;
    comp_main();
}
 )")
},{"ComputeShader__SourceCode_CabbageGlobalContext_h_211_56",
ShaderCodeModule(R"(cbuffer PushConsts
{
    float3 pushConsts_lightColor : packoffset(c0);
    uint pushConsts_finalOutputImage : packoffset(c0.w);
};

RWTexture2D<unorm float4> inputImageRGBA16[] : register(u3, space0);
Texture2D<float4> textures[1] : register(t1, space0);
SamplerState _textures_sampler[1] : register(s1, space0);
RWTexture2D<uint> inputImageRGBA8[1] : register(u3, space0);
RWTexture2DArray<unorm float4> inputImage2DArray[1] : register(u3, space0);

static uint3 gl_GlobalInvocationID;
struct SPIRV_Cross_Input
{
    uint3 gl_GlobalInvocationID : SV_DispatchThreadID;
};

void comp_main()
{
    inputImageRGBA16[pushConsts_finalOutputImage][int2(gl_GlobalInvocationID.xy)] = float4(pushConsts_lightColor, 1.0f);
}

[numthreads(8, 8, 1)]
void main(SPIRV_Cross_Input stage_input)
{
    gl_GlobalInvocationID = stage_input.gl_GlobalInvocationID;
    comp_main();
}
 )")
},
};