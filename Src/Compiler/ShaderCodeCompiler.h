#pragma once

#include <cstdint>
#include <source_location>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

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

        struct TireNode
        {
            ShaderBindInfo data;
            TireNode *next[256];
            std::vector<int> nextIdxList;
            bool isLeaf;

            TireNode()
            {
                isLeaf = false;
                for (int idx = 0; idx < 256; ++idx)
                {
                    next[idx] = nullptr;
                }
                // std::memeset(next, 0, sizeof(next));
            }
        };

        struct TireTree
        {
            TireNode *pRoot;

            TireTree()
            {
                pRoot = nullptr;
            }

            void addShaderBindInfo(std::string &name, ShaderBindInfo shaderBindInfo)
            {
                pRoot = pRoot == nullptr ? new TireNode() : pRoot;
                TireNode *tempRoot = pRoot;
                for (char c : name)
                {
                    int idx = c - '\0';
                    if (tempRoot->next[idx] == nullptr)
                    {
                        tempRoot->next[idx] = new TireNode();
                        tempRoot->nextIdxList.push_back(idx);
                    }
                    tempRoot = tempRoot->next[idx];
                }
                tempRoot->isLeaf = true;
                tempRoot->data = shaderBindInfo;
            }

            void travelTireTree(TireNode *root, std::vector<ShaderBindInfo> shaderBindInfoList)
            {
                for (int nextIdx : root->nextIdxList)
                {
                    travelTireTree(root->next[nextIdx], shaderBindInfoList);
                }
                if (root->isLeaf)
                {
                    shaderBindInfoList.push_back(root->data);
                }
            }

            std::vector<ShaderBindInfo> findAllShaderBindInfo()
            {
                TireNode *tempRoot = pRoot;
                std::vector<ShaderBindInfo> shaderBindInfoList;
                if (pRoot != nullptr)
                {
                    travelTireTree(pRoot, shaderBindInfoList);
                }
                return shaderBindInfoList;
            }

            ShaderBindInfo *findShaderBindInfo(const std::string &resourceName)
            {
                TireNode *tempRoot = pRoot;
                for (char c : resourceName)
                {
                    int idx = c - '\0';
                    if (tempRoot->next[idx] == nullptr)
                    {
                        return nullptr;
                    }
                    tempRoot = tempRoot->next[idx];
                }
                return &(tempRoot->data);
            }

            void releaseTireNode(TireNode *root)
            {
                for (TireNode *pNext : root->next)
                {
                    if (pNext != nullptr)
                    {
                        releaseTireNode(pNext);
                    }
                }
                delete root;
            }

            ~TireTree()
            {
                if (pRoot == nullptr)
                {
                    return;
                }
                releaseTireNode(pRoot);
            }
        }tireTree;

        ShaderBindInfo *findShaderBindInfo(const std::string &resourceName)
        {
            return tireTree.findShaderBindInfo(resourceName);
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