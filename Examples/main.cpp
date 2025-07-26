#include <iostream>

#include "Codegen/ControlFlows.h"

#include "Codegen/CustomLibrary.h"

#include"Compiler/ShaderCodeCompiler.h"

#include <Codegen/AST/Parser.hpp>
#include <Codegen/AST/AST.hpp>
#include <Codegen/Generator/SlangGenerator.hpp>
#include <utility>
#include <ktm/type/vec.h>

#include <Codegen/RasterizedPipelineObject.h>
#include <Codegen/BuiltinVariate.h>
#include <Codegen/TypeAlias.h>

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

int main(int argc, char* argv[])
{
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

	Texture2D<fvec4> texture;
	Sampler sampler;

	auto DistributionGGX = [&](Float3 N,Float3 H,Float roughness)
	{
		Float a = roughness * roughness;
		Float a2 = a * a;
		Float NdotH = max(dot(N,H),{0.0});
		Float NdotH2 = NdotH * NdotH;

		Float nom = a2;
		Float denom = (NdotH2 * (a2 - 1.0) + 1.0);
		Float NewDenom = 3.14159265359f * denom * denom;

		return nom / NewDenom;
	};

	auto GeometrySchlickGGX = [&](Float NdotV,Float roughness)
	{
		Float r = (roughness + 1.0f);
		Float k = (r * r) / 8.0f;

		Float nom = NdotV;
		Float denom = NdotV * (1.0f - k) + k;

		return nom / denom;
	};

	auto GeometrySmith = [&](Float3 N, Float3 V, Float3 L, Float roughness)
	{
		Float NdotV = max(dot(N, V), {0.0f});
		Float NdotL = max(dot(N, L), {0.0f});
		Float ggx2 = GeometrySchlickGGX(NdotV, roughness);
		Float ggx1 = GeometrySchlickGGX(NdotL, roughness);

		return ggx1 * ggx2;
	};

	auto fresnelSchlick = [&](Float cosTheta, Float3 F0)
	{
		return F0 + (fvec3(1) - F0) * pow(clamp(1.0f - cosTheta, {0.0}, {1.0}), {5.0});
	};

	auto calculateColor = [&](Float3 WorldPos,Float3 Normal,Float3 albedo,Float metallic, Float roughness)
	{
		auto N = normalize(Normal);
		auto V = normalize(viewPos - WorldPos);

		Float3 F0 = fvec3(0.04f);
		F0 = lerp(F0, albedo, metallic);
		Float3 Lo = fvec3(0);

		Float3 L = normalize(lightPos - WorldPos);
		Float3 H = normalize(V + L);
		Float attenuation = 1.0;
		Float3 radiance = lightColor * attenuation;

		Float NDF = DistributionGGX(N,H,roughness);
		Float G = GeometrySmith(N,V,L,roughness);
		Float3 F = fresnelSchlick(clamp(dot(H,V),{0},{1}),F0);

		Float3 numerator = NDF * G * F;
		Float denominator = 4.0f * max(dot(N, V), {0.0}) * max(dot(N, L), {0.0}) + 0.0001;
		Float3 specular = numerator / denominator;

		auto kS = F;
		auto kD = fvec3(1.f) - kS;
		kD *= 1.f - metallic;

		Float NdotL = max(dot(N, L), {0.0f});
		Lo += (kD * albedo / Float{3.14159265359f} + specular) * radiance * NdotL;

		Float3 ambient = fvec3(0.03) * albedo;
		return ambient + Lo;
	};

	auto fragment = [&](Aggregate<VertexOutput> input)
	{
		Float4 color = texture.sample(sampler,input->fragTexCoord);
		Float3 albedo;
		$IF(color->w > 0.01)
			albedo = color->xyz();
		$ELSE
			albedo = input->fragColor;
		Float4 outColor = Float4(calculateColor(input->fragPos,input->fragNormal,albedo,0.5,0.5),1.0);
		return outColor;
	};

	Parser::setBindless(true);
	auto pipeline = RasterizedPipelineObject::parse(vertex, fragment);
	puts(pipeline.vertexGeneration.c_str());
	puts(pipeline.fragmentGeneration.c_str());

    ShaderCodeCompiler vertxShader(pipeline.vertexGeneration, ::ShaderStage::VertexShader,ShaderLanguage::Slang);
    ShaderCodeCompiler fragShader(pipeline.fragmentGeneration, ::ShaderStage::FragmentShader,ShaderLanguage::Slang);
}
