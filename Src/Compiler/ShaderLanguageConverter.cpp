#include <iostream>

#include <SPIRV/GlslangToSpv.h>
#include <glslang/Public/ResourceLimits.h>
#include <glslang/Public/ShaderLang.h>
// #include <glslang/Include/ResourceLimits.h>

#include <spirv_cross.hpp>
#include <spirv_glsl.hpp>
#include <spirv_hlsl.hpp>
#include <spirv_msl.hpp>
#include <spirv_parser.hpp>

#include "ShaderLanguageConverter.h"

#include <array>
#include <utility>

#ifdef WIN32
#include <atlbase.h>
#include <dxcapi.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")
#endif

namespace EmbeddedShader
{
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
            case ShaderStage::VertexShader:
                stage = EShLangVertex;
                break;
            case ShaderStage::FragmentShader:
                stage = EShLangFragment;
                break;
            case ShaderStage::ComputeShader:
                stage = EShLangCompute;
                break;
            default:
                return resultSpirvCode;
        }

        std::vector<const char *> shaderSources;
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
            // std::cout << "build Reflection Error" << std::endl;
        }
        else
        {
            // std::cout << program.getNumLiveUniformBlocks() << std::endl;
            // program.dumpReflection();
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
                    // case ShaderLanguage::ESSL:
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
                case ShaderLanguage::HLSL: {
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
        catch (const spirv_cross::CompilerError &error)
        {
            std::cout << error.what();
        }

        return resultCode;
    }

    void diagnoseIfNeeded(slang::IBlob *diagnosticsBlob)
    {
        if (diagnosticsBlob != nullptr)
        {
            std::cout << static_cast<const char *>(diagnosticsBlob->getBufferPointer()) << std::endl;
        }
    }

    std::string ShaderLanguageConverter::slangCompiler(std::string shaderCode, ShaderLanguage targetLanguage, Slang::ComPtr<slang::IComponentType>& program)
    {
        std::string result;
        Slang::ComPtr<slang::IGlobalSession> slangGlobalSession;
        slang::createGlobalSession(slangGlobalSession.writeRef());
        slang::SessionDesc sessionDesc = {};
        slang::TargetDesc targetDesc = {};
        switch (targetLanguage)
        {
            case ShaderLanguage::GLSL:
                // case ShaderLanguage::ESSL:
            {
                targetDesc.format = SLANG_GLSL;
                slangGlobalSession->findProfile("glsl_460");
                break;
            }
            case ShaderLanguage::HLSL: {
                targetDesc.format = SLANG_HLSL;
                slangGlobalSession->findProfile("sm_6_7");
                break;
            }
                // case ShaderLanguage::SpirV: {
                //     targetDesc.format = SLANG_SPIRV;
                //     slangGlobalSession->findProfile("spirv_1_6");
                //     targetDesc.flags = SLANG_TARGET_FLAG_GENERATE_SPIRV_DIRECTLY;
                //     break;
                // }
                // case ShaderLanguage::MSL:
                //	targetDesc.format = SLANG_METAL; break;
                // case ShaderLanguage::DXIL:
                //	targetDesc.format = SLANG_DXIL; break;
            default:
                return result;
                break;
        }
        sessionDesc.targets = &targetDesc;
        sessionDesc.defaultMatrixLayoutMode = SLANG_MATRIX_LAYOUT_COLUMN_MAJOR;
        sessionDesc.targetCount = 1;
        Slang::ComPtr<slang::ISession> session;
        (slangGlobalSession->createSession(sessionDesc, session.writeRef()));
        slang::IModule *slangModule = nullptr;
        {
            Slang::ComPtr<slang::IBlob> diagnosticBlob;
            // slangModule = session->loadModule(shaderCode.c_str(), diagnosticBlob.writeRef());
            slangModule = session->loadModuleFromSourceString(std::to_string(std::hash<std::string>()(shaderCode)).c_str(), "", shaderCode.c_str(), diagnosticBlob.writeRef());
        }
        Slang::ComPtr<slang::IEntryPoint> entryPoint;
        slangModule->findEntryPointByName("main", entryPoint.writeRef());
        std::vector<slang::IComponentType *> componentTypes;
        componentTypes.push_back(slangModule);
        componentTypes.push_back(entryPoint);
        Slang::ComPtr<slang::IComponentType> composedProgram;
        {
            Slang::ComPtr<slang::IBlob> diagnosticsBlob;
            SlangResult result = session->createCompositeComponentType(
                componentTypes.data(), componentTypes.size(), composedProgram.writeRef(), diagnosticsBlob.writeRef());
        }
        Slang::ComPtr<slang::IComponentType> linkedProgram;
        {
            Slang::ComPtr<slang::IBlob> diagnosticsBlob;
            SlangResult result = composedProgram->link(
                linkedProgram.writeRef(),
                diagnosticsBlob.writeRef());
            if (SLANG_FAILED(result))
                return {};
        }
        Slang::ComPtr<slang::IBlob> spirvCode;
        {
            Slang::ComPtr<slang::IBlob> diagnosticsBlob;
            SlangResult result = linkedProgram->getEntryPointCode(0, 0, spirvCode.writeRef(), diagnosticsBlob.writeRef());
            if (SLANG_FAILED(result))
                return {};
        }
        result.resize(spirvCode->getBufferSize() / sizeof(char));
        memcpy(result.data(), spirvCode->getBufferPointer(), spirvCode->getBufferSize());
        program = linkedProgram;
        return result;
    }

    size_t reflect_set = 0;
    void addParameterBlockReflection(slang::TypeLayoutReflection* type)
    {
        size_t reflect_bind = 0;
        std::cout << "pb set index: " << reflect_set << "\n";
        if (type->getSize() > 0)
        {
            std::cout << "pb ubo\n binding: " << reflect_bind++ << "\n set: " << reflect_set << "\n";
        }

        //std::cout << "pb set count: " << type->getDescriptorSetCount() << "\n";
        //for (int relativeSetIndex = 0; relativeSetIndex < type->getDescriptorSetCount(); ++relativeSetIndex)
        //{
            int relativeSetIndex = 0;
            auto rangeCount = type->getDescriptorSetDescriptorRangeCount(relativeSetIndex);
            std::cout << "pb range count: " << rangeCount << "\n";
            for (int rangeIndex = 0; rangeIndex < rangeCount; ++rangeIndex)
            {
                slang::BindingType bindingType = type->getDescriptorSetDescriptorRangeType(relativeSetIndex, rangeIndex);
                auto descriptorCount = type->getDescriptorSetDescriptorRangeDescriptorCount(relativeSetIndex, rangeIndex);
                std::cout << "\t pb descriptor count: " << descriptorCount << "\n";
                std::cout << "pb binding: " << reflect_bind++ << " binding type: \n\t";
                switch (bindingType)
                {
                case slang::BindingType::Unknown:
                    puts("Unknown");
                    break;
                case slang::BindingType::Sampler:
                    puts("Sampler");
                    break;
                case slang::BindingType::Texture:
                    puts("Texture");
                    break;
                case slang::BindingType::ConstantBuffer:
                    puts("ConstantBuffer");
                    break;
                case slang::BindingType::ParameterBlock:
                    puts("ParameterBlock");
                    break;
                case slang::BindingType::TypedBuffer:
                    puts("TypedBuffer");
                    break;
                case slang::BindingType::RawBuffer:
                    puts("RawBuffer");
                    break;
                case slang::BindingType::CombinedTextureSampler:
                    puts("CombinedTextureSampler");
                    break;
                case slang::BindingType::InputRenderTarget:
                    puts("InputRenderTarget");
                    break;
                case slang::BindingType::InlineUniformData:
                    puts("InlineUniformData");
                    break;
                case slang::BindingType::RayTracingAccelerationStructure:
                    puts("RayTracingAccelerationStructure");
                    break;
                case slang::BindingType::VaryingInput:
                    puts("VaryingInput");
                    break;
                case slang::BindingType::VaryingOutput:
                    puts("VaryingOutput");
                    break;
                case slang::BindingType::ExistentialValue:
                    puts("ExistentialValue");
                    break;
                case slang::BindingType::PushConstant:
                    puts("PushConstant");
                    break;
                case slang::BindingType::MutableFlag:
                    puts("MutableFlag");
                    break;
                case slang::BindingType::MutableTexture:
                    puts("MutableTexture");
                    break;
                case slang::BindingType::MutableTypedBuffer:
                    puts("MutableTypedBuffer");
                    break;
                case slang::BindingType::MutableRawBuffer:
                    puts("MutableRawBuffer");
                    break;
                case slang::BindingType::BaseMask:
                    puts("BaseMask");
                    break;
                case slang::BindingType::ExtMask:
                    puts("ExtMask");
                    break;
                }
            }
        //}
    }

    std::vector<ShaderCodeModule::ShaderResources> ShaderLanguageConverter::slangCompiler(const std::string &shaderCode,
                                                                                          const std::vector<ShaderLanguage> &targetBinary, const std::vector<ShaderLanguage> &targetLanguage, std::vector<std::vector<uint32_t>> &binaryTargetsOutput,
                                                                                          std::vector<std::string> &targetsOutput, bool isEnabledReflection)
    {
        if (targetBinary.empty() && targetLanguage.empty())
        {
            throw std::logic_error("No target language specified for Slang compilation.");
        }
        Slang::ComPtr<slang::IGlobalSession> globalSession;
        createGlobalSession(globalSession.writeRef());

        slang::SessionDesc sessionDesc = {};

        std::vector<slang::TargetDesc> targets(targetLanguage.size() + targetBinary.size());

        for (size_t i = 0; i < targetBinary.size(); ++i)
        {
            auto& target = targets[i];
            auto language = targetBinary[i];
            switch (language)
            {
            case ShaderLanguage::SpirV:
                target.format = SLANG_SPIRV;
                target.flags = SLANG_TARGET_FLAG_GENERATE_SPIRV_DIRECTLY;
            case ShaderLanguage::DXIL:
                target.format = SLANG_DXIL;
                target.profile = globalSession->findProfile("sm_6_0");
                break;
            case ShaderLanguage::DXBC:
                target.format = SLANG_DXBC;
                break;
            default:
                throw std::logic_error("Unsupported binary target for Slang compilation.");
            }
        }

        for (size_t i = 0; i < targetLanguage.size(); ++i)
        {
            auto& target = targets[i + targetBinary.size()];
            auto language = targetLanguage[i];
            switch (language)
            {
                case ShaderLanguage::GLSL:
                    // case ShaderLanguage::ESSL:
                {
                    target.format = SLANG_GLSL;
                    break;
                }
                case ShaderLanguage::HLSL: {
                    target.format = SLANG_HLSL;
                    break;
                }
                // case ShaderLanguage::MSL:
                //	targetDesc.format = SLANG_METAL; break;
                case ShaderLanguage::DXIL:
                    target.format = SLANG_DXIL;
                    break;
                case ShaderLanguage::DXBC:
                    target.format = SLANG_DXBC;
                    break;
                default:
                    throw std::logic_error("Unsupported target language for Slang compilation.");
            }
        }

        sessionDesc.defaultMatrixLayoutMode = SLANG_MATRIX_LAYOUT_COLUMN_MAJOR;
        sessionDesc.targets = targets.data();
        sessionDesc.targetCount = static_cast<SlangInt>(targets.size());

        std::array options =
            {
            slang::CompilerOptionEntry{
                slang::CompilerOptionName::EmitSpirvDirectly,
                {slang::CompilerOptionValueKind::Int, 1, 0, nullptr, nullptr}},
            slang::CompilerOptionEntry{
                slang::CompilerOptionName::BindlessSpaceIndex,
                {slang::CompilerOptionValueKind::Int, 1, 0, nullptr, nullptr}}};
        sessionDesc.compilerOptionEntries = options.data();
        sessionDesc.compilerOptionEntryCount = options.size();

        Slang::ComPtr<slang::ISession> session;
        globalSession->createSession(sessionDesc, session.writeRef());

        // 3. Load module
        Slang::ComPtr<slang::IModule> slangModule;
        {
            auto hashStr = std::to_string(std::hash<std::string>()(shaderCode));
            Slang::ComPtr<slang::IBlob> diagnosticsBlob;
            slangModule = session->loadModuleFromSourceString(hashStr.c_str(), (hashStr + ".slang").c_str(), shaderCode.c_str(), diagnosticsBlob.writeRef()); // Optional diagnostic container
            diagnoseIfNeeded(diagnosticsBlob);
            if (!slangModule)
            {
                throw std::runtime_error("Failed to load Slang module.");
            }
        }

        // 4. Query Entry Points
        Slang::ComPtr<slang::IEntryPoint> entryPoint;
        {
            Slang::ComPtr<slang::IBlob> diagnosticsBlob;
            slangModule->findEntryPointByName("main", entryPoint.writeRef());
            if (!entryPoint)
            {
                std::cout << "Error getting entry point" << std::endl;
                throw std::runtime_error("Failed to find entry point 'main' in Slang module.");
            }
        }

        // 5. Compose Modules + Entry Points
        std::array<slang::IComponentType *, 2> componentTypes =
            {
            slangModule,
            entryPoint};

        Slang::ComPtr<slang::IComponentType> composedProgram;
        {
            Slang::ComPtr<slang::IBlob> diagnosticsBlob;
            SlangResult result = session->createCompositeComponentType(
                componentTypes.data(),
                componentTypes.size(),
                composedProgram.writeRef(),
                diagnosticsBlob.writeRef());
            diagnoseIfNeeded(diagnosticsBlob);
            if (SLANG_FAILED(result))
                throw std::runtime_error("Failed to create composite component type in Slang.");
        }

        // 6. Link
        Slang::ComPtr<slang::IComponentType> linkedProgram;
        {
            Slang::ComPtr<slang::IBlob> diagnosticsBlob;
            SlangResult result = composedProgram->link(
                linkedProgram.writeRef(),
                diagnosticsBlob.writeRef());
            diagnoseIfNeeded(diagnosticsBlob);
            if (SLANG_FAILED(result))
                throw std::runtime_error("Failed to link Slang program.");
        }

        binaryTargetsOutput.resize(targetLanguage.size());
        for (size_t i = 0; i < binaryTargetsOutput.size(); ++i)
        {
            Slang::ComPtr<slang::IBlob> targetCodeBlob;
            Slang::ComPtr<slang::IBlob> diagnosticsBlob;
            SlangResult result = linkedProgram->getEntryPointCode(
                0,
                static_cast<SlangInt>(i),
                targetCodeBlob.writeRef(),
                diagnosticsBlob.writeRef());
            diagnoseIfNeeded(diagnosticsBlob);
            if (SLANG_FAILED(result))
                throw std::runtime_error("Failed to get target code from Slang program.");
            if (targetCodeBlob)
            {
                binaryTargetsOutput[i].resize(targetCodeBlob->getBufferSize() / sizeof(uint32_t));
                memcpy(binaryTargetsOutput[i].data(), targetCodeBlob->getBufferPointer(), targetCodeBlob->getBufferSize());
            }
        }

        targetsOutput.resize(targetLanguage.size());
        for (size_t i = 0; i < targetsOutput.size(); ++i)
        {
            Slang::ComPtr<slang::IBlob> targetCodeBlob;
            Slang::ComPtr<slang::IBlob> diagnosticsBlob;
            SlangResult result = linkedProgram->getEntryPointCode(
                0,
                static_cast<SlangInt>(i + targetBinary.size()), // Skip the first entry point if there are binary targets
                targetCodeBlob.writeRef(),
                diagnosticsBlob.writeRef());
            diagnoseIfNeeded(diagnosticsBlob);
            if (SLANG_FAILED(result))
                throw std::runtime_error("Failed to get target code from Slang program.");
            if (targetCodeBlob)
            {
                targetsOutput[i].resize(targetCodeBlob->getBufferSize() / sizeof(char));
                memcpy(targetsOutput[i].data(), targetCodeBlob->getBufferPointer(), targetCodeBlob->getBufferSize());
            }
        }

        if (!isEnabledReflection)
            return {};

        std::vector<ShaderCodeModule::ShaderResources> reflectedResources(targets.size());
        for (size_t i = 0; i < targets.size(); ++i)
        {
            auto& reflection = reflectedResources[i];
            auto programLayout = composedProgram->getLayout(static_cast<SlangInt>(i));
            // auto globalLayout = programLayout->getGlobalParamsVarLayout();
            // if (globalLayout->getCategory() == slang::ParameterCategory::PushConstantBuffer)
            // {
            //     reflection.pushConstantSize = globalLayout->getTypeLayout()->getSize();
            //     reflection.pushConstantName = globalLayout->getName();
            // }
            //
            // auto entryPointLayout = programLayout->getEntryPointByIndex(0);
            // auto varLayout = entryPointLayout->getVarLayout();
            // auto typeLayout = varLayout->getTypeLayout();
            // switch (typeLayout->getKind())
            // {
            //     case slang::TypeReflection::Kind::ConstantBuffer:
            //         reflection.bindInfoPool[typeLayout->getName()] = ShaderCodeModule::ShaderResources::ShaderBindInfo{
            //             varLayout->getBindingSpace(),
            //             varLayout->getBindingIndex(),
            //             varLayout->getBindingIndex(),
            //             varLayout->getName(),
            //             typeLayout->getName(),
            //             ShaderCodeModule::ShaderResources::BindType::uniformBuffers};
            //         break;
            //     case slang::TypeReflection::Kind::SamplerState:
            //         break;
            //     case slang::TypeReflection::Kind::TextureBuffer:
            //         break;
            //     case slang::TypeReflection::Kind::ShaderStorageBuffer:
            //         break;
            //     default:break;
            // }

            // auto entryPointLayout = programLayout->getEntryPointByIndex(0);
            // for (int ii = 0; ii < entryPointLayout->getParameterCount(); ++ii)
            // {
            //     slangReflectAddBindInfo(entryPointLayout->getParameterByIndex(ii),reflection,"");
            // }

            std::cout << "begin reflect...\n";
            //std::cout << "begin global reflect...\n";
            //addParameterBlockReflection(programLayout->getGlobalParamsTypeLayout());
            //std::cout << "begin entry point reflect...\n";
            // addParameterBlockReflection(programLayout->getEntryPointByIndex(0)->getTypeLayout());
            for (int ii = 0; ii < programLayout->getParameterCount(); ++ii)
            {
                reflect_set = ii;
                 addParameterBlockReflection(programLayout->getParameterByIndex(ii)->getTypeLayout()->getElementTypeLayout());
            }
            std::cout << "end reflect...\n\n";
        }
        return reflectedResources;
    }

    std::vector<uint32_t> ShaderLanguageConverter::slangSpirvCompiler(const std::string &shaderCode, Slang::ComPtr<slang::IComponentType>& program)
    {
        std::vector<uint32_t> result;
        // 1. Create Global Session
        Slang::ComPtr<slang::IGlobalSession> globalSession;
        createGlobalSession(globalSession.writeRef());

        // 2. Create Session
        slang::SessionDesc sessionDesc = {};
        slang::TargetDesc targetDesc = {};
        targetDesc.format = SLANG_SPIRV;
        // targetDesc.profile = globalSession->findProfile("spirv_1_6");
        targetDesc.flags = SLANG_TARGET_FLAG_GENERATE_SPIRV_DIRECTLY;

        sessionDesc.defaultMatrixLayoutMode = SLANG_MATRIX_LAYOUT_COLUMN_MAJOR;
        sessionDesc.targets = &targetDesc;
        sessionDesc.targetCount = 1;

        std::array options =
            {
            slang::CompilerOptionEntry{
                slang::CompilerOptionName::EmitSpirvDirectly,
                {slang::CompilerOptionValueKind::Int, 1, 0, nullptr, nullptr}},
            slang::CompilerOptionEntry{
                slang::CompilerOptionName::BindlessSpaceIndex,
                {slang::CompilerOptionValueKind::Int, 1, 0, nullptr, nullptr}}};
        sessionDesc.compilerOptionEntries = options.data();
        sessionDesc.compilerOptionEntryCount = options.size();

        Slang::ComPtr<slang::ISession> session;
        globalSession->createSession(sessionDesc, session.writeRef());

        // 3. Load module
        Slang::ComPtr<slang::IModule> slangModule;
        {
            auto hashStr = std::to_string(std::hash<std::string>()(shaderCode));
            Slang::ComPtr<slang::IBlob> diagnosticsBlob;
            slangModule = session->loadModuleFromSourceString(hashStr.c_str(), (hashStr + ".slang").c_str(), shaderCode.c_str(), diagnosticsBlob.writeRef()); // Optional diagnostic container
            diagnoseIfNeeded(diagnosticsBlob);
            if (!slangModule)
            {
                return {};
            }
        }

        // 4. Query Entry Points
        Slang::ComPtr<slang::IEntryPoint> entryPoint;
        {
            Slang::ComPtr<slang::IBlob> diagnosticsBlob;
            slangModule->findEntryPointByName("main", entryPoint.writeRef());
            if (!entryPoint)
            {
                std::cout << "Error getting entry point" << std::endl;
                return {};
            }
        }

        // 5. Compose Modules + Entry Points
        std::array<slang::IComponentType *, 2> componentTypes =
            {
            slangModule,
            entryPoint};

        Slang::ComPtr<slang::IComponentType> composedProgram;
        {
            Slang::ComPtr<slang::IBlob> diagnosticsBlob;
            SlangResult result = session->createCompositeComponentType(
                componentTypes.data(),
                componentTypes.size(),
                composedProgram.writeRef(),
                diagnosticsBlob.writeRef());
            diagnoseIfNeeded(diagnosticsBlob);
            if (SLANG_FAILED(result))
                return {};
        }

        // 6. Link
        Slang::ComPtr<slang::IComponentType> linkedProgram;
        {
            Slang::ComPtr<slang::IBlob> diagnosticsBlob;
            SlangResult result = composedProgram->link(
                linkedProgram.writeRef(),
                diagnosticsBlob.writeRef());
            diagnoseIfNeeded(diagnosticsBlob);
            if (SLANG_FAILED(result))
                return {};
        }

        // 7. Get Target Kernel Code
        Slang::ComPtr<slang::IBlob> spirvCode;
        {
            Slang::ComPtr<slang::IBlob> diagnosticsBlob;
            SlangResult result = linkedProgram->getEntryPointCode(
                0,
                0,
                spirvCode.writeRef(),
                diagnosticsBlob.writeRef());
            diagnoseIfNeeded(diagnosticsBlob);
            if (SLANG_FAILED(result))
                return {};
        }
        result.resize(spirvCode->getBufferSize() / sizeof(uint32_t));
        memcpy(result.data(), spirvCode->getBufferPointer(), spirvCode->getBufferSize());
        program = linkedProgram;
        return result;
    }
#ifdef WIN32
    std::vector<uint32_t> ShaderLanguageConverter::dxilCompiler(const std::string& hlslShader, ShaderStage stage)
    {
        CComPtr<IDxcUtils> pUtils;
        CComPtr<IDxcCompiler3> pCompiler;
        DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&pUtils));
        DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&pCompiler));

        std::wstring_view targetName;
        switch (stage)
        {
            case ShaderStage::VertexShader:
                targetName = L"vs_6_6";
                break;
            case ShaderStage::FragmentShader:
                targetName = L"ps_6_6";
                break;
            case ShaderStage::ComputeShader:
                targetName = L"cs_6_6";
                break;
            default:
                throw std::runtime_error("Unknown shader stage");
        }
        LPCWSTR args[] =
        {
            L"Helicon",                  // Optional shader source file name for error reporting
                                         // and for PIX shader source view.
            L"-E", L"main",              // Entry point.
            L"-T", targetName.data(),    // Target.
    #ifdef CABBAGE_ENGINE_DEBUG
            L"-Zs",                      // Enable debug information (slim format)
    #endif
        };

        //
        // Open source file.
        //
        CComPtr<IDxcBlobEncoding> pSource = nullptr;
        pUtils->CreateBlob(hlslShader.data(), hlslShader.size() * sizeof(char), DXC_CP_ACP, &pSource);
        DxcBuffer Source;
        Source.Ptr = pSource->GetBufferPointer();
        Source.Size = pSource->GetBufferSize();
        Source.Encoding = DXC_CP_ACP; // Assume BOM says UTF8 or UTF16 or this is ANSI text.

        //
        // Compile it with specified arguments.
        //
        CComPtr<IDxcResult> pResults;
        pCompiler->Compile(
            &Source,                                   // Source buffer.
            args,                                      // Array of pointers to arguments.
            std::size(args),                           // Number of arguments.
            nullptr,                                   // User-provided interface to handle #include directives (optional).
            IID_PPV_ARGS(&pResults)                    // Compiler output status, buffer, and errors.
        );

        //
        // Print errors if present.
        //
        CComPtr<IDxcBlobUtf8> pErrors = nullptr;
        pResults->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&pErrors), nullptr);
        // Note that d3dcompiler would return null if no errors or warnings are present.
        // IDxcCompiler3::Compile will always return an error buffer, but its length
        // will be zero if there are no warnings or errors.
        if (pErrors != nullptr && pErrors->GetStringLength() != 0)
            wprintf(L"DXC Warnings and Errors:\n%S\n", pErrors->GetStringPointer());

        HRESULT hrStatus;
        pResults->GetStatus(&hrStatus);
        if (FAILED(hrStatus))
            throw std::runtime_error("Dxc Compilation Failed");

        CComPtr<IDxcBlob> pShader = nullptr;
        CComPtr<IDxcBlobUtf16> pShaderName = nullptr;
        pResults->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&pShader), &pShaderName);
        if (!pShader)
            throw std::runtime_error("Dxc Compilation Failed");

        std::vector<uint32_t> result(pShader->GetBufferSize() / sizeof(uint32_t));
        memcpy(result.data(), pShader->GetBufferPointer(), pShader->GetBufferSize());
        return result;
    }

    std::vector<uint32_t> ShaderLanguageConverter::dxbcCompiler(const std::string& hlslShader, ShaderStage stage)
    {
        UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef CABBAGE_ENGINE_DEBUG
        flags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_ENABLE_UNBOUNDED_DESCRIPTOR_TABLES;
#endif

        std::string_view targetName;
        switch (stage)
        {
            case ShaderStage::VertexShader:
                targetName = "vs_5_1";
                break;
            case ShaderStage::FragmentShader:
                targetName = "ps_5_1";
                break;
            case ShaderStage::ComputeShader:
                targetName = "cs_5_1";
                break;
            default:
                throw std::runtime_error("Unknown shader stage");
        }

        CComPtr<ID3DBlob> code;
        CComPtr<ID3DBlob> error;
        D3DCompile(hlslShader.data(), hlslShader.size() * sizeof(char),"Helicon",nullptr,nullptr,"main",targetName.data(),
                   flags, 0, &code, &error);
        if (error && error->GetBufferSize() != 0)
        {
            printf("D3DCompiler Warnings and Errors:\n%s\n", static_cast<const char*>(error->GetBufferPointer()));
            throw std::runtime_error("D3DCompiler Compilation Failed");
        }

        std::vector<uint32_t> result(code->GetBufferSize() / sizeof(uint32_t));
        memcpy(result.data(), code->GetBufferPointer(), code->GetBufferSize());
        return result;
    }
