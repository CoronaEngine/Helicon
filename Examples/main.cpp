#include <iostream>

#include "Codegen/ControlFlows.h"

#include "Codegen/CustomLibrary.h"

#include"Compiler/ShaderCodeCompiler.h"
#include "Compiler/ShaderLanguageConverter.h"

#include <Codegen/AST/AST.hpp>
#include <Codegen/AST/Parser.hpp>
#include <Codegen/Generator/SlangGenerator.hpp>
#include <ktm/type/vec.h>
#include <utility>

#include <Codegen/RasterizedPipelineObject.h>
#include <Codegen/BuiltinVariate.h>
#include <Codegen/ComputePipelineObject.h>
#include <Codegen/TypeAlias.h>
#include <Compiler/ShaderHardcodeManager.h>

// 自动编译的 shader（相对路径，相对于当前源文件）
// 宏 HLSL(path) 会展开为 "path.hpp"，CMake 会自动编译并生成对应的头文件
#include HLSL(shaders/example.hlsl)

// 保留原有的手动嵌入示例
static std::vector<uint32_t> D__shader_txt {119734787,67072,524299,21,0,131089,1,393227,1,1280527431,1685353262,808793134,0,196622,0,1,262159,0,4,0,196611,5,500,196613,4,0,393221,13,1735550317,828975205,993093947,3879273,196613,10,97,196613,11,98,196613,12,99,131091,2,196641,3,2,262165,6,32,1,262176,7,7,6,262167,8,6,3,393249,9,8,7,7,7,327734,2,4,0,3,131320,5,65789,65592,327734,8,13,0,9,196663,7,10,196663,7,11,196663,7,12,131320,14,262205,6,15,10,262205,6,16,11,262205,6,17,12,393296,8,18,15,16,17,131326,18,65592,};
static ::EmbeddedShader::FunctionProxy<::EmbeddedShader::VariateProxy<::ktm::svec3(int a, int b, int c)>> merge{"merge","int3",{"int","int","int",},&D__shader_txt};

using namespace EmbeddedShader;

struct VertexInput
{
	Float3 inPosition;
	Float3 inNormal;
	Float2 inTexCoord;
	Float3 inColor;
};

struct VertexOutput
{
	Float3 fragPos;
	Float3 fragNormal;
	Float2 fragTexCoord;
	Float3 fragColor;
};

struct TextureStruct
{
	Texture2D<ktm::fvec4> texture;
	Sampler sampler;
};

struct ImageStruct
{
	Texture2D<ktm::fvec4> image;
};

int main(int argc, char* argv[])
{
    auto vs_code = R"(#version 450
#extension GL_EXT_nonuniform_qualifier : enable

layout(push_constant) uniform PushConsts
{
    uint storageBufferIndex;
    uint uniformBufferIndex;
} pushConsts;

layout(set = 3, binding = 0) uniform GlobalUniformParam
{
    float globalTime;
    float globalScale;
    uint frameCount;
    uint padding;
} globalParams[];

layout(set = 1, binding = 0) readonly buffer StorageBufferObject
{
    uint textureIndex;
    mat4 model;
    mat4 view;
    mat4 proj;
    vec3 viewPos;
    vec3 lightColor;
    vec3 lightPos;
} storageBufferObjects[];

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inColor;

layout(location = 0) out vec3 fragPos;
layout(location = 1) out vec3 fragNormal;
layout(location = 2) out vec2 fragTexCoord;
layout(location = 3) out vec3 fragColor;

void main()
{
    mat4 scaledModel = mat4(vec4(storageBufferObjects[pushConsts.storageBufferIndex].model[0].xyz * globalParams[pushConsts.uniformBufferIndex].globalScale, storageBufferObjects[pushConsts.storageBufferIndex].model[0].w),
                            vec4(storageBufferObjects[pushConsts.storageBufferIndex].model[1].xyz * globalParams[pushConsts.uniformBufferIndex].globalScale, storageBufferObjects[pushConsts.storageBufferIndex].model[1].w),
                            vec4(storageBufferObjects[pushConsts.storageBufferIndex].model[2].xyz * globalParams[pushConsts.uniformBufferIndex].globalScale, storageBufferObjects[pushConsts.storageBufferIndex].model[2].w),
                            storageBufferObjects[pushConsts.storageBufferIndex].model[3]);

    gl_Position = storageBufferObjects[pushConsts.storageBufferIndex].proj *
                  storageBufferObjects[pushConsts.storageBufferIndex].view *
                  scaledModel *
                  vec4(inPosition, 1.0);

    fragPos = vec3(scaledModel * vec4(inPosition, 1.0));
    fragNormal = normalize(mat3(transpose(inverse(scaledModel))) * inNormal);
    fragColor = inColor;
    fragTexCoord = inTexCoord;
})";
    auto fs_code = R"(#version 450
