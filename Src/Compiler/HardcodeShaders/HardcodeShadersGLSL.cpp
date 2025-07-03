#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShadersGLSL = {{"VertexShader__SourceCode_CabbageGlobalContext_h_192_63",
ShaderCodeModule(R"(#version 460
#extension GL_EXT_nonuniform_qualifier : require

layout(set = 0, binding = 2, std430) readonly buffer MeshBonesMatrix
{
    mat4 matrix[];
} bonesMatrix[];

layout(set = 0, binding = 0, std140) uniform UniformBufferObject
{
    mat4 viewProjMatrix;
} uniformBufferObjects[];

layout(push_constant, std430) uniform PushConsts
{
    uint textureIndex;
    uint boneIndex;
    uint uniformBufferIndex;
    mat4 modelMatrix;
} pushConsts;

layout(location = 4) in vec4 jointWeights;
layout(location = 3) in uvec4 boneIndexes;
layout(location = 0) in vec3 inPosition;
layout(location = 0) out vec3 fragPos;
layout(location = 2) out vec2 fragTexCoord;
layout(location = 2) in vec2 inTexCoord;
layout(location = 1) out vec3 fragNormal;
layout(location = 1) in vec3 inNormal;
layout(location = 3) out vec2 fragMotionVector;

void main()
{
    vec4 totalPosition = vec4(0.0);
    if (dot(jointWeights, vec4(1.0)) > 0.001000000047497451305389404296875)
    {
        for (int i = 0; i < 4; i++)
        {
            vec4 localPosition = bonesMatrix[pushConsts.boneIndex].matrix[boneIndexes[i]] * vec4(inPosition, 1.0);
            totalPosition += (localPosition * jointWeights[i]);
        }
    }
    else
    {
        totalPosition = vec4(inPosition, 1.0);
    }
    vec4 worldPos = pushConsts.modelMatrix * totalPosition;
    fragPos = worldPos.xyz;
    gl_Position = uniformBufferObjects[pushConsts.uniformBufferIndex].viewProjMatrix * worldPos;
    fragTexCoord = inTexCoord;
    fragNormal = inNormal;
    fragMotionVector = vec2(0.0);
}

 )")
},{"FragmentShader__SourceCode_CabbageGlobalContext_h_192_63",
ShaderCodeModule(R"(#version 460
#extension GL_EXT_nonuniform_qualifier : require

layout(set = 0, binding = 0, std140) uniform UniformBufferObject
{
    mat4 viewProjMatrix;
} uniformBufferObjects[1];

layout(push_constant, std430) uniform PushConsts
{
    uint textureIndex;
    uint boneIndex;
    uint uniformBufferIndex;
    mat4 modelMatrix;
} pushConsts;

layout(set = 0, binding = 1) uniform sampler2D textures[];

layout(location = 2) out vec4 gbufferBaseColor;
layout(location = 2) in vec2 fragTexCoord;
layout(location = 1) out vec3 gbufferNormal;
layout(location = 1) in vec3 fragNormal;
layout(location = 0) out vec3 gbufferPostion;
layout(location = 0) in vec3 fragPos;
layout(location = 3) out vec2 gbufferMotionVector;
layout(location = 3) in vec2 fragMotionVector;

void main()
{
    gbufferBaseColor = vec4(vec3(texture(textures[pushConsts.textureIndex], fragTexCoord).xyz), 1.0);
    gbufferNormal = fragNormal;
    gbufferPostion = fragPos;
    gbufferMotionVector = fragMotionVector;
}

 )")
},{"VertexShader__SourceCode_CabbageGlobalContext_h_199_61",
ShaderCodeModule(R"(#version 460
#extension GL_EXT_nonuniform_qualifier : require

layout(set = 0, binding = 2, std430) readonly buffer MeshBonesMatrix
{
    mat4 matrix[];
} bonesMatrix[];

layout(set = 0, binding = 0, std140) uniform UniformBufferObject
{
    mat4 viewProjMatrix;
} uniformBufferObjects[];

layout(push_constant, std430) uniform PushConsts
{
    uint textureIndex;
    uint boneIndex;
    uint uniformBufferIndex;
    mat4 modelMatrix;
} pushConsts;

layout(location = 4) in vec4 jointWeights;
layout(location = 3) in uvec4 boneIndexes;
layout(location = 0) in vec3 inPosition;
layout(location = 0) out vec3 fragPos;
layout(location = 2) out vec2 fragTexCoord;
layout(location = 2) in vec2 inTexCoord;
layout(location = 1) out vec3 fragNormal;
layout(location = 1) in vec3 inNormal;
layout(location = 3) out vec2 fragMotionVector;

void main()
{
    vec4 totalPosition = vec4(0.0);
    if (dot(jointWeights, vec4(1.0)) > 0.001000000047497451305389404296875)
    {
        for (int i = 0; i < 4; i++)
        {
            vec4 localPosition = bonesMatrix[pushConsts.boneIndex].matrix[boneIndexes[i]] * vec4(inPosition, 1.0);
            totalPosition += (localPosition * jointWeights[i]);
        }
    }
    else
    {
        totalPosition = vec4(inPosition, 1.0);
    }
    vec4 worldPos = pushConsts.modelMatrix * totalPosition;
    fragPos = worldPos.xyz;
    gl_Position = uniformBufferObjects[pushConsts.uniformBufferIndex].viewProjMatrix * worldPos;
    fragTexCoord = inTexCoord;
    fragNormal = inNormal;
    fragMotionVector = vec2(0.0);
}

 )")
},{"FragmentShader__SourceCode_CabbageGlobalContext_h_199_61",
ShaderCodeModule(R"(#version 460
#extension GL_EXT_nonuniform_qualifier : require

layout(set = 0, binding = 0, std140) uniform UniformBufferObject
{
    mat4 viewProjMatrix;
} uniformBufferObjects[1];

layout(push_constant, std430) uniform PushConsts
{
    uint textureIndex;
    uint boneIndex;
    uint uniformBufferIndex;
    mat4 modelMatrix;
} pushConsts;

layout(set = 0, binding = 1) uniform sampler2D textures[];

layout(location = 2) out vec4 gbufferBaseColor;
layout(location = 2) in vec2 fragTexCoord;
layout(location = 1) out vec3 gbufferNormal;
layout(location = 1) in vec3 fragNormal;
layout(location = 0) out vec3 gbufferPostion;
layout(location = 0) in vec3 fragPos;
layout(location = 3) out vec2 gbufferMotionVector;
layout(location = 3) in vec2 fragMotionVector;

void main()
{
    gbufferBaseColor = vec4(vec3(texture(textures[pushConsts.textureIndex], fragTexCoord).xyz), 1.0);
    gbufferNormal = fragNormal;
    gbufferPostion = fragPos;
    gbufferMotionVector = fragMotionVector;
}

 )")
},{"ComputeShader__SourceCode_CabbageGlobalContext_h_208_53",
ShaderCodeModule(R"(#version 460
#extension GL_EXT_nonuniform_qualifier : require
layout(local_size_x = 8, local_size_y = 8, local_size_z = 1) in;

layout(set = 0, binding = 0, std140) uniform UniformBufferObject
{
    vec3 lightPostion;
    mat4 lightViewMatrix;
    mat4 lightProjMatrix;
    vec3 eyePosition;
    vec3 eyeDir;
    mat4 eyeViewMatrix;
    mat4 eyeProjMatrix;
} uniformBufferObjects[];

layout(push_constant, std430) uniform PushConsts
{
    uvec2 gbufferSize;
    uint gbufferPostionImage;
    uint gbufferBaseColorImage;
    uint gbufferNormalImage;
    uint gbufferDepthImage;
    uvec2 shadowMapSize;
    uint shadowMapDepthImage;
    vec3 lightColor;
    vec3 sun_dir;
    float camera_near;
    float camera_far;
    uint finalOutputImage;
    uint uniformBufferIndex;
    uint mutiviewImageIndex;
    uint time;
} pushConsts;

layout(set = 0, binding = 1) uniform sampler2D textures[];
layout(set = 0, binding = 3, rgba16) uniform image2D inputImageRGBA16[];
layout(set = 0, binding = 3, r32ui) uniform readonly writeonly uimage2D inputImageRGBA8[1];
layout(set = 0, binding = 3, rgba16) uniform readonly image2DArray inputImage2DArray[1];

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;
    float nom = a2;
    float denom = (NdotH2 * (a2 - 1.0)) + 1.0;
    denom = (3.1415927410125732421875 * denom) * denom;
    return nom / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = roughness + 1.0;
    float k = (r * r) / 8.0;
    float nom = NdotV;
    float denom = (NdotV * (1.0 - k)) + k;
    return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float param = NdotV;
    float param_1 = roughness;
    float ggx2 = GeometrySchlickGGX(param, param_1);
    float param_2 = NdotL;
    float param_3 = roughness;
    float ggx1 = GeometrySchlickGGX(param_2, param_3);
    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + ((vec3(1.0) - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0));
}

vec3 calculateColor(vec3 WorldPos, vec3 Normal, vec3 lightPos, vec3 lightColor, vec3 albedo, float metallic, float roughness)
{
    vec3 N = normalize(Normal);
    vec3 V = normalize(uniformBufferObjects[pushConsts.uniformBufferIndex].eyePosition - WorldPos);
    vec3 F0 = vec3(0.039999999105930328369140625);
    F0 = mix(F0, albedo, vec3(metallic));
    vec3 Lo = vec3(0.0);
    vec3 L = normalize(pushConsts.sun_dir);
    vec3 H = normalize(V + L);
    float attenuation = 1.0;
    vec3 radiance = lightColor * attenuation;
    vec3 param = N;
    vec3 param_1 = H;
    float param_2 = roughness;
    float NDF = DistributionGGX(param, param_1, param_2);
    vec3 param_3 = N;
    vec3 param_4 = V;
    vec3 param_5 = L;
    float param_6 = roughness;
    float G = GeometrySmith(param_3, param_4, param_5, param_6);
    float param_7 = clamp(dot(H, V), 0.0, 1.0);
    vec3 param_8 = F0;
    vec3 F = fresnelSchlick(param_7, param_8);
    vec3 numerator = F * (NDF * G);
    float denominator = ((4.0 * max(dot(N, V), 0.0)) * max(dot(N, L), 0.0)) + 9.9999997473787516355514526367188e-05;
    vec3 specular = numerator / vec3(denominator);
    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= (1.0 - metallic);
    float NdotL = max(dot(N, L), 0.0);
    Lo += (((((kD * albedo) / vec3(3.1415927410125732421875)) + specular) * radiance) * NdotL);
    vec3 ambient = vec3(0.02999999932944774627685546875) * albedo;
    return ambient + Lo;
}

bool intersectWithEarth(vec3 rayOrigin, vec3 rayDir, inout float t0, inout float t1)
{
    vec3 rc = -rayOrigin;
    float radius2 = 41873842372608.0;
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
    return (3.0 * (1.0 + (mu * mu))) / 50.26548004150390625;
}

float HenyeyGreensteinPhase(float mu)
{
    return 0.422399997711181640625 / (7.141592502593994140625 * pow(1.577600002288818359375 - (1.519999980926513671875 * mu), 1.5));
}

float approx_air_column_density_ratio_through_atmosphere(float a, float b, float z2, float r0)
{
    float x0 = sqrt(max((r0 * r0) - z2, 9.9999996826552253889678874634872e-21));
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
        return 100000002004087734272.0;
    }
    float abs_a = abs(a);
    float abs_b = abs(b);
    float z = sqrt(z2);
    float sqrt_z = sqrt(z);
    float ra = sqrt((a * a) + z2);
    float rb = sqrt((b * b) + z2);
    float ch0 = (((1.0 - (1.0 / (2.0 * r0))) * 1.25331413745880126953125) * sqrt_z) + (0.60000002384185791015625 * x0);
    float cha = (((1.0 - (1.0 / (2.0 * ra))) * 1.25331413745880126953125) * sqrt_z) + (0.60000002384185791015625 * abs_a);
    float chb = (((1.0 - (1.0 / (2.0 * rb))) * 1.25331413745880126953125) * sqrt_z) + (0.60000002384185791015625 * abs_b);
    float s0 = min(exp(r0 - z), 1.0) / ((x0 / r0) + (1.0 / ch0));
    float sa = exp(r0 - ra) / max((abs_a / ra) + (1.0 / cha), 0.00999999977648258209228515625);
    float sb = exp(r0 - rb) / max((abs_b / rb) + (1.0 / chb), 0.00999999977648258209228515625);
    return max((sign(b) * (s0 - sb)) - (sign(a) * (s0 - sa)), 0.0);
}

