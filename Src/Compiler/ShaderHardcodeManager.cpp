#include <regex>
#include <fstream>
#include <sstream>
#include <filesystem>

#include"ShaderHardcodeManager.h"


bool ShaderHardcodeManager::hardcodeFileOpened = false;

const std::string ShaderHardcodeManager::hardcodeShaderPath = (std::filesystem::path(HELICON_ROOT_PATH) / "Src" / "Compiler" / "HardcodeShaders").string();


std::string ShaderHardcodeManager::getHardcodeVariableName(const std::source_location& sourceLocation, ShaderStage inputStage)
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
    std::replace(fileName.begin(), fileName.end(), '\\', '_');
    std::replace(fileName.begin(), fileName.end(), '/', '_');
    std::replace(fileName.begin(), fileName.end(), '.', '_');
    std::replace(fileName.begin(), fileName.end(), ':', '_');

	switch (inputStage)
	{
	case ShaderStage::VertexShader:
		fileName = "VertexShader_" + fileName;
		break;
	case ShaderStage::FragmentShader:
		fileName = "FragmentShader_" + fileName;
		break;
	case ShaderStage::ComputeShader:
		fileName = "ComputeShader_" + fileName;
		break;
	default:
		break;
	}

	return fileName + "_" + std::to_string(sourceLocation.line()) + "_" + std::to_string(sourceLocation.column());
}

bool ShaderHardcodeManager::generateHardcodeFiles()
{
	{
        std::fstream fileStream(hardcodeShaderPath + "/HardcodeShaders.h", std::ios::out);

		fileStream << "#pragma once" << std::endl;
        fileStream << "#include <unordered_map>" << std::endl;
		fileStream << "#include\"../ShaderCodeCompiler.h\"" << std::endl;
		fileStream << "class HardcodeShaders" << std::endl;
		fileStream << "{" << std::endl;
		fileStream << "	friend struct ShaderHardcodeManager;" << std::endl;
		fileStream << "	static std::unordered_map<std::string, ShaderCodeModule> hardcodeShadersSpirV;" << std::endl;
		//fileStream << "	static std::unordered_map<std::string, ShaderCodeModule> hardcodeShadersDXIL;" << std::endl;
		fileStream << "	static std::unordered_map<std::string, ShaderCodeModule> hardcodeShadersHLSL;" << std::endl;
		fileStream << "	static std::unordered_map<std::string, ShaderCodeModule> hardcodeShadersGLSL;" << std::endl;
		fileStream << "	static std::unordered_map<std::string, ShaderCodeModule> hardcodeShadersSlang;" << std::endl;
		//fileStream << "	static std::unordered_map<std::string, ShaderCodeModule> hardcodeShadersESSL;" << std::endl;
		//fileStream << "	static std::unordered_map<std::string, ShaderCodeModule> hardcodeShadersMSL;" << std::endl;
		fileStream << "};" << std::endl;

		fileStream.close();
	}

	auto createCodeFile = [&](const std::string &lang)->void
		{
			std::fstream fileStream(hardcodeShaderPath + "/HardcodeShaders" + lang + ".cpp", std::ios::out);

			fileStream << "#include\"HardcodeShaders.h\"" << std::endl;
			fileStream << "std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShaders" + lang + " = {" << std::endl;
			fileStream << "};";

			fileStream.close();
		};

	createCodeFile("SpirV");
	//createCodeFile("DXIL");
	createCodeFile("HLSL");
	createCodeFile("GLSL");
	createCodeFile("Slang");
	//createCodeFile("ESSL");
	//createCodeFile("MSL");

	hardcodeFileOpened = true;

	return true;
}

void ShaderHardcodeManager::addTarget(
	const std::string& shaderCode,
	const std::string& targetName,
	const std::string& itemName,
	const std::source_location& sourceLocation)
{
	createHeader(targetName);

	//Definition
	createTarget(targetName);

	std::fstream hardcodeShaderFile(hardcodePath / ("HardcodeShaders" + targetName + ".cpp"), std::ios::out | std::ios::in);
	hardcodeShaderFile.seekg(-static_cast<int>(sizeof("};")), std::ios::end);
	hardcodeShaderFile << "{\"" + itemName + "_" + getSourceLocationString(sourceLocation) + "\", ShaderCodeModule(R\"(" + shaderCode + ")\"),}," << std::endl;
	hardcodeShaderFile << "};";
}

void ShaderHardcodeManager::addTarget(const std::vector<uint32_t>& shaderCode, const std::string& targetName,
	const std::string& itemName, const std::source_location& sourceLocation)
{
	createHeader(targetName);

	//Definition
	createTarget(targetName);

	std::fstream hardcodeShaderFile(hardcodePath / ("HardcodeShaders" + targetName + ".cpp"), std::ios::out | std::ios::in);
	hardcodeShaderFile.seekg(-static_cast<int>(sizeof("};")), std::ios::end);
	hardcodeShaderFile << "{\"" + itemName + "_" + getSourceLocationString(sourceLocation) + "\", ShaderCodeModule(std::vector<uint32_t>{";
	for (uint32_t code : shaderCode)
	{
		hardcodeShaderFile << code << ",";
	}
	hardcodeShaderFile << "}),}," << std::endl;
	hardcodeShaderFile << "};";
}

std::string ShaderHardcodeManager::ShaderLanguageFlagToString(ShaderLanguage language)
{
	switch (language)
	{
	case ShaderLanguage::GLSL:
		return "GLSL";
	case ShaderLanguage::HLSL:
		return "HLSL";
	case ShaderLanguage::SpirV:
		return "SpirV";
	case ShaderLanguage::Slang:
		return "Slang";
	//case ShaderLanguage::ESSL:
	//	return "ESSL";
	//case ShaderLanguage::MSL:
	//	return "MSL";
	//case ShaderLanguage::DXIL:
	//	return "DXIL";
	default:
		return " ";
	}
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
};)";
		hardcodeFileOpened = true;
		hardcodeShaderFile.close();
	}

	//Declare
	hardcodeShaderFile.open(hardcodePath / "HardcodeShaders.h", std::ios::in | std::ios::out);
	if (auto& ti = targetInfos[targetName]; !ti.isExistTargetItem)
	{
		// 如果没有声明，添加声明
		hardcodeShaderFile.seekg(-static_cast<int>(sizeof("};")), std::ios::end);
		hardcodeShaderFile << "\t""static std::unordered_map<std::string, ShaderCodeModule> hardcodeShaders" + targetName + ";" << std::endl;
		hardcodeShaderFile << "};";
		ti.isExistTargetItem = true;
	}
	hardcodeShaderFile.close();
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