#extension GL_EXT_nonuniform_qualifier : enable

layout(push_constant) uniform PushConsts
{
    uint storageBufferIndex;
    uint uniformBufferIndex;
} pushConsts;

layout(set = 3, binding = 0) uniform GlobalUniformParam
{
    float globalTime;
    float globalScale;
    uint frameCount;
    uint padding;
} globalParams[];

layout(set = 1, binding = 0) readonly buffer StorageBufferObject
{
    uint textureIndex;
    mat4 model;
    mat4 view;
    mat4 proj;
    vec3 viewPos;
    vec3 lightColor;
    vec3 lightPos;
} storageBufferObjects[];

layout(set = 0, binding = 0) uniform sampler2D textures[];

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 fragTexCoord;
layout(location = 3) in vec3 inColor;

layout(location = 0) out vec4 outColor;

// ----------------------------------------------------------------------------
float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH * NdotH;

    float nom = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = 3.14159265359 * denom * denom;

    return nom / denom;
}

// ----------------------------------------------------------------------------
float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r * r) / 8.0;

    float nom = NdotV;
    float denom = NdotV * (1.0 - k) + k;

    return nom / denom;
}

// ----------------------------------------------------------------------------
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

// ----------------------------------------------------------------------------
vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

vec3 calculateColor(vec3 WorldPos, vec3 Normal, vec3 albedo, float metallic, float roughness)
{
    vec3 N = normalize(Normal);
    vec3 V = normalize(storageBufferObjects[pushConsts.storageBufferIndex].viewPos - WorldPos);

    // calculate reflectance at normal incidence; if dia-electric (like plastic) use F0
    // of 0.04 and if it's a metal, use the albedo color as F0 (metallic workflow)
    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo, metallic);

    // reflectance equation
    vec3 Lo = vec3(0.0);
    //for(int i = 0; i < 4; ++i)
    {
        // calculate per-light radiance
        vec3 L = normalize(storageBufferObjects[pushConsts.storageBufferIndex].lightPos - WorldPos);
        vec3 H = normalize(V + L);
        //float distance = length(lightPos - WorldPos);
        float attenuation = 1.0;
        vec3 radiance = storageBufferObjects[pushConsts.storageBufferIndex].lightColor * attenuation;

        // Cook-Torrance BRDF
        float NDF = DistributionGGX(N, H, roughness);
        float G = GeometrySmith(N, V, L, roughness);
        vec3 F = fresnelSchlick(clamp(dot(H, V), 0.0, 1.0), F0);

        vec3 numerator = NDF * G * F;
        float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001; // + 0.0001 to prevent divide by zero
        vec3 specular = numerator / denominator;

        // kS is equal to Fresnel
        vec3 kS = F;
        // for energy conservation, the diffuse and specular light can't
        // be above 1.0 (unless the surface emits light); to preserve this
        // relationship the diffuse component (kD) should equal 1.0 - kS.
        vec3 kD = vec3(1.0) - kS;
        // multiply kD by the inverse metalness such that only non-metals
        // have diffuse lighting, or a linear blend if partly metal (pure metals
        // have no diffuse light).
        kD *= 1.0 - metallic;

        // scale light by NdotL
        float NdotL = max(dot(N, L), 0.0);

        // add to outgoing radiance Lo
        Lo += (kD * albedo / 3.14159265359 + specular) * radiance * NdotL;  // note that we already multiplied the BRDF by the Fresnel (kS) so we won't multiply by kS again
    }

    // ambient lighting (note that the next IBL tutorial will replace
    // this ambient lighting with environment lighting).
    vec3 ambient = vec3(0.03) * albedo;

    return ambient + Lo;
}