#endif

    // get Reflected Bind Info
    ShaderCodeModule::ShaderResources ShaderLanguageConverter::spirvCrossReflectedBindInfo(std::vector<uint32_t> spirv_file, ShaderLanguage targetLanguage, int32_t targetVersion)
    {
        ShaderCodeModule::ShaderResources result = {};
        spirv_cross::ShaderResources res{};

        spirv_cross::CompilerGLSL *compiler{};
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
                // opts.es = (targetLanguage == ShaderLanguage::ESSL);
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
            default:
                throw std::runtime_error("unsupported shader language");
        }

        for (auto &item : res.uniform_buffers)
        {
            ShaderCodeModule::ShaderResources::ShaderBindInfo bindInfo = {};

            bindInfo.variateName = item.name;
            bindInfo.typeName = "uniform";
            bindInfo.elementCount = compiler->get_type((uint64_t)item.base_type_id).member_types.size();
            bindInfo.typeSize = (uint32_t)compiler->get_declared_struct_size(compiler->get_type(item.base_type_id));

            bindInfo.set = compiler->get_decoration(item.id, spv::DecorationDescriptorSet);
            bindInfo.binding = compiler->get_decoration(item.id, spv::DecorationBinding);
            bindInfo.location = compiler->get_decoration(item.id, spv::DecorationLocation);

            bindInfo.bindType = ShaderCodeModule::ShaderResources ::uniformBuffers;
            // result.bindInfoPool.push_back(bindInfo);
            result.bindInfoPool.insert(std::pair<std::string, ShaderCodeModule::ShaderResources::ShaderBindInfo>(bindInfo.variateName, bindInfo));
        }

        for (auto &item : res.sampled_images)
        {
            ShaderCodeModule::ShaderResources::ShaderBindInfo bindInfo = {};

            bindInfo.typeName = "sampler2D";
            bindInfo.variateName = item.name;

            bindInfo.set = compiler->get_decoration(item.id, spv::DecorationDescriptorSet);
            bindInfo.binding = compiler->get_decoration(item.id, spv::DecorationBinding);
            bindInfo.location = compiler->get_decoration(item.id, spv::DecorationLocation);

            bindInfo.bindType = ShaderCodeModule::ShaderResources ::sampledImages;

            // result.bindInfoPool.push_back(bindInfo);
            result.bindInfoPool.insert(std::pair<std::string, ShaderCodeModule::ShaderResources::ShaderBindInfo>(bindInfo.variateName, bindInfo));
        }

        for (auto &item : res.stage_inputs)
        {
            ShaderCodeModule::ShaderResources::ShaderBindInfo bindInfo = {};

            bindInfo.variateName = item.name;

            const spirv_cross::SPIRType &base_type = compiler->get_type(item.base_type_id);
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

            bindInfo.bindType = ShaderCodeModule::ShaderResources ::stageInputs;

            result.bindInfoPool.insert(std::pair<std::string, ShaderCodeModule::ShaderResources::ShaderBindInfo>(bindInfo.variateName, bindInfo));
        }

        for (auto &item : res.stage_outputs)
        {
            ShaderCodeModule::ShaderResources::ShaderBindInfo bindInfo = {};

            bindInfo.variateName = item.name;

            const spirv_cross::SPIRType &base_type = compiler->get_type(item.base_type_id);
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

            bindInfo.bindType = ShaderCodeModule::ShaderResources ::stageOutputs;

            result.bindInfoPool.insert(std::pair<std::string, ShaderCodeModule::ShaderResources::ShaderBindInfo>(bindInfo.variateName, bindInfo));
        }

        for (auto &item : res.push_constant_buffers)
        {
            result.pushConstantName = item.name;
            result.pushConstantSize = (uint32_t)compiler->get_declared_struct_size(compiler->get_type((uint64_t)item.base_type_id));

            // obtain all the push constant member
            spirv_cross::SmallVector<spirv_cross::BufferRange> ranges = compiler->get_active_buffer_ranges(item.id);
            for (auto &range : ranges)
            {
                ShaderCodeModule::ShaderResources::ShaderBindInfo bindInfo = {};
                bindInfo.typeSize = (uint32_t)range.range;
                bindInfo.byteOffset = (uint32_t)range.offset;
                bindInfo.variateName = compiler->get_member_name(item.base_type_id, range.index);

                bindInfo.bindType = ShaderCodeModule::ShaderResources ::pushConstantMembers;

                result.bindInfoPool.insert(std::pair<std::string, ShaderCodeModule::ShaderResources::ShaderBindInfo>(result.pushConstantName + "." + bindInfo.variateName, bindInfo));
            }
        }

        delete compiler;
        return result;
    }

    void ShaderLanguageConverter::slangReflectAddBindInfo(slang::VariableLayoutReflection* var,
                                                          ShaderCodeModule::ShaderResources& shaderResources, const std::string& parentPrefix)
    {
        slang::TypeLayoutReflection* type = var->getTypeLayout();
        auto name = var->getName();

        std::string fullName = parentPrefix.empty() ? name :
                           parentPrefix + "." + name;

        if (type->getKind() == slang::TypeReflection::Kind::ConstantBuffer ||
        type->getKind() == slang::TypeReflection::Kind::ParameterBlock)
        {
            ShaderCodeModule::ShaderResources::ShaderBindInfo info {};
            info.variateName = name;
            info.typeName    = "uniform";
            info.set         = static_cast<uint32_t>(var->getBindingSpace(SLANG_PARAMETER_CATEGORY_DESCRIPTOR_TABLE_SLOT));
            info.binding     = var->getBindingIndex();
            info.location    = var->getBindingIndex();
            info.bindType    = ShaderCodeModule::ShaderResources::uniformBuffers;
            info.elementCount= type->getFieldCount();
            info.typeSize    = static_cast<uint32_t>(type->getSize(SLANG_PARAMETER_CATEGORY_UNIFORM));

            shaderResources.bindInfoPool[fullName] = info;

            // 继续展开内部字段（如果关心成员）
            for (uint32_t f = 0; f < type->getFieldCount(); ++f)
                slangReflectAddBindInfo(type->getFieldByIndex(f), shaderResources, fullName);
            return;
        }

        // 2. push constant buffer
        if (var->getCategory() == SLANG_PARAMETER_CATEGORY_PUSH_CONSTANT_BUFFER)
        {
            shaderResources.pushConstantName = name;
            shaderResources.pushConstantSize = (uint32_t)type->getSize(SLANG_PARAMETER_CATEGORY_PUSH_CONSTANT_BUFFER);

            for (uint32_t f = 0; f < type->getFieldCount(); ++f)
            {
                auto* field = type->getFieldByIndex(f);
                ShaderCodeModule::ShaderResources::ShaderBindInfo info {};
                info.variateName = field->getName();
                info.typeName    = field->getTypeLayout()->getName();
                info.byteOffset  = static_cast<uint32_t>(field->getOffset(SLANG_PARAMETER_CATEGORY_UNIFORM));
                info.typeSize    = static_cast<uint32_t>(field->getTypeLayout()->getSize(SLANG_PARAMETER_CATEGORY_UNIFORM));
                info.bindType    = ShaderCodeModule::ShaderResources::pushConstantMembers;

                shaderResources.bindInfoPool[shaderResources.pushConstantName + "." + info.variateName] = info;
            }
            return;
        }
        // 3. texture / sampler
        if (type->getKind() == slang::TypeReflection::Kind::Resource &&
            type->getResourceShape() == SLANG_TEXTURE_BUFFER)
        {
            ShaderCodeModule::ShaderResources::ShaderBindInfo info {};
            info.variateName = name;
            info.typeName    = "sampler2D";
            info.set         = static_cast<uint32_t>(var->getBindingSpace(SLANG_PARAMETER_CATEGORY_DESCRIPTOR_TABLE_SLOT));
            info.binding     = var->getBindingIndex();
            info.location    = info.binding;
            info.bindType    = ShaderCodeModule::ShaderResources::sampledImages;

            shaderResources.bindInfoPool[fullName] = info;
            return;
        }

        // 4. stage inputs
        if (var->getCategory() == SLANG_PARAMETER_CATEGORY_VARYING_INPUT)
        {
            ShaderCodeModule::ShaderResources::ShaderBindInfo info {};
            info.variateName = name;
            info.typeName    = type->getName();
            info.location    = var->getBindingIndex();
            info.elementCount= type->getFieldCount();
            info.typeSize    = type->getSize();
            info.bindType    = ShaderCodeModule::ShaderResources::stageInputs;

            shaderResources.bindInfoPool[fullName] = info;
            return;
        }

        // 5. stage outputs
        if (var->getCategory() == SLANG_PARAMETER_CATEGORY_VARYING_OUTPUT)
        {
            ShaderCodeModule::ShaderResources::ShaderBindInfo info {};
            info.variateName = name;
            info.typeName    = type->getName();
            info.location    = var->getBindingIndex();
            info.elementCount= type->getFieldCount();
            info.typeSize    = type->getSize();
            info.bindType    = ShaderCodeModule::ShaderResources::stageOutputs;

            shaderResources.bindInfoPool[fullName] = info;
        }
    }
}