float approx_air_column_density_ratio_along_3d_ray_for_curved_world(vec3 P, vec3 V, float x, float r, float H)
{
    float xz = dot(-P, V);
    float z2 = dot(P, P) - (xz * xz);
    float param = 0.0 - xz;
    float param_1 = x - xz;
    float param_2 = z2;
    float param_3 = r / H;
    return approx_air_column_density_ratio_through_atmosphere(param, param_1, param_2, param_3);
}

vec3 getAtmosphericSky(vec3 rayOrigin, vec3 rayDir, vec3 sun_dir, float sun_power)
{
    int samplesCount = 16;
    vec3 betaR = vec3(5.5000000429572537541389465332031e-06, 1.2999999853491317480802536010742e-05, 2.2399999579647555947303771972656e-05);
    vec3 betaM = vec3(2.0999999833293259143829345703125e-05);
    vec3 param = rayOrigin;
    vec3 param_1 = rayDir;
    float t0;
    float param_2 = t0;
    float t1;
    float param_3 = t1;
    bool _583 = intersectWithEarth(param, param_1, param_2, param_3);
    t0 = param_2;
    t1 = param_3;
    if (!_583)
    {
        return vec3(0.0);
    }
    float march_step = t1 / float(samplesCount);
    float mu = dot(rayDir, sun_dir);
    float param_4 = mu;
    float phaseR = rayleighPhase(param_4);
    float param_5 = mu;
    float phaseM = HenyeyGreensteinPhase(param_5);
    float optical_depthR = 0.0;
    float optical_depthM = 0.0;
    vec3 sumR = vec3(0.0);
    vec3 sumM = vec3(0.0);
    float march_pos = 0.0;
    float t0_1;
    float t1_1;
    for (int i = 0; i < samplesCount; i++)
    {
        vec3 s = rayOrigin + (rayDir * (march_pos + (0.5 * march_step)));
        float height = length(s) - 6371000.0;
        float hr = exp((-height) / 7994.0) * march_step;
        float hm = exp((-height) / 1200.0) * march_step;
        optical_depthR += hr;
        optical_depthM += hm;
        vec3 param_6 = s;
        vec3 param_7 = sun_dir;
        float param_8 = t0_1;
        float param_9 = t1_1;
        bool _669 = intersectWithEarth(param_6, param_7, param_8, param_9);
        t0_1 = param_8;
        t1_1 = param_9;
        vec3 param_10 = s;
        vec3 param_11 = sun_dir;
        float param_12 = t1_1;
        float param_13 = 6371000.0;
        float param_14 = 7994.0;
        float optical_depth_lightR = approx_air_column_density_ratio_along_3d_ray_for_curved_world(param_10, param_11, param_12, param_13, param_14);
        vec3 param_15 = s;
        vec3 param_16 = sun_dir;
        float param_17 = t1_1;
        float param_18 = 6371000.0;
        float param_19 = 1200.0;
        float optical_depth_lightM = approx_air_column_density_ratio_along_3d_ray_for_curved_world(param_15, param_16, param_17, param_18, param_19);
        vec3 tau = (betaR * (optical_depthR + optical_depth_lightR)) + ((betaM * 1.10000002384185791015625) * (optical_depthM + optical_depth_lightM));
        vec3 attenuation = exp(-tau);
        sumR += (attenuation * hr);
        sumM += (attenuation * hm);
        march_pos += march_step;
    }
    return (((sumR * phaseR) * betaR) + ((sumM * phaseM) * betaM)) * sun_power;
}