void main()
{
    vec4 color = vec4(textureLod(textures[storageBufferObjects[pushConsts.storageBufferIndex].textureIndex], fragTexCoord, 0.0));
    outColor = vec4(calculateColor(inPosition, inNormal, color.w > 0.01 ? color.xyz : inColor, 0.5, 0.5),1.0);
})";

    EmbeddedShader::ShaderCodeCompiler vertexCompiler(vs_code,
                                                      EmbeddedShader::ShaderStage::VertexShader,
                                                      EmbeddedShader::ShaderLanguage::GLSL,
                                                      EmbeddedShader::CompilerOption());

    EmbeddedShader::ShaderCodeCompiler fragmentCompiler(fs_code,
                                                        EmbeddedShader::ShaderStage::FragmentShader,
                                                        EmbeddedShader::ShaderLanguage::GLSL,
                                                        EmbeddedShader::CompilerOption());
    using namespace EmbeddedShader::Ast;
	using namespace ktm;

	Float4x4 model;
	Float3x3 modelInverse;
	Float4x4 view;
	Float4x4 proj;
	Float3 viewPos;
	Float3 lightColor;
	Float3 lightPos;
	auto vertex = [&](Aggregate<VertexInput> input)
	{
		Aggregate<VertexOutput> output;
		position() = mul(mul(mul(proj,view),model),Float4(input->inPosition,1.0));
		output->fragPos = mul(model,Float4(input->inPosition,1.0))->xyz();
		output->fragNormal = normalize(mul(modelInverse,input->inNormal));
		output->fragColor = input->inColor;
		output->fragTexCoord = input->inTexCoord;
		return output;
	};

	Aggregate<TextureStruct> textureStruct;

	auto DistributionGGX = [&](const Float3& N, const Float3& H,Float roughness)
	{
		Float a = roughness * roughness;
		Float a2 = a * a;
		Float NdotH = max(dot(N,H),0.0f);
		Float NdotH2 = NdotH * NdotH;

		Float nom = a2;
		Float denom = (NdotH2 * (a2 - 1.0) + 1.0);
		denom = 3.14159265359f * denom * denom;

		return nom / denom;
	};

	auto GeometrySchlickGGX = [&](Float NdotV, const Float& roughness)
	{
		Float r = (roughness + 1.0f);
		Float k = (r * r) / 8.0f;

		Float nom = NdotV;
		Float denom = NdotV * (1.0f - k) + k;

		return nom / denom;
	};

	auto GeometrySmith = [&](const Float3& N, const Float3& V, const Float3& L, const Float& roughness)
	{
		Float NdotV = max(dot(N, V), 0.0f);
		Float NdotL = max(dot(N, L), 0.0f);
		Float ggx2 = GeometrySchlickGGX(NdotV, roughness);
		Float ggx1 = GeometrySchlickGGX(NdotL, roughness);

		return ggx1 * ggx2;
	};

	auto fresnelSchlick = [&](const Float& cosTheta, const Float3& F0)
	{
		return F0 + (fvec3(1) - F0) * pow(clamp(1.0f - cosTheta, 0.0f, 1.0f), 5.0f);
	};

	auto calculateColor = [&](const Float3& WorldPos,const Float3& Normal,const Float3& albedo,const Float& metallic, const Float& roughness)
	{
		auto N = normalize(Normal);
		auto V = normalize(viewPos - WorldPos);

		Float3 F0 = fvec3(0.04f);
		F0 = mix(F0, albedo, metallic);
		Float3 Lo = fvec3(0);

		Float3 L = normalize(lightPos - WorldPos);
		Float3 H = normalize(V + L);
		Float attenuation = 1.0;
		Float3 radiance = lightColor * attenuation;

		Float NDF = DistributionGGX(N,H,roughness);
		Float G = GeometrySmith(N,V,L,roughness);
		Float3 F = fresnelSchlick(clamp(dot(H,V),0.f,1.f),F0);

		Float3 numerator = NDF * G * F;
		Float denominator = 4.0f * max(dot(N, V), 0.0f) * max(dot(N, L), 0.0f) + 0.0001;
		Float3 specular = numerator / denominator;

		auto kS = F;
		auto kD = fvec3(1.f) - kS;
		kD *= 1.f - metallic;

		Float NdotL = max(dot(N, L), 0.0f);
		Lo += (kD * albedo / Float{3.14159265359f} + specular) * radiance * NdotL;

		Float3 ambient = fvec3(0.03) * albedo;
		return ambient + Lo;
	};

	auto fragment = [&](Aggregate<VertexOutput> input)
	{
		Float4 color = textureStruct->texture.sample(textureStruct->sampler,input->fragTexCoord);
		Float3 albedo;
		$IF(color->w > 0.01)
			albedo = color->xyz();
		$ELSE
			albedo = input->fragColor;
		Float4 outColor = Float4(calculateColor(input->fragPos,input->fragNormal,albedo,0.5,0.5),1.0);
		return outColor;
	};

	Texture2D<fvec4> inputImageRGBA16;

	auto acesFilmicToneMapCurve = [&](Float3 x)
	{
		Float a = 2.51f;
		Float b = 0.03f;
		Float c = 2.43f;
		Float d = 0.59f;
		Float e = 0.14f;

		return clamp((x * (a * x + b)) / (x * (c * x + d) + e), fvec3(0.0f), fvec3(1.0f));
	};

	auto acesFilmicToneMapInverse = [&](const Float3& x)
	{
		Float3 a = fvec3(-0.59f) * x + fvec3(0.03f);
		Float3 b = sqrt(fvec3(-1.0127f) * x * x + fvec3(1.3702f) * x + fvec3(0.0009));
		Float3 c = fvec3(2) * (fvec3(2.43f) * x - fvec3(2.51f));
		return ((a - b) / c);
	};

	auto compute = [&]
	{
		Float4 color = inputImageRGBA16[dispatchThreadID()->xy()];
		inputImageRGBA16[dispatchThreadID()->xy()] = Float4(acesFilmicToneMapCurve(color->xyz()),1.f);
	};

	CompilerOption compilerOption = {};
	compilerOption.compileHLSL = false;
	compilerOption.compileDXIL = true;
	compilerOption.compileDXBC = true;
	compilerOption.compileGLSL = true;
	compilerOption.enableBindless = true;

	auto rasterizedPipeline = RasterizedPipelineObject::compile(vertex, fragment,compilerOption);
	auto computePipeline = ComputePipelineObject::compile(compute,uvec3(8,8,1),compilerOption);
	puts(std::get<1>(rasterizedPipeline.vertex->getShaderCode(ShaderLanguage::Slang).shaderCode).c_str());
	puts(std::get<1>(rasterizedPipeline.fragment->getShaderCode(ShaderLanguage::Slang).shaderCode).c_str());
	puts(std::get<1>(computePipeline.compute->getShaderCode(ShaderLanguage::Slang).shaderCode).c_str());

	//puts(std::get<1>(rasterizedPipeline.vertex->getShaderCode(ShaderLanguage::GLSL,true).shaderCode).c_str());

	std::string slangTest = R"(


