#include <regex>
#include <fstream>
#include <sstream>
#include <filesystem>

#include"ShaderHardcodeManager.h"


bool ShaderHardcodeManager::hardcodeFileOpened = false;

std::string ShaderHardcodeManager::getItemName(const std::source_location& sourceLocation, ShaderStage inputStage)
{
	return enumToString(inputStage) + "_" + getSourceLocationString(sourceLocation);
}

void ShaderHardcodeManager::addTarget(
	const std::string& shaderCode,
	const std::string& targetName,
	const std::string& itemName)
{
	createHeader(targetName);

	//Definition
	createTarget(targetName);

	std::fstream hardcodeShaderFile(hardcodePath / ("HardcodeShaders" + targetName + ".cpp"), std::ios::out | std::ios::in);
	hardcodeShaderFile.seekg(-static_cast<int>(sizeof("};")), std::ios::end);
	hardcodeShaderFile << "{\"" + itemName + "\", ShaderCodeModule(R\"(" + shaderCode + ")\"),}," << std::endl;
	hardcodeShaderFile << "};";
}

void ShaderHardcodeManager::addTarget(const std::vector<uint32_t>& shaderCode, const std::string& targetName, const std::string& itemName)
{
	createHeader(targetName);

	//Definition
	createTarget(targetName);

	std::fstream hardcodeShaderFile(hardcodePath / ("HardcodeShaders" + targetName + ".cpp"), std::ios::out | std::ios::in);
	hardcodeShaderFile.seekg(-static_cast<int>(sizeof("};")), std::ios::end);
	hardcodeShaderFile << "{\"" + itemName + "\", ShaderCodeModule(std::vector<uint32_t>{";
	for (uint32_t code : shaderCode)
	{
		hardcodeShaderFile << code << ",";
	}
	hardcodeShaderFile << "}),}," << std::endl;
	hardcodeShaderFile << "};";
}

ShaderCodeModule ShaderHardcodeManager::getHardcodeShader(const std::string& targetName, const std::string& itemName)
{
#ifdef CABBAGE_ENGINE_DEBUG
#else

#endif
	return {};
}

void ShaderHardcodeManager::createHeader(const std::string& targetName)
{
	// 检查文件是否存在
	std::fstream hardcodeShaderFile;
	if (!hardcodeFileOpened)
	{
		// 如果不存在，则创建文件
		hardcodeShaderFile.open(hardcodePath / "HardcodeShaders.h", std::ios::out | std::ios::trunc);
		hardcodeShaderFile << R"(#pragma once
#include <unordered_map>
#include "../ShaderCodeCompiler.h"
class HardcodeShaders
{
	static std::unordered_map<std::string,std::unordered_map<std::string, ShaderCodeModule>*> hardcodeShaders;
};)";
		hardcodeShaderFile.close();

		hardcodeShaderFile.open(hardcodePath / "HardcodeShaders.cpp", std::ios::out | std::ios::trunc);
		hardcodeShaderFile << R"(#include"HardcodeShaders.h"
std::unordered_map<std::string,std::unordered_map<std::string, ShaderCodeModule>*> HardcodeShaders::hardcodeShaders = {
};)";
		hardcodeShaderFile.close();
		hardcodeFileOpened = true;
	}

	//Declare
	if (auto& ti = targetInfos[targetName]; !ti.isExistTargetItem)
	{
		// 如果没有声明，添加声明
		hardcodeShaderFile.open(hardcodePath / "HardcodeShaders.h", std::ios::in | std::ios::out);
		hardcodeShaderFile.seekg(-static_cast<int>(sizeof("};")), std::ios::end);
		hardcodeShaderFile << "\t""static std::unordered_map<std::string, ShaderCodeModule> hardcodeShaders" + targetName + ";" << std::endl;
		hardcodeShaderFile << "};";
		hardcodeShaderFile.close();

		hardcodeShaderFile.open(hardcodePath / "HardcodeShaders.cpp", std::ios::in | std::ios::out);
		hardcodeShaderFile.seekg(-static_cast<int>(sizeof("};")), std::ios::end);
		hardcodeShaderFile << "{\"" + targetName + "\",&hardcodeShaders" + targetName + "}," << std::endl;
		hardcodeShaderFile << "};";

		ti.isExistTargetItem = true;
	}
}

void ShaderHardcodeManager::createTarget(const std::string& name)
{
	auto& exist = targetInfos[name];
	if (exist.isExistTargetFile)
		return;

	std::fstream hardcodeShaderFile (hardcodePath / ("HardcodeShaders" + name + ".cpp"), std::ios::out | std::ios::trunc);
	hardcodeShaderFile << R"(#include"HardcodeShaders.h"
std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShaders)" + name + R"( = {
};)";
	exist.isExistTargetFile = true;
}

std::string ShaderHardcodeManager::getSourceLocationString(const std::source_location& sourceLocation)
{
	std::string fileName = sourceLocation.file_name();
	std::regex pattern(R"(CabbageEngine(.*))");
	std::smatch matches;
	if (std::regex_search(fileName, matches, pattern))
	{
		if (matches.size() > 1)
		{
			fileName = matches[1].str();
		}
		else
		{
			throw std::runtime_error("Failed to resolve source path.");
		}
	}
	std::ranges::replace(fileName, '\\', '_');
	std::ranges::replace(fileName, '/', '_');
	std::ranges::replace(fileName, '.', '_');
	std::ranges::replace(fileName, ':', '_');

	return fileName;
}
