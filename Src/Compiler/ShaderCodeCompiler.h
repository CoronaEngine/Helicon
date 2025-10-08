#pragma once

#include <cstdint>
#include <source_location>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace EmbeddedShader
{
    enum class ShaderLanguage : uint16_t
    {
        GLSL,
        HLSL,
        DXIL,
        DXBC,
        SpirV,
        Slang,
    };

    std::string enumToString(ShaderLanguage language);

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

    std::string enumToString(ShaderStage stage);

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

                texture,
                sampler,
                rawBuffer,
                storageTexture,
                storageBuffer,
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

            std::unordered_map<std::string, ShaderBindInfo> bindInfoPool;

            ShaderBindInfo *findShaderBindInfo(const std::string &resourceName)
            {
                auto it = bindInfoPool.find(resourceName);
                if (it != bindInfoPool.end())
                {
                    return &it->second;
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

        ShaderCodeModule(std::string shaderCode,ShaderResources shaderResources)
            : shaderResources(std::move(shaderResources)),shaderCode(std::move(shaderCode))
        {
        }

        ShaderCodeModule(std::vector<uint32_t> shaderCode,ShaderResources shaderResources)
            : shaderResources(std::move(shaderResources)),shaderCode(std::move(shaderCode))
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

        struct CompilerOption
        {
            bool compileGLSL = true;
            bool compileHLSL = true;
            bool compileDXIL = true;
            bool compileDXBC = true;
            bool compileSpirV = true;
            bool enableBindless = true;
        };

        ShaderCodeCompiler(const std::string &shaderCode, ShaderStage inputStage, ShaderLanguage language = ShaderLanguage::GLSL, CompilerOption option = {}, const std::source_location &sourceLocation = std::source_location::current());
        ~ShaderCodeCompiler() = default;

        [[nodiscard]] ShaderCodeModule getShaderCode(ShaderLanguage language, bool bindless = false) const;
        void compile(const std::string& shaderCode, ShaderStage inputStage, ShaderLanguage language = ShaderLanguage::GLSL, CompilerOption option = {}) const;
    private:
        std::string sourceLocationStr;
        std::string stage;
    };
}