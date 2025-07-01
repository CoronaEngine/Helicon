#include "SourceFilesPath.h"
//
//const std::string CabbageFiles::runtimePath =
//    [] {
//        std::string result = std::filesystem::current_path().string();
//        std::replace(result.begin(), result.end(), '\\', '/');
//        return result;
//    }();
//
//const std::string CabbageFiles::rootPath =
//    [] {
//        std::string resultPath = "";
//        std::string runtimePath = std::filesystem::current_path().string();
//        //std::replace(runtimePath.begin(), runtimePath.end(), '\\', '/');
//        std::regex pattern(R"((.*)CabbageFramework\b)");
//        std::smatch matches;
//        if (std::regex_search(runtimePath, matches, pattern))
//        {
//            if (matches.size() > 1)
//            {
//                resultPath = matches[1].str() + "CabbageFramework";
//            }
//            else
//            {
//                throw std::runtime_error("Failed to resolve source path.");
//            }
//        }
//        std::replace(resultPath.begin(), resultPath.end(), '\\', '/');
//        return resultPath;
//    }();
//
//const std::string CabbageFiles::codePath =
//    [] {
//        std::string resultPath = "";
//        std::string runtimePath = std::filesystem::current_path().string();
//        // std::replace(runtimePath.begin(), runtimePath.end(), '\\', '/');
//        std::regex pattern(R"((.*)CabbageFramework\b)");
//        std::smatch matches;
//        if (std::regex_search(runtimePath, matches, pattern))
//        {
//            if (matches.size() > 1)
//            {
//                resultPath = matches[1].str() + "CabbageFramework";
//            }
//            else
//            {
//                throw std::runtime_error("Failed to resolve source path.");
//            }
//        }
//        std::replace(resultPath.begin(), resultPath.end(), '\\', '/');
//        return resultPath + "/SourceCode";
//    }();
//
//const std::string CabbageFiles::shaderPath =
//    [] {
//        std::string resultPath = "";
//        std::string runtimePath = std::filesystem::current_path().string();
//        // std::replace(runtimePath.begin(), runtimePath.end(), '\\', '/');
//        std::regex pattern(R"((.*)CabbageFramework\b)");
//        std::smatch matches;
//        if (std::regex_search(runtimePath, matches, pattern))
//        {
//            if (matches.size() > 1)
//            {
//                resultPath = matches[1].str() + "CabbageFramework";
//            }
//            else
//            {
//                throw std::runtime_error("Failed to resolve source path.");
//            }
//        }
//        std::replace(resultPath.begin(), resultPath.end(), '\\', '/');
//        return resultPath + "/SourceCode" + "/CabbageFramework/CabbageMultimedia";
//    }();
//
//const std::string CabbageFiles::hardcodeShaderPath =
//    [] {
//        std::string resultPath = "";
//        std::string runtimePath = std::filesystem::current_path().string();
//        // std::replace(runtimePath.begin(), runtimePath.end(), '\\', '/');
//        std::regex pattern(R"((.*)CabbageFramework\b)");
//        std::smatch matches;
//        if (std::regex_search(runtimePath, matches, pattern))
//        {
//            if (matches.size() > 1)
//            {
//                resultPath = matches[1].str() + "CabbageFramework";
//            }
//            else
//            {
//                throw std::runtime_error("Failed to resolve source path.");
//            }
//        }
//        std::replace(resultPath.begin(), resultPath.end(), '\\', '/');
//        return resultPath + "/SourceCode" + "/CabbageFramework/CabbageFoundation/ShaderCodeCompiler/HardcodeShaders";
//    }();


std::vector<uint32_t> CabbageFiles::readBinaryFile(const std::string_view filename)
{
    std::ifstream file(filename.data(), std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
        throw std::runtime_error("failed to open file!");
    }

    const size_t fileSize = file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), static_cast<std::streamsize>(fileSize));

    file.close();

    std::vector<uint32_t> result;
    result.resize(buffer.size() / 4);
    memcpy(result.data(), buffer.data(), buffer.size() * sizeof(char));

    return result;
}

std::string CabbageFiles::readStringFile(const std::string_view file_path)
{
    std::ifstream file(file_path.data());
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open the file.");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    file.close();
    return buffer.str();
}