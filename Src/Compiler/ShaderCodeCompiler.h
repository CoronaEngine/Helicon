#pragma once

#include <cstdint>
#include <source_location>
#include <string>
#include <variant>
#include <vector>
#include <unordered_map>


enum class ShaderLanguage : uint16_t
{
    GLSL,
    HLSL,
    SpirV,
    Slang,
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
        enum BindType
        {
            pushConstantMembers = 0,
            stageInputs = 1,
            stageOutputs = 2,
            uniformBuffers = 3,
            sampledImages = 4,
        };
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

            BindType bindType;
        };

        uint32_t pushConstantSize = 0;
        std::string pushConstantName;

        std::vector<std::pair<std::string, ShaderBindInfo>> bindInfoPool;


        ShaderBindInfo *findShaderBindInfo(const std::string &resourceName)
        {
            if (bindInfoPool.empty())
            {
                return nullptr;
            }
            else
            {
                uint16_t charIndex = 0;

                uint16_t left = 0;
                uint16_t right = bindInfoPool.size() - 1;

                while (left <= right)
                {
                    if (left == right)
                    {
                        return (bindInfoPool[left].first[charIndex] == resourceName[charIndex]) ? &(bindInfoPool[left].second) : nullptr;
                    }
                    if (bindInfoPool[left].first[charIndex] == resourceName[charIndex] &&
                        bindInfoPool[right].first[charIndex] == resourceName[charIndex])
                    {
                        charIndex++;
                    }

                    if (resourceName[charIndex] > bindInfoPool[left].first[charIndex])
                    {
                        left++;
                    }
                    if (resourceName[charIndex] < bindInfoPool[right].first[charIndex])
                    {
                        right--;
                    }

                    if (resourceName[charIndex] < bindInfoPool[left].first[charIndex] ||
                        resourceName[charIndex] > bindInfoPool[right].first[charIndex])
                    {
                        return nullptr;
                    }
                }
            }
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

    ShaderCodeCompiler(const std::string &shaderCode, ShaderStage inputStage, ShaderLanguage language = ShaderLanguage::GLSL, const std::source_location &sourceLocation = std::source_location::current());
    ~ShaderCodeCompiler() = default;

    [[nodiscard]] ShaderCodeModule getShaderCode(ShaderLanguage language) const;

  private:
    std::string hardcodeVariableName;
};