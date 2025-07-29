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

            uint16_t current_char_index = 0;                 // ��ǰ���ڱȽϵ��ַ�����
            uint16_t search_left = 0;                        // ��ǰ������Χ����߽�
            uint16_t search_right = bindInfoPool.size() - 1; // ��ǰ������Χ���ұ߽�

            while (search_left <= search_right && current_char_index < resourceName.length())
            {
                char targetChar = resourceName[current_char_index];
                uint16_t found_idx = (uint16_t)-1; // ��¼�ڱ��ֶ��ֲ����У���һ���ַ�ƥ���λ��

                // �ڵ�ǰ [search_left, search_right] ��Χ�ڽ��ж��ֲ��ң�Ѱ�ҵ�һ���ַ�ƥ�� targetChar ��Ԫ��
                uint16_t low = search_left;
                uint16_t high = search_right;
                uint16_t mid;

                while (low <= high)
                {
                    mid = low + (high - low) / 2;

                    // ��鵱ǰ�ַ��������Ƿ��㹻
                    if (bindInfoPool[mid].first.size() <= current_char_index)
                    {
                        // �����ǰ�ַ�����Ŀ���ַ������̣�˵�����޷�ƥ������ַ���
                        // �Ҹ������������Ӧ���������㹻�����ַ���֮ǰ��
                        // ��ˣ�������Ҫ���Ҳ��ҡ�
                        low = mid + 1;
                        continue;
                    }

                    char middleChar = bindInfoPool[mid].first[current_char_index];

                    if (middleChar == targetChar)
                    {
                        // �ҵ�һ��ƥ����ַ��������ܲ��ǵ�һ����
                        // ��¼����������������벿�ּ���Ѱ�Ҹ����ƥ���
                        found_idx = mid;
                        high = mid - 1; // ���������ң�Ѱ�ҵ�һ��ƥ�������
                    }
                    else if (middleChar < targetChar)
                    {
                        // �м��ַ�С��Ŀ���ַ���˵��Ŀ���ַ����Ҳ�
                        low = mid + 1;
                    }
                    else // middleChar > targetChar
                    {
                        // �м��ַ�����Ŀ���ַ���˵��Ŀ���ַ������
                        high = mid - 1;
                    }
                }

                // ����ڱ����ַ����ֲ�����û���ҵ��κ�ƥ����ַ�
                if (found_idx == (uint16_t)-1)
                {
                    return nullptr; // �޷��ҵ�ƥ�� resourceName ���ַ���
                }

                // �ҵ��˵�һ���ַ�ƥ������� found_idx
                // ������Ҫȷ�������ڸ� charIndex ���ַ�ƥ�� targetChar �ķ�Χ

                // �ҵ���Χ����ʼ (first_match_start)
                uint16_t first_match_start = found_idx;
                while (first_match_start > search_left)
                {
                    // ��ֹԽ�����
                    if (bindInfoPool[first_match_start - 1].first.size() <= current_char_index ||
                        bindInfoPool[first_match_start - 1].first[current_char_index] != targetChar)
                    {
                        break;
                    }
                    first_match_start--;
                }

                // �ҵ���Χ�Ľ��� (last_match_end)
                uint16_t last_match_end = found_idx;
                while (last_match_end < search_right)
                {
                    // ��ֹԽ�����
                    if (bindInfoPool[last_match_end + 1].first.size() <= current_char_index ||
                        bindInfoPool[last_match_end + 1].first[current_char_index] != targetChar)
                    {
                        break;
                    }
                    last_match_end++;
                }

                // ������һ�������ķ�Χ
                search_left = first_match_start;
                search_right = last_match_end;
                current_char_index++; // ׼���Ƚ���һ���ַ�
            }

            // ѭ������ʱ�������Ѿ��Ƚ��� resourceName �������ַ���
            // ���� search_left �� search_right ȷ���������� resourceName ����ǰ׺���ַ����ķ�Χ��
            // ������Ҫ��������յ���С��Χ [search_left, search_right] �У�
            // ��ȷ������ resourceName ��ȫƥ����ַ�����

            // �������յ���С��Χ�����������ַ���ƥ�� (�����޷����⣬��Ϊ��Ҫ��ȷƥ�������ַ���)
            // �������Χͨ����ǳ�С������Ч�ʺܸߡ�
            for (uint16_t i = search_left; i <= search_right; ++i)
            {
                // �ؼ��㣺������е����������ַ����Ƚϣ���ֻ�������С����С��Χ�����
                // ��ͨ������ÿ�ζ��ֵ����ж������ַ����Ƚ�Ҫ��Ч�öࡣ
                if (bindInfoPool[i].first == resourceName)
                {
                    return &bindInfoPool[i].second;
                }
            }

            return nullptr; // δ�ҵ���ȷƥ��
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