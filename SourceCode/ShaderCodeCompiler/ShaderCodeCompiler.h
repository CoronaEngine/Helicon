#pragma once

#include <cstdint>
#include <source_location>
#include <string>
#include <variant>
#include <vector>

#include"CabbageFramework/CabbageCommon/CabbageCommon.h"


enum class ShaderLanguage : uint16_t
{
    GLSL,
    HLSL,
    SpirV,
};

enum class ShaderStage : uint16_t
{
    VertexShader = 0,
    FragmentShader = 1,
    ComputeShader = 2,
    // RayGenShader = 3,
    // IntersectShader = 4,
    // AnyHitShader = 5,
    // ClosestHitShader = 6,
    // MissShader = 7,
};

struct ShaderCodeModule
{
    struct ShaderResources
    {
        struct ShaderBindInfo
        {
            uint32_t set = 0;
            uint32_t binding = 0;
            uint32_t location = 0;

            std::string variateName;
            std::string typeName;
            uint64_t elementCount = 0;
            uint32_t typeSize = 0;
            uint64_t byteOffset = 0;
        };

        uint32_t pushConstantSize = 0;
        std::string pushConstantName;
        std::vector<ShaderBindInfo> pushConstantMembers;

        std::vector<ShaderBindInfo> stageInputs;
        std::vector<ShaderBindInfo> stageOutputs;
        std::vector<ShaderBindInfo> uniformBuffers;
        std::vector<ShaderBindInfo> sampledImages;

        ShaderBindInfo *findPushConstantMembers(const std::string_view resourceName)
        {
            for (auto &pushConstantMember : pushConstantMembers)
            {
                if (pushConstantMember.variateName == resourceName)
                {
                    return &pushConstantMember;
                }
            }
            return nullptr;
        }

        ShaderBindInfo *findStageInputs(const std::string_view resourceName)
        {
            for (auto &stageInput : stageInputs)
            {
                if (stageInput.variateName == resourceName)
                {
                    return &stageInput;
                }
            }
            return nullptr;
        }

        ShaderBindInfo *findStageOutputs(const std::string_view resourceName)
        {
            for (auto &stageOutput : stageOutputs)
            {
                if (stageOutput.variateName == resourceName)
                {
                    return &stageOutput;
                }
            }
            return nullptr;
        }

        ShaderBindInfo *findUniformBuffers(const std::string_view resourceName)
        {
            for (auto &uniformBuffer : uniformBuffers)
            {
                if (uniformBuffer.variateName == resourceName)
                {
                    return &uniformBuffer;
                }
            }
            return nullptr;
        }

        ShaderBindInfo *findSampledImages(const std::string_view resourceName)
        {
            for (auto &sampledImage : sampledImages)
            {
                if (sampledImage.variateName == resourceName)
                {
                    return &sampledImage;
                }
            }
            return nullptr;
        }
    } shaderResources;

    ShaderCodeModule() = default;
    ~ShaderCodeModule() = default;

    ShaderCodeModule(std::string shaderCode)
        : shaderCode(std::move(shaderCode))
    {
    }
    ShaderCodeModule(std::vector<uint32_t> shaderCode)
        : shaderCode(std::move(shaderCode))
    {
    }

    operator std::string()
    {
        return std::get<std::string>(shaderCode);
    }

    operator std::vector<uint32_t>()
    {
        return std::get<std::vector<uint32_t>>(shaderCode);
    }

    std::variant<std::vector<uint32_t>, std::string> shaderCode;
};

struct ShaderCodeCompiler
{
  public:
    // ShaderCodeCompiler(const std::string &shaderCode, ShaderStage inputStage, ShaderLanguage language = ShaderLanguage::GLSL, const std::source_location &sourceLocation = std::source_location::current());
    // ShaderCodeCompiler(const std::vector<uint32_t> &shaderCode, ShaderStage inputStage, ShaderLanguage language = ShaderLanguage::GLSL, const std::source_location &sourceLocation = std::source_location::current());

    ShaderCodeCompiler(const std::string &shaderCodePath, ShaderStage inputStage, ShaderLanguage language = ShaderLanguage::GLSL, const std::source_location &sourceLocation = std::source_location::current());
    ~ShaderCodeCompiler() = default;

    [[nodiscard]] ShaderCodeModule getShaderCode(ShaderLanguage language) const;

  private:
    std::string hardcodeVariableName;
};