struct Data
{
	float2 coord;
};

struct ParameterBlockData
{
	ConstantBuffer<Data>.Handle data;
	Texture2D.Handle texture;
	SamplerState.Handle sampler;
	RWTexture2D<uint2>.Handle inImage;
	RWTexture2D<float4>.Handle outImage;
};

ParameterBlock<ParameterBlockData> data;

[shader("fragment")]
float4 main() : SV_TARGET0
{
    return data.texture.Sample(data.sampler,(*(data.data)).coord) * data.outImage[data.inImage[uint2(0,0)]];
})";

	/*[vk::binding(0, 1)]
__DynamicResource<__DynamicResourceKind.Sampler> samplerHandles[];

[vk::binding(0, 2)]
__DynamicResource<__DynamicResourceKind.General> textureHandles[];

[vk::binding(0, 3)]
__DynamicResource<__DynamicResourceKind.General> bufferHandles[];

[vk::binding(0, 4)]
__DynamicResource<__DynamicResourceKind.General> combinedTextureSamplerHandles[];

[vk::binding(0, 5)]
__DynamicResource<__DynamicResourceKind.General> accelerationStructureHandles[];

[vk::binding(0, 6)]
__DynamicResource<__DynamicResourceKind.General> texelBufferHandles[];

export T getDescriptorFromHandle<T>(DescriptorHandle<T> handle) where T : IOpaqueDescriptor
{
	__target_switch
	{
	case spirv:
	case glsl:
		if (T.kind == DescriptorKind.Sampler)
			return samplerHandles[((uint2)handle).x].asOpaqueDescriptor<T>();
		else if (T.kind == DescriptorKind.Texture)
			return textureHandles[((uint2)handle).x].asOpaqueDescriptor<T>();
		else if (T.kind == DescriptorKind.Buffer)
			return bufferHandles[((uint2)handle).x].asOpaqueDescriptor<T>();
		else if (T.kind == DescriptorKind.CombinedTextureSampler)
			return combinedTextureSamplerHandles[((uint2)handle).x].asOpaqueDescriptor<T>();
		else if (T.kind == DescriptorKind.AccelerationStructure)
			return accelerationStructureHandles[((uint2)handle).x].asOpaqueDescriptor<T>();
		else if (T.kind == DescriptorKind.TexelBuffer)
			return texelBufferHandles[((uint2)handle).x].asOpaqueDescriptor<T>();
		else
			return defaultGetDescriptorFromHandle(handle);
	default:
		return defaultGetDescriptorFromHandle(handle);
	}
}*/

	// std::vector<std::vector<uint32_t>> binaryOutputs;
 //    std::vector<std::string> outputs;
 //    ShaderLanguageConverter::slangCompiler(slangTest, {ShaderLanguage::SpirV}, {ShaderLanguage::GLSL}, binaryOutputs, outputs, true);
 //    //puts(outputs[0].c_str());
 //
	// ShaderLanguageConverter::glslangSpirvCompiler(outputs[0], ShaderLanguage::GLSL, ::ShaderStage::FragmentShader);

	system("clear");
	Texture2D<fvec4> image;
	Texture2D<fvec4> image2;
	auto testShader = [&]
	{
		image[Uint2(0,0)] = image2[merge(0,0,0)->xy()];
	};
	compilerOption.compileDXBC = false;
	compilerOption.compileDXIL = false;
	compilerOption.compileHLSL = false;
	compilerOption.compileGLSL = true;
	compilerOption.compileSpirV = true;
	compilerOption.enableBindless = true;
	auto testPipeline = ComputePipelineObject::compile(testShader,uvec3(8,8,1),compilerOption);
	puts(std::get<1>(testPipeline.compute->getShaderCode(ShaderLanguage::Slang).shaderCode).c_str());
	puts(std::get<1>(testPipeline.compute->getShaderCode(ShaderLanguage::GLSL,true).shaderCode).c_str());
	std::cout << textureStruct->texture.node->accessPath();
}