void main()
{
    vec2 screenUV = vec2(float(gl_GlobalInvocationID.x) / float(pushConsts.gbufferSize.x), float(gl_GlobalInvocationID.y) / float(pushConsts.gbufferSize.y));
    float gbufferDepth = textureLod(textures[pushConsts.gbufferDepthImage], screenUV, 0.0).x;
    vec3 renderResult = vec3(0.0);
    if (gbufferDepth < 0.999000012874603271484375)
    {
        vec4 gbufferPostion = imageLoad(inputImageRGBA16[pushConsts.gbufferPostionImage], ivec2(gl_GlobalInvocationID.xy));
        vec4 gbufferBaseColor = imageLoad(inputImageRGBA16[pushConsts.gbufferBaseColorImage], ivec2(gl_GlobalInvocationID.xy));
        vec4 gbufferNormal = imageLoad(inputImageRGBA16[pushConsts.gbufferNormalImage], ivec2(gl_GlobalInvocationID.xy));
        vec3 param = gbufferPostion.xyz;
        vec3 param_1 = gbufferNormal.xyz;
        vec3 param_2 = uniformBufferObjects[pushConsts.uniformBufferIndex].lightPostion;
        vec3 param_3 = pushConsts.lightColor;
        vec3 param_4 = gbufferBaseColor.xyz;
        float param_5 = 0.5;
        float param_6 = 0.5;
        renderResult = calculateColor(param, param_1, param_2, param_3, param_4, param_5, param_6);
    }
    else
    {
        vec2 aspect_ratio = vec2(float(pushConsts.gbufferSize.x) / float(pushConsts.gbufferSize.y), 1.0);
        float fov = 1.0;
        vec2 point_ndc = vec2(float(gl_GlobalInvocationID.x) / float(pushConsts.gbufferSize.x), float(gl_GlobalInvocationID.y) / float(pushConsts.gbufferSize.y));
        vec3 cam_local_point = vec3((((2.0 * point_ndc.x) - 1.0) * aspect_ratio.x) * fov, ((1.0 - (2.0 * point_ndc.y)) * aspect_ratio.y) * fov, -1.0);
        vec3 cam_origin = vec3(0.0, 6371001.0, 0.0) + uniformBufferObjects[pushConsts.uniformBufferIndex].eyePosition;
        vec3 cam_look_at = vec3(0.0, 6371001.0, 0.0) + uniformBufferObjects[pushConsts.uniformBufferIndex].eyeDir;
        vec3 fwd = normalize(cam_look_at - cam_origin);
        vec3 up = vec3(0.0, 1.0, 0.0);
        vec3 right = cross(up, fwd);
        up = cross(fwd, right);
        vec3 rayOrigin = cam_origin;
        vec3 rayDir = normalize((fwd + (up * cam_local_point.y)) + (right * cam_local_point.x));
        vec3 param_7 = rayOrigin;
        vec3 param_8 = rayDir;
        vec3 param_9 = pushConsts.sun_dir;
        float param_10 = 20.0;
        renderResult = getAtmosphericSky(param_7, param_8, param_9, param_10);
    }
    imageStore(inputImageRGBA16[pushConsts.finalOutputImage], ivec2(gl_GlobalInvocationID.xy), vec4(renderResult, 1.0));
}

 )")
},{"ComputeShader__SourceCode_CabbageGlobalContext_h_211_56",
ShaderCodeModule(R"(#version 460
#extension GL_EXT_nonuniform_qualifier : require
layout(local_size_x = 8, local_size_y = 8, local_size_z = 1) in;

layout(push_constant, std430) uniform PushConsts
{
    vec3 lightColor;
    uint finalOutputImage;
} pushConsts;

layout(set = 0, binding = 3, rgba16) uniform writeonly image2D inputImageRGBA16[];
layout(set = 0, binding = 1) uniform sampler2D textures[1];
layout(set = 0, binding = 3, r32ui) uniform readonly writeonly uimage2D inputImageRGBA8[1];
layout(set = 0, binding = 3, rgba16) uniform readonly image2DArray inputImage2DArray[1];

void main()
{
    imageStore(inputImageRGBA16[pushConsts.finalOutputImage], ivec2(gl_GlobalInvocationID.xy), vec4(pushConsts.lightColor, 1.0));
}

 )")
},
};