# ============================= Helicon CMake 配置 =============================
cmake_minimum_required(VERSION 4.0)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(
    Helicon
    VERSION 0.5.0
    HOMEPAGE_URL "https://github.com/CoronaEngine/Helicon"
    LANGUAGES C CXX
)

function(helicon_install_runtime_deps target_name)
    # 从 Helicon 库获取它声明的依赖列表
    get_target_property(HELICON_DEPS Helicon INTERFACE_HELICON_RUNTIME_DEPS)

    if(NOT HELICON_DEPS)
        message(WARNING "Helicon library did not specify any runtime dependencies.")
        return()
    endif()

    message(STATUS "Scheduling runtime dependencies for ${target_name}: ${HELICON_DEPS}")

    # 使用生成器表达式 $<TARGET_FILE_DIR:...> 来获取目标在构建时的实际输出目录
    # 这能完美处理 Debug/Release 等不同配置
    set(DESTINATION_DIR "$<TARGET_FILE_DIR:${target_name}>")

    add_custom_command(
        TARGET ${target_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${HELICON_DEPS}
        "${DESTINATION_DIR}"
        COMMENT "Copying Helicon runtime dependencies to ${target_name} output directory"
        VERBATIM
    )
endfunction()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# 是否构建示例
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    option(HELICON_BUILD_EXAMPLES "是否构建 Helicon 示例" ON)
else()
    option(HELICON_BUILD_EXAMPLES "是否构建 Helicon 示例" OFF)
endif()

add_compile_definitions(
    $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>
    NOMINMAX

    $<$<CONFIG:Debug>:CABBAGE_ENGINE_DEBUG>
    $<$<CONFIG:RelWithDebInfo>:CABBAGE_ENGINE_DEBUG>
    $<$<CONFIG:Release>:CABBAGE_ENGINE_RELEASE>
    $<$<CONFIG:MinSizeRel>:CABBAGE_ENGINE_RELEASE>
)

include(FetchContent)

FetchContent_Declare(
    pfr
    GIT_REPOSITORY https://github.com/boostorg/pfr.git
    GIT_TAG develop
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(pfr)

FetchContent_Declare(
    ktm
    GIT_REPOSITORY https://github.com/YGXXD/ktm.git
    GIT_TAG main
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(ktm)

FetchContent_Declare(
    preprocessor
    GIT_REPOSITORY https://github.com/boostorg/preprocessor.git
    GIT_TAG develop
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(preprocessor)

FetchContent_Declare(
    glslang
    GIT_REPOSITORY https://github.com/KhronosGroup/glslang.git
    GIT_TAG main
    EXCLUDE_FROM_ALL
)
set(ENABLE_OPT OFF)
set(ENABLE_GLSLANG_BINARIES OFF)
FetchContent_MakeAvailable(glslang)

FetchContent_Declare(
    SPIRV-Cross
    GIT_REPOSITORY https://github.com/KhronosGroup/SPIRV-Cross.git
    GIT_TAG main
    EXCLUDE_FROM_ALL
)
set(SPIRV_CROSS_SHARED OFF)
set(SPIRV_CROSS_STATIC ON)
set(SPIRV_CROSS_ENABLE_TESTS OFF)
set(SPIRV_CROSS_CLI OFF)
FetchContent_MakeAvailable(SPIRV-Cross)

FetchContent_Declare(
    SPIRV-Headers
    GIT_REPOSITORY https://github.com/KhronosGroup/SPIRV-Headers.git
    GIT_TAG vulkan-sdk-1.4.335.0
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(SPIRV-Headers)

FetchContent_Declare(
    SPIRV-Tools
    GIT_REPOSITORY https://github.com/KhronosGroup/SPIRV-Tools.git
    GIT_TAG vulkan-sdk-1.4.335.0
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(SPIRV-Tools)

# 修复 SPIRV-Tools 在 C++20 下的运算符重写警告 (C5232)
if(MSVC)
    target_compile_options(SPIRV-Tools-opt PRIVATE /Wv:18)
    target_compile_options(SPIRV-Tools-opt PRIVATE /wd4717 /wd5232)
endif()

# ============================================================================
# Shader 自动编译模块
# ============================================================================
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/HeliconShaderCompile.cmake)

add_subdirectory(Src)
add_subdirectory(Scripts)

if(HELICON_BUILD_EXAMPLES)
    add_subdirectory(Examples)
endif()