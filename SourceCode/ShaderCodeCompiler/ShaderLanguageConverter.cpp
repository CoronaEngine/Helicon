#include <iostream>

#include <glslang/Public/ShaderLang.h>
#include <glslang/Public/ResourceLimits.h>
#include <SPIRV/GlslangToSpv.h>
//#include <glslang/Include/ResourceLimits.h>

#include <spirv_cross.hpp>
#include <spirv_parser.hpp>
#include <spirv_glsl.hpp>
#include <spirv_hlsl.hpp>
#include <spirv_msl.hpp>

//#include <slang/slang.h>
//#include <slang/slang-com-ptr.h>
//#include <slang/slang-com-helper.h>

#include"ShaderLanguageConverter.h"

#include <utility>


std::vector<uint32_t> ShaderLanguageConverter::glslangSpirvCompiler(std::string shaderCode, ShaderLanguage inputLanguage, ShaderStage inputStage)
{
	// GLSL version is default by 460
	// Higher versions are compatible with lower versions
	// Version in HLSL is disabled

	std::vector<uint32_t> resultSpirvCode;

	glslang::EShSource shaderLang;
	switch (inputLanguage)
	{
	case ShaderLanguage::GLSL:
		shaderLang = glslang::EShSourceGlsl;
		break;
	case ShaderLanguage::HLSL:
		shaderLang = glslang::EShSourceHlsl;
		break;
	default:
		return resultSpirvCode;
	}

	EShLanguage stage = EShLangVertex;
	switch (inputStage)
	{
	case ShaderStage::VertexShader: stage = EShLangVertex; break;
	case ShaderStage::FragmentShader: stage = EShLangFragment; break;
	case ShaderStage::ComputeShader: stage = EShLangCompute; break;
	default:return resultSpirvCode;
	}

	std::vector<const char*> shaderSources;
	shaderSources.push_back(shaderCode.c_str());

	glslang::InitializeProcess();

	glslang::TShader shader(stage);
	shader.setStrings(shaderSources.data(), 1);
	shader.setEnvInput(shaderLang, stage, glslang::EShClientVulkan, 460);
	shader.setEnvClient(glslang::EShClientVulkan, glslang::EShTargetVulkan_1_3);
	shader.setEnvTarget(glslang::EShTargetSpv, glslang::EShTargetSpv_1_6);
	shader.setEntryPoint("main");

	if (!shader.parse(GetDefaultResources(), 460, false, EShMsgDefault))
	{
		std::cerr << shader.getInfoLog();
		return resultSpirvCode;
	}

	glslang::TProgram program;
	program.addShader(&shader);
	if (!program.link(EShMsgVulkanRules))
	{
		std::cerr << program.getInfoLog();
		return resultSpirvCode;
	}


	if (!program.buildReflection(EShReflectionAllBlockVariables | EShReflectionIntermediateIO))
    {
        //std::cout << "build Reflection Error" << std::endl;
    }
    else
    {
        //std::cout << program.getNumLiveUniformBlocks() << std::endl;
        //program.dumpReflection();
    }  

	const auto intermediate = program.getIntermediate(stage);

	glslang::GlslangToSpv(*intermediate, resultSpirvCode);

	glslang::FinalizeProcess();

	return resultSpirvCode;
}


std::string ShaderLanguageConverter::spirvCrossConverter(std::vector<uint32_t> spirv_file, ShaderLanguage targetLanguage, int32_t targetVersion)
{
	std::string resultCode = "";

	try
	{
		switch (targetLanguage)
		{
		case ShaderLanguage::GLSL:
		//case ShaderLanguage::ESSL:
		{
			spirv_cross::CompilerGLSL compiler(spirv_file);

			spirv_cross::CompilerGLSL::Options opts = compiler.get_common_options();
			opts.enable_420pack_extension = false;
			opts.version = 460;
			opts.vulkan_semantics = true;
			opts.es = false;
			compiler.set_common_options(opts);

			resultCode = compiler.compile();
			break;
		}
		case ShaderLanguage::HLSL:
		{
			spirv_cross::CompilerHLSL compiler(spirv_file);

			spirv_cross::CompilerHLSL::Options opts = compiler.get_hlsl_options();
		    opts.shader_model = 67;
			compiler.set_hlsl_options(opts);

			resultCode = compiler.compile();
			break;
		}
		default:
			break;
		}
	}
	catch (const spirv_cross::CompilerError& error)
	{
		std::cout << error.what();
	}

	return resultCode;
}

