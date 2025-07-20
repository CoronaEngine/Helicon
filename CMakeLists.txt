# ============================= Helicon CMake 配置 =============================
cmake_minimum_required(VERSION 4.0)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(
    Helicon
    VERSION 0.5.0
    HOMEPAGE_URL "https://github.com/CoronaEngine/Helicon"
    LANGUAGES C CXX
)

# 是否构建示例
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    option(HELICON_BUILD_EXAMPLES "是否构建 Helicon 示例" ON)
else()
    option(HELICON_BUILD_EXAMPLES "是否构建 Helicon 示例" OFF)
endif()

# Slang DLL路径配置
set(SLANG_DLL_DIR "" CACHE PATH "Slang DLL文件的目录路径")

add_compile_definitions(
    $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>
    NOMINMAX
)

set(BUILD_SHARED_LIBS OFF)

# 依赖库
add_subdirectory(Env/pfr EXCLUDE_FROM_ALL)
add_subdirectory(Env/ktm EXCLUDE_FROM_ALL)
add_subdirectory(Env/preprocessor EXCLUDE_FROM_ALL)

set(ENABLE_OPT OFF)
set(ENABLE_GLSLANG_BINARIES OFF)
add_subdirectory(Env/glslang EXCLUDE_FROM_ALL)

set(SPIRV_CROSS_SHARED OFF)
set(SPIRV_CROSS_STATIC ON)
set(SPIRV_CROSS_ENABLE_TESTS OFF)
set(SPIRV_CROSS_CLI OFF)
add_subdirectory(Env/SPIRV-Cross EXCLUDE_FROM_ALL)

add_subdirectory(Src)

if(HELICON_BUILD_EXAMPLES)
    add_subdirectory(Examples)
endif()