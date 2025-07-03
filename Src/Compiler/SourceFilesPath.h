#pragma once

#include<vector>
#include<fstream>
#include<sstream>
#include<filesystem>
#include<regex>

struct CabbageFiles
{
    static std::vector<uint32_t> readBinaryFile(const std::string_view filename);
    static std::string readStringFile(const std::string_view file_path);
};
