#include "SourceFilesPath.h"

const std::string CabbageFiles::runtimePath =
    [] {
        std::string result = std::filesystem::current_path().string();
        std::replace(result.begin(), result.end(), '\\', '/');
        return result;
    }();

const std::string CabbageFiles::rootPath =
    [] {
        std::string resultPath = "";
        std::string runtimePath = std::filesystem::current_path().string();
        //std::replace(runtimePath.begin(), runtimePath.end(), '\\', '/');
        std::regex pattern(R"((.*)CabbageEngine\b)");
        std::smatch matches;
        if (std::regex_search(runtimePath, matches, pattern))
        {
            if (matches.size() > 1)
            {
                resultPath = matches[1].str() + "CabbageEngine";
            }
            else
            {
                throw std::runtime_error("Failed to resolve source path.");
            }
        }
        std::replace(resultPath.begin(), resultPath.end(), '\\', '/');
        return resultPath;
    }();

const std::string CabbageFiles::codePath =
    [] {
        std::string resultPath = "";
        std::string runtimePath = std::filesystem::current_path().string();
        // std::replace(runtimePath.begin(), runtimePath.end(), '\\', '/');
        std::regex pattern(R"((.*)CabbageEngine\b)");
        std::smatch matches;
        if (std::regex_search(runtimePath, matches, pattern))
        {
            if (matches.size() > 1)
            {
                resultPath = matches[1].str() + "CabbageEngine";
            }
            else
            {
                throw std::runtime_error("Failed to resolve source path.");
            }
        }
        std::replace(resultPath.begin(), resultPath.end(), '\\', '/');
        return resultPath + "/SourceCode";
    }();

const std::string CabbageFiles::shaderPath =
    [] {
        std::string resultPath = "";
        std::string runtimePath = std::filesystem::current_path().string();
        // std::replace(runtimePath.begin(), runtimePath.end(), '\\', '/');
        std::regex pattern(R"((.*)CabbageEngine\b)");
        std::smatch matches;
        if (std::regex_search(runtimePath, matches, pattern))
        {
            if (matches.size() > 1)
            {
                resultPath = matches[1].str() + "CabbageEngine";
            }
            else
            {
                throw std::runtime_error("Failed to resolve source path.");
            }
        }
        std::replace(resultPath.begin(), resultPath.end(), '\\', '/');
        return resultPath + "/SourceCode" + "/CabbageFramework/CabbageMultimedia";
    }();

const std::string CabbageFiles::hardcodeShaderPath =
    [] {
        std::string resultPath = "";
        std::string runtimePath = std::filesystem::current_path().string();
        // std::replace(runtimePath.begin(), runtimePath.end(), '\\', '/');
        std::regex pattern(R"((.*)CabbageEngine\b)");
        std::smatch matches;
        if (std::regex_search(runtimePath, matches, pattern))
        {
            if (matches.size() > 1)
            {
                resultPath = matches[1].str() + "CabbageEngine";
            }
            else
            {
                throw std::runtime_error("Failed to resolve source path.");
            }
        }
        std::replace(resultPath.begin(), resultPath.end(), '\\', '/');
        return resultPath + "/SourceCode" + "/CabbageFramework/CabbageFoundation/ShaderCodeCompiler/HardcodeShaders";
    }();