//
//static std::string slangCompiler(std::string _filePath, ShaderLanguage targetLanguage)
//{
//    std::string result;
//    Slang::ComPtr<slang::IGlobalSession> slangGlobalSession;
//    slang::createGlobalSession(slangGlobalSession.writeRef());
//    slang::SessionDesc sessionDesc = {};
//    slang::TargetDesc targetDesc = {};
//    switch (targetLanguage)
//    {
//    case ShaderLanguage::GLSL:
//        // case ShaderLanguage::ESSL:
//        {
//            targetDesc.format = SLANG_GLSL;
//            slangGlobalSession->findProfile("glsl_460");
//            break;
//        }
//    case ShaderLanguage::HLSL: {
//        targetDesc.format = SLANG_HLSL;
//        slangGlobalSession->findProfile("sm_6_7");
//        break;
//    }
//    case ShaderLanguage::SpirV: {
//        targetDesc.format = SLANG_SPIRV;
//        slangGlobalSession->findProfile("spirv_1_6");
//        targetDesc.flags = SLANG_TARGET_FLAG_GENERATE_SPIRV_DIRECTLY;
//        break;
//    }
//    // case ShaderLanguage::MSL:
//    //	targetDesc.format = SLANG_METAL; break;
//    // case ShaderLanguage::DXIL:
//    //	targetDesc.format = SLANG_DXIL; break;
//    default:
//        return result;
//        break;
//    }
//    sessionDesc.targets = &targetDesc;
//    sessionDesc.defaultMatrixLayoutMode = SLANG_MATRIX_LAYOUT_COLUMN_MAJOR;
//    sessionDesc.targetCount = 1;
//    Slang::ComPtr<slang::ISession> session;
//    (slangGlobalSession->createSession(sessionDesc, session.writeRef()));
//    slang::IModule *slangModule = nullptr;
//    {
//        Slang::ComPtr<slang::IBlob> diagnosticBlob;
//        slangModule = session->loadModule(_filePath.c_str(), diagnosticBlob.writeRef());
//    }
//    Slang::ComPtr<slang::IEntryPoint> entryPoint;
//    slangModule->findEntryPointByName("main", entryPoint.writeRef());
//    std::vector<slang::IComponentType *> componentTypes;
//    componentTypes.push_back(slangModule);
//    componentTypes.push_back(entryPoint);
//    Slang::ComPtr<slang::IComponentType> composedProgram;
//    {
//        Slang::ComPtr<slang::IBlob> diagnosticsBlob;
//        SlangResult result = session->createCompositeComponentType(
//            componentTypes.data(), componentTypes.size(), composedProgram.writeRef(), diagnosticsBlob.writeRef());
//    }
//    Slang::ComPtr<slang::IBlob> spirvCode;
//    {
//        Slang::ComPtr<slang::IBlob> diagnosticsBlob;
//        SlangResult result = composedProgram->getEntryPointCode(0, 0, spirvCode.writeRef(), diagnosticsBlob.writeRef());
//    }
//    result.resize(spirvCode->getBufferSize() / sizeof(char));
//    memcpy(result.data(), spirvCode->getBufferPointer(), spirvCode->getBufferSize());
//    return result;
//}


//get Reflected Bind Info
ShaderCodeModule::ShaderResources ShaderLanguageConverter::spirvCrossReflectedBindInfo(std::vector<uint32_t> spirv_file, ShaderLanguage targetLanguage, int32_t targetVersion)
{
	ShaderCodeModule::ShaderResources result = {};
    spirv_cross::ShaderResources res{};

    spirv_cross::CompilerGLSL* compiler{};
    switch (targetLanguage)
    {
        case ShaderLanguage::GLSL: {
            compiler = new spirv_cross::CompilerGLSL(std::move(spirv_file));

            spirv_cross::CompilerGLSL::Options opts = compiler->get_common_options();
            opts.enable_420pack_extension = false;
            if (targetVersion > 0)
            {
                opts.version = targetVersion;
            }
            //opts.es = (targetLanguage == ShaderLanguage::ESSL);
            opts.es = false;
            compiler->set_common_options(opts);
            res = compiler->get_shader_resources();
            break;
        }
        case ShaderLanguage::HLSL: {
            auto hlsl_compiler = new spirv_cross::CompilerHLSL{std::move(spirv_file)};
            compiler = hlsl_compiler;
            auto hlsl_options = hlsl_compiler->get_hlsl_options();
            hlsl_options.shader_model = 67;
            hlsl_compiler->set_hlsl_options(hlsl_options);

            res = compiler->get_shader_resources();
            break;
        }
        default: throw std::runtime_error("unsupported shader language");
    }


	for (auto& item : res.uniform_buffers)
	{
		ShaderCodeModule::ShaderResources::ShaderBindInfo bindInfo = {};

		bindInfo.variateName = item.name;
		bindInfo.typeName = "uniform";
		bindInfo.elementCount = compiler->get_type((uint64_t)item.base_type_id).member_types.size();
		bindInfo.typeSize = (uint32_t)compiler->get_declared_struct_size(compiler->get_type(item.base_type_id));

		bindInfo.set = compiler->get_decoration(item.id, spv::DecorationDescriptorSet);
		bindInfo.binding = compiler->get_decoration(item.id, spv::DecorationBinding);
		bindInfo.location = compiler->get_decoration(item.id, spv::DecorationLocation);

		result.uniformBuffers.push_back(bindInfo);
	}

	for (auto& item : res.sampled_images)
	{
		ShaderCodeModule::ShaderResources::ShaderBindInfo bindInfo = {};

		bindInfo.typeName = "sampler2D";
		bindInfo.variateName = item.name;

		bindInfo.set = compiler->get_decoration(item.id, spv::DecorationDescriptorSet);
		bindInfo.binding = compiler->get_decoration(item.id, spv::DecorationBinding);
		bindInfo.location = compiler->get_decoration(item.id, spv::DecorationLocation);
		result.sampledImages.push_back(bindInfo);
	}

	for (auto& item : res.stage_inputs)
	{
		ShaderCodeModule::ShaderResources::ShaderBindInfo bindInfo = {};

		bindInfo.variateName = item.name;

		const spirv_cross::SPIRType& base_type = compiler->get_type(item.base_type_id);
		bindInfo.elementCount = base_type.vecsize * base_type.columns;
		bindInfo.typeSize = 4 * base_type.vecsize * base_type.columns;

		switch (base_type.basetype)
		{
		case spirv_cross::SPIRType::Float:
			bindInfo.typeName = "float";
			break;
		case spirv_cross::SPIRType::UInt:
			bindInfo.typeName = "uint";
			break;
		case spirv_cross::SPIRType::Int:
			bindInfo.typeName = "int";
			break;
		default:
			break;
		}

		bindInfo.set = compiler->get_decoration(item.id, spv::DecorationDescriptorSet);
		bindInfo.binding = compiler->get_decoration(item.id, spv::DecorationBinding);
		bindInfo.location = compiler->get_decoration(item.id, spv::DecorationLocation);
		result.stageInputs.push_back(bindInfo);
	}

	for (auto& item : res.stage_outputs)
	{
		ShaderCodeModule::ShaderResources::ShaderBindInfo bindInfo = {};

		bindInfo.variateName = item.name;

		const spirv_cross::SPIRType& base_type = compiler->get_type(item.base_type_id);
		bindInfo.elementCount = base_type.vecsize * base_type.columns;
		bindInfo.typeSize = 4 * base_type.vecsize * base_type.columns;

		switch (base_type.basetype)
		{
		case spirv_cross::SPIRType::Float:
			bindInfo.typeName = "float";
			break;
		case spirv_cross::SPIRType::UInt:
			bindInfo.typeName = "uint";
			break;
		case spirv_cross::SPIRType::Int:
			bindInfo.typeName = "int";
			break;
		default:
			break;
		}

		bindInfo.set = compiler->get_decoration(item.id, spv::DecorationDescriptorSet);
		bindInfo.binding = compiler->get_decoration(item.id, spv::DecorationBinding);
		bindInfo.location = compiler->get_decoration(item.id, spv::DecorationLocation);
		result.stageOutputs.push_back(bindInfo);
	}

	for (auto& item : res.push_constant_buffers)
	{
		result.pushConstantName = item.name;
		result.pushConstantSize = (uint32_t)compiler->get_declared_struct_size(compiler->get_type((uint64_t)item.base_type_id));

		//obtain all the push constant member
		spirv_cross::SmallVector<spirv_cross::BufferRange> ranges = compiler->get_active_buffer_ranges(item.id);
		for (auto& range : ranges)
		{
			ShaderCodeModule::ShaderResources::ShaderBindInfo bindInfo = {};
			bindInfo.typeSize = (uint32_t)range.range;
			bindInfo.byteOffset = (uint32_t)range.offset;
			bindInfo.variateName = compiler->get_member_name(item.base_type_id, range.index);

			//printf("\nAccessing member #  % u, offset % u, size % u", range.index, range.offset, range.range);

			result.pushConstantMembers.push_back(bindInfo);
		}
	}

    delete compiler;
	return result;
}