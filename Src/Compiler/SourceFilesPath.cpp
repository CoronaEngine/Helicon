#include "SourceFilesPath.h"


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