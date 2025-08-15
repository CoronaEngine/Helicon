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
	Texture2D<ktm::fvec4> texture = Sampler{};
};

int main(int argc, char* argv[])
{
	using namespace EmbeddedShader::Ast;
	using namespace ktm;

	ShaderHardcodeManager::setHardcodePath(std::filesystem::path(HELICON_ROOT_PATH) / "Src" / "Compiler" / "HardcodeShaders");
/*
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
		Float4 color = textureStruct->texture.sample(input->fragTexCoord);
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

	auto rasterizedPipeline = RasterizedPipelineObject::compile(vertex, fragment);
	puts(std::get<1>(rasterizedPipeline.vertex->getShaderCode(ShaderLanguage::Slang,true).shaderCode).c_str());
	puts(std::get<1>(rasterizedPipeline.fragment->getShaderCode(ShaderLanguage::Slang,true).shaderCode).c_str());
	auto computePipeline = ComputePipelineObject::compile(compute,uvec3(8,8,1));
	puts(std::get<1>(computePipeline.compute->getShaderCode(ShaderLanguage::Slang,true).shaderCode).c_str());
*/
    std::string slangTest = R"(
Sampler2D textures[];
struct Data
{
    uint sampler2dIndex;
}

ConstantBuffer<Data> data;

[shader("fragment")]
float4 main(float2 coord : TEXCOORD) : SV_TARGET0
{
    return textures[data.sampler2dIndex].Sample(coord);
})";

    std::vector<std::vector<uint32_t>> binaryOutputs;
    std::vector<std::string> outputs;
    ShaderLanguageConverter::slangCompiler(slangTest, {ShaderLanguage::SpirV}, {ShaderLanguage::HLSL}, binaryOutputs, outputs, true);
    puts(outputs[0].c_str());
}