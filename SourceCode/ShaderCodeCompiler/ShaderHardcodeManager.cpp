#include <regex>

#include"ShaderHardcodeManager.h"

#include"HardcodeShaders/HardcodeShaders.h"


bool ShaderHardcodeManager::hardcodeFileOpened = false;


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


bool ShaderHardcodeManager::hardcodeShaderCode(const std::string& shaderCode, ShaderLanguage language, ShaderStage inputStage, const std::source_location& sourceLocation)
{
	std::string shaderLanguage = ShaderLanguageFlagToString(language);
	std::string hardcodeVariableName = getHardcodeVariableName(sourceLocation, inputStage);

	switch (language)
	{
	case ShaderLanguage::GLSL:
	    HardcodeShaders::hardcodeShadersGLSL.insert(std::pair(hardcodeVariableName, shaderCode));
		break;
	case ShaderLanguage::HLSL:
	    HardcodeShaders::hardcodeShadersHLSL.insert(std::pair(hardcodeVariableName, shaderCode));
		break;
	//case ShaderLanguage::ESSL:
	//	if (HardcodeShaders::hardcodeShadersESSL.find(hardcodeVariableName) == HardcodeShaders::hardcodeShadersESSL.end())
	//	{
	//		HardcodeShaders::hardcodeShadersESSL.insert(std::pair<std::string, std::string>(hardcodeVariableName, shaderCode));
	//	}
	//	break;
	//case ShaderLanguage::MSL:
	//	if (HardcodeShaders::hardcodeShadersMSL.find(hardcodeVariableName) == HardcodeShaders::hardcodeShadersMSL.end())
	//	{
	//		HardcodeShaders::hardcodeShadersMSL.insert(std::pair<std::string, std::string>(hardcodeVariableName, shaderCode));
	//	}
	//	break;
	default:
		return false;
	}

#if CABBAGE_ENGINE_DEBUG
	if (!hardcodeFileOpened)
	{
		generateHardcodeFiles();
		hardcodeFileOpened = true;
	}

    std::fstream sourceFileStream(CabbageFiles::hardcodeShaderPath + "/HardcodeShaders" + shaderLanguage + ".cpp", std::ios::in | std::ios::out);

	if (sourceFileStream.is_open())
	{
		sourceFileStream.seekg(-int(sizeof("};")), std::ios::end);

		sourceFileStream << "{\"" + hardcodeVariableName + "\"," << std::endl;
		sourceFileStream << "ShaderCodeModule(R\"(" << shaderCode << " )\")" << std::endl;

		sourceFileStream << "}," << std::endl;
		sourceFileStream << "};";

		sourceFileStream.close();
	}
	else
	{
		return false;
	}
#endif

	return true;
}


bool ShaderHardcodeManager::hardcodeShaderCode(const std::vector<uint32_t>& shaderCode, ShaderLanguage language, ShaderStage inputStage, const std::source_location& sourceLocation)
{
	std::string shaderLanguage = ShaderLanguageFlagToString(language);
	std::string hardcodeVariableName = getHardcodeVariableName(sourceLocation, inputStage);

	switch (language)
	{
	case ShaderLanguage::SpirV:
		if (!HardcodeShaders::hardcodeShadersSpirV.contains(hardcodeVariableName))
		{
			HardcodeShaders::hardcodeShadersSpirV.insert(std::pair<std::string, std::vector<uint32_t>>(hardcodeVariableName, shaderCode));
		}
		break;
	//case ShaderLanguage::DXIL:
	//	if (HardcodeShaders::hardcodeShadersDXIL.find(hardcodeVariableName) == HardcodeShaders::hardcodeShadersDXIL.end())
	//	{
	//		HardcodeShaders::hardcodeShadersDXIL.insert(std::pair<std::string, std::vector<uint32_t>>(hardcodeVariableName, shaderCode));
	//	}
	//	break;
	default:
		return false;
	}

#if CABBAGE_ENGINE_DEBUG
	if (!hardcodeFileOpened)
	{
		generateHardcodeFiles();
		hardcodeFileOpened = true;
	}

	std::fstream sourceFileStream(CabbageFiles::hardcodeShaderPath + "/HardcodeShaders" + shaderLanguage + ".cpp", std::ios::in | std::ios::out);

	if (sourceFileStream.is_open())
	{
		sourceFileStream.seekg(-int(sizeof("};")), std::ios::end);

		sourceFileStream << "{\"" + hardcodeVariableName + "\",";
		sourceFileStream << "ShaderCodeModule(std::vector<uint32_t>({";
		for (size_t index = 0; index < shaderCode.size(); index++)
		{
			sourceFileStream << shaderCode[index] << ",";
		}

		sourceFileStream << "}))}," << std::endl;
		sourceFileStream << "};";

		sourceFileStream.close();
	}
	else
	{
		return false;
	}
#endif

	return true;
}


