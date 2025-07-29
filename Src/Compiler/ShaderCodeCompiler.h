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

            uint16_t current_char_index = 0;                 // 当前正在比较的字符索引
            uint16_t search_left = 0;                        // 当前搜索范围的左边界
            uint16_t search_right = bindInfoPool.size() - 1; // 当前搜索范围的右边界

            while (search_left <= search_right && current_char_index < resourceName.length())
            {
                char targetChar = resourceName[current_char_index];
                uint16_t found_idx = (uint16_t)-1; // 记录在本轮二分查找中，第一个字符匹配的位置

                // 在当前 [search_left, search_right] 范围内进行二分查找，寻找第一个字符匹配 targetChar 的元素
                uint16_t low = search_left;
                uint16_t high = search_right;
                uint16_t mid;

                while (low <= high)
                {
                    mid = low + (high - low) / 2;

                    // 检查当前字符串长度是否足够
                    if (bindInfoPool[mid].first.size() <= current_char_index)
                    {
                        // 如果当前字符串比目标字符索引短，说明它无法匹配后续字符，
                        // 且根据排序规则，它应该在所有足够长的字符串之前。
                        // 因此，我们需要向右查找。
                        low = mid + 1;
                        continue;
                    }

                    char middleChar = bindInfoPool[mid].first[current_char_index];

                    if (middleChar == targetChar)
                    {
                        // 找到一个匹配的字符，但可能不是第一个。
                        // 记录下来，并尝试在左半部分继续寻找更早的匹配项。
                        found_idx = mid;
                        high = mid - 1; // 继续向左找，寻找第一个匹配的索引
                    }
                    else if (middleChar < targetChar)
                    {
                        // 中间字符小于目标字符，说明目标字符在右侧
                        low = mid + 1;
                    }
                    else // middleChar > targetChar
                    {
                        // 中间字符大于目标字符，说明目标字符在左侧
                        high = mid - 1;
                    }
                }

                // 如果在本轮字符二分查找中没有找到任何匹配的字符
                if (found_idx == (uint16_t)-1)
                {
                    return nullptr; // 无法找到匹配 resourceName 的字符串
                }

                // 找到了第一个字符匹配的索引 found_idx
                // 现在需要确定所有在该 charIndex 处字符匹配 targetChar 的范围

                // 找到范围的起始 (first_match_start)
                uint16_t first_match_start = found_idx;
                while (first_match_start > search_left)
                {
                    // 防止越界访问
                    if (bindInfoPool[first_match_start - 1].first.size() <= current_char_index ||
                        bindInfoPool[first_match_start - 1].first[current_char_index] != targetChar)
                    {
                        break;
                    }
                    first_match_start--;
                }

                // 找到范围的结束 (last_match_end)
                uint16_t last_match_end = found_idx;
                while (last_match_end < search_right)
                {
                    // 防止越界访问
                    if (bindInfoPool[last_match_end + 1].first.size() <= current_char_index ||
                        bindInfoPool[last_match_end + 1].first[current_char_index] != targetChar)
                    {
                        break;
                    }
                    last_match_end++;
                }

                // 更新下一轮搜索的范围
                search_left = first_match_start;
                search_right = last_match_end;
                current_char_index++; // 准备比较下一个字符
            }

            // 循环结束时，我们已经比较了 resourceName 的所有字符，
            // 并且 search_left 和 search_right 确定了所有与 resourceName 共享前缀的字符串的范围。
            // 现在需要在这个最终的缩小范围 [search_left, search_right] 中，
            // 精确查找与 resourceName 完全匹配的字符串。

            // 遍历最终的缩小范围，进行完整字符串匹配 (这里无法避免，因为需要精确匹配整个字符串)
            // 但这个范围通常会非常小，所以效率很高。
            for (uint16_t i = search_left; i <= search_right; ++i)
            {
                // 关键点：这里进行的是完整的字符串比较，但只在最后缩小到最小范围后进行
                // 这通常比在每次二分迭代中都进行字符串比较要高效得多。
                if (bindInfoPool[i].first == resourceName)
                {
                    return &bindInfoPool[i].second;
                }
            }

            return nullptr; // 未找到精确匹配
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