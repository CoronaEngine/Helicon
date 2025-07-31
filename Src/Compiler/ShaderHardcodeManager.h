#pragma once

#include "ShaderCodeCompiler.h"
#include <filesystem>


struct ShaderHardcodeManager
{
	static std::string getHardcodeVariableName(const std::source_location& sourceLocation, ShaderStage inputStage);
	static void addTarget(const std::string& shaderCode, const std::string& targetName, const std::string& itemName, const std::source_location& sourceLocation);
	static void addTarget(const std::vector<uint32_t>& shaderCode, const std::string& targetName, const std::string& itemName, const std::source_location& sourceLocation);
private:
	static bool hardcodeFileOpened;
	static const std::string hardcodeShaderPath;
	static bool generateHardcodeFiles();
	static std::string ShaderLanguageFlagToString(ShaderLanguage language);

	static void createHeader(const std::string& targetName);
	static void createTarget(const std::string& name);

	static std::string getSourceLocationString(const std::source_location& sourceLocation);

	struct TargetInfo
	{
		bool isExistTargetItem = false;
		bool isExistTargetFile = false;
	};

	static inline std::unordered_map<std::string, TargetInfo> targetInfos;
	static inline std::filesystem::path hardcodePath = std::filesystem::path(HELICON_ROOT_PATH) / "Src" / "Compiler" / "HardcodeShaders";
};