bool ShaderHardcodeManager::generateHardcodeFiles()
{
	{
        std::fstream fileStream(CabbageFiles::hardcodeShaderPath + "/HardcodeShaders.h", std::ios::out);

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
		//fileStream << "	static std::unordered_map<std::string, ShaderCodeModule> hardcodeShadersESSL;" << std::endl;
		//fileStream << "	static std::unordered_map<std::string, ShaderCodeModule> hardcodeShadersMSL;" << std::endl;
		fileStream << "};" << std::endl;

		fileStream.close();
	}

	auto createCodeFile = [&](const std::string &lang)->void
		{
        std::fstream fileStream(CabbageFiles::hardcodeShaderPath + "/HardcodeShaders" + lang + ".cpp", std::ios::out);

			fileStream << "#include\"HardcodeShaders.h\"" << std::endl;
			fileStream << "std::unordered_map<std::string, ShaderCodeModule> HardcodeShaders::hardcodeShaders" + lang + " = {" << std::endl;
			fileStream << "};";

			fileStream.close();
		};

	createCodeFile("SpirV");
	//createCodeFile("DXIL");
	createCodeFile("HLSL");
	createCodeFile("GLSL");
	//createCodeFile("ESSL");
	//createCodeFile("MSL");

	hardcodeFileOpened = true;

	return true;
}


ShaderCodeModule ShaderHardcodeManager::getHardcodeShader(const std::string &hardcodeVariableName, ShaderLanguage language)
{
	switch (language)
	{
	case ShaderLanguage::GLSL:
	{
		if (const auto it = HardcodeShaders::hardcodeShadersGLSL.find(hardcodeVariableName); it != HardcodeShaders::hardcodeShadersGLSL.end())
			return it->second;
		break;
	}
	case ShaderLanguage::HLSL:
	{
	    if (const auto it = HardcodeShaders::hardcodeShadersHLSL.find(hardcodeVariableName); it != HardcodeShaders::hardcodeShadersHLSL.end())
	        return it->second;
		break;
	}
	case ShaderLanguage::SpirV:
	{
	    if (const auto it = HardcodeShaders::hardcodeShadersSpirV.find(hardcodeVariableName); it != HardcodeShaders::hardcodeShadersSpirV.end())
	        return it->second;
		break;
	}
	//case ShaderLanguage::ESSL:
	//{
	//	if (HardcodeShaders::hardcodeShadersESSL.find(hardcodeVariableName) != HardcodeShaders::hardcodeShadersESSL.end())
	//	{
	//		return HardcodeShaders::hardcodeShadersESSL[hardcodeVariableName];
	//	}
	//	break;
	//}
	//case ShaderLanguage::MSL:
	//{
	//	if (HardcodeShaders::hardcodeShadersMSL.find(hardcodeVariableName) != HardcodeShaders::hardcodeShadersMSL.end())
	//	{
	//		return HardcodeShaders::hardcodeShadersMSL[hardcodeVariableName];
	//	}
	//	break;
	//}
	//case ShaderLanguage::DXIL:
	//{
	//	if (HardcodeShaders::hardcodeShadersDXIL.find(hardcodeVariableName) != HardcodeShaders::hardcodeShadersDXIL.end())
	//	{
	//		return HardcodeShaders::hardcodeShadersDXIL[hardcodeVariableName];
	//	}
	//	break;
	//}
	default:
		break;
	}
	return {};
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