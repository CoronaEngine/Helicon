file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})
add_library(Helicon STATIC ${SOURCE_FILES})

set_target_properties(Helicon PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/$<CONFIG>
)

target_compile_definitions(Helicon PUBLIC
    HELICON_ROOT_PATH="${PROJECT_SOURCE_DIR}"
)

target_include_directories(Helicon PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/Env/ktm"
    "${PROJECT_SOURCE_DIR}/Env/pfr/include"
    "${PROJECT_SOURCE_DIR}/Env/preprocessor/include"
    "${PROJECT_SOURCE_DIR}/Env/glslang"
    "${PROJECT_SOURCE_DIR}/Env/SPIRV-Cross"
    "${PROJECT_SOURCE_DIR}/Env/slang/include"
    "${PROJECT_SOURCE_DIR}/Env/dxc/inc"
)

# --- 1. 架构检测 ---
if(MSVC)
    message(STATUS "MSVC detected")
    if(DEFINED CMAKE_VS_PLATFORM_NAME)
        set(TARGET_ARCH ${CMAKE_VS_PLATFORM_NAME})
    else()
        # 如果VS平台名称未定义，使用指针大小判断
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            set(TARGET_ARCH "x64")
        else()
            set(TARGET_ARCH "x86")
        endif()
    endif()

    if(TARGET_ARCH STREQUAL "Win32")
        set(TARGET_ARCH "x86")
    endif()
else()
    # 为非 MSVC 编译器规范化架构名称
    string(TOLOWER "${CMAKE_SYSTEM_PROCESSOR}" TARGET_ARCH)

    if(TARGET_ARCH STREQUAL "amd64" OR TARGET_ARCH STREQUAL "x86_64")
        set(TARGET_ARCH "x64")
    elseif(TARGET_ARCH STREQUAL "aarch64")
        set(TARGET_ARCH "arm64")
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4 AND(TARGET_ARCH STREQUAL "x86" OR TARGET_ARCH STREQUAL "i386"))
        set(TARGET_ARCH "x86")
    endif()
endif()

message(STATUS "Target Arch: ${TARGET_ARCH}")

target_link_directories(Helicon PUBLIC
    ${PROJECT_SOURCE_DIR}/Env/slang/lib
    ${PROJECT_SOURCE_DIR}/Env/dxc/lib/${TARGET_ARCH}
)

target_link_libraries(Helicon PUBLIC
    glslang
    glslang-default-resource-limits
    spirv-cross-core
    spirv-cross-c
    spirv-cross-cpp
    spirv-cross-util
    slang
    slang-rt
    gfx
    dxcompiler
    dxil
)

file(GLOB SLANG_DLLS "${PROJECT_SOURCE_DIR}/Env/slang/bin/*.dll")
file(GLOB DXC_DLLS "${PROJECT_SOURCE_DIR}/Env/dxc/bin/${TARGET_ARCH}/*.dll")

if(SLANG_DLLS)
    message(STATUS "Found Slang DLLs: ${SLANG_DLLS}")

    add_custom_command(
        TARGET Helicon POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SLANG_DLLS} # 源文件列表
        ${HELICON_BINARY_DIR}/bin/$<CONFIG> # 目标目录
        COMMENT "Copying Slang DLLs to the output directory"
        VERBATIM
    )
endif()

if(DXC_DLLS)
    message(STATUS "Found DXC DLLs: ${DXC_DLLS}")

    add_custom_command(
        TARGET Helicon POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${DXC_DLLS} # 源文件列表
        ${HELICON_BINARY_DIR}/bin/$<CONFIG> # 目标目录
        COMMENT "Copying DXC DLLs to the output directory"
        VERBATIM
    )
endif()