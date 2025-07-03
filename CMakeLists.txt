# ============================= Helicon CMake 配置 =============================
cmake_minimum_required(VERSION 4.0)
set(CMAKE_POLICY_VERSION_MINIMUM "4.0")

# 项目信息
project(
    Helicon
    VERSION 0.5.0
    HOMEPAGE_URL "https://github.com/CoronaEngine/Helicon"
    LANGUAGES C CXX
)

# ----------------------------------------------------------------------------
# 全局属性与策略
# ----------------------------------------------------------------------------
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW) # 使 option() 支持目录作用域
    message(STATUS "[Helicon] 启用策略 CMP0077 (option() 支持目录作用域)")
endif()

# ----------------------------------------------------------------------------
# 根目录判定与日志输出
# ----------------------------------------------------------------------------
set(IS_ROOT_DIR FALSE)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(IS_ROOT_DIR TRUE)
    message(STATUS "[Helicon] 当前为项目根目录: ${CMAKE_CURRENT_SOURCE_DIR}")
else()
    message(STATUS "[Helicon] 当前为子目录: ${CMAKE_CURRENT_SOURCE_DIR}")
endif()

# ----------------------------------------------------------------------------
# 检查是否使用 CMake 预设配置
# ----------------------------------------------------------------------------
if(NOT USED_PRESET_CONFIG)
    message(FATAL_ERROR "[Helicon] 必须使用 CMake 预设配置 (USED_PRESET_CONFIG)！")
endif()

# ----------------------------------------------------------------------------
# 文件分组函数（用于 IDE 文件夹结构）
# ----------------------------------------------------------------------------
function(set_source_groups SOURCE_FILES SOURCE_DIR SOURCE_DIR_NAME)
    foreach(each_source_file IN LISTS SOURCE_FILES)
        get_filename_component(each_source_path "${each_source_file}" PATH)
        file(RELATIVE_PATH each_source_path_rel ${SOURCE_DIR} ${each_source_path})
        if("${each_source_path_rel}" STREQUAL "")
            source_group("${SOURCE_DIR_NAME}" FILES ${each_source_file})
        else()
            string(REPLACE "/" "\\" each_source_group_path ${each_source_path_rel})
            source_group("${SOURCE_DIR_NAME}/${each_source_group_path}" FILES ${each_source_file})
        endif()
    endforeach()
endfunction()

# ----------------------------------------------------------------------------
# 设置源代码目录与递归搜索
# ----------------------------------------------------------------------------
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Src)
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "${SOURCE_DIR}/*.*")

# ----------------------------------------------------------------------------
# 忽略特定文件
# ----------------------------------------------------------------------------
set(IGNORE_FILES "")
if(NOT IS_ROOT_DIR)
    set(IGNORE_FILES "SourceCode/main.cpp")
endif()
foreach(file ${IGNORE_FILES})
    list(FILTER SOURCE_FILES EXCLUDE REGEX ${file})
endforeach()

# ----------------------------------------------------------------------------
# 目标类型与分组
# ----------------------------------------------------------------------------
if(IS_ROOT_DIR)
    add_executable(${PROJECT_NAME} ${SOURCE_FILES})
else()
    add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
endif()
set_source_groups("${SOURCE_FILES}" ${SOURCE_DIR} "SourceCode")

# ----------------------------------------------------------------------------
# 目标属性
# ----------------------------------------------------------------------------
if(IS_ROOT_DIR)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/$<CONFIG>
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib/$<CONFIG>
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib/$<CONFIG>
        PDB_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin/$<CONFIG>
        VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
else()
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib/$<CONFIG>
        VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# ----------------------------------------------------------------------------
# 子仓库与第三方库
# ----------------------------------------------------------------------------
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(Env/pfr EXCLUDE_FROM_ALL)
add_subdirectory(Env/ktm EXCLUDE_FROM_ALL)
add_subdirectory(Env/preprocessor EXCLUDE_FROM_ALL)
set(ENABLE_OPT OFF)
add_subdirectory(Env/glslang EXCLUDE_FROM_ALL)
set(SPIRV_CROSS_SHARED OFF)
set(SPIRV_CROSS_STATIC ON)
set(SPIRV_CROSS_ENABLE_TESTS OFF)
set(SPIRV_CROSS_CLI OFF)
add_subdirectory(Env/SPIRV-Cross EXCLUDE_FROM_ALL)

# ----------------------------------------------------------------------------
# 公共目标配置
# ----------------------------------------------------------------------------
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<AND:$<CONFIG:RelWithDebInfo>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-fno-omit-frame-pointer>
    $<$<AND:$<CONFIG:RelWithDebInfo>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-g>
    $<$<AND:$<CONFIG:MinSizeRel>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-ffunction-sections>
    $<$<AND:$<CONFIG:MinSizeRel>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-fdata-sections>
    $<$<AND:$<CONFIG:MinSizeRel>,$<CXX_COMPILER_ID:Clang>>:-Oz>
    $<$<AND:$<CONFIG:MinSizeRel>,$<CXX_COMPILER_ID:MSVC>>:/GL>
    $<$<CXX_COMPILER_ID:MSVC>:/W1>
    $<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>
    $<$<CXX_COMPILER_ID:MSVC>:/execution-charset:utf-8>
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:RelWithDebInfo>:ENABLE_DETAILED_LOGGING=1>
    $<$<CONFIG:RelWithDebInfo>:CABBAGE_ENGINE_DEBUG>
    $<$<CONFIG:MinSizeRel>:DISABLE_EXTRA_FEATURES=1>
    $<$<CONFIG:MinSizeRel>:CABBAGE_ENGINE_RELEASE>
    $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>
    NOMINMAX
)

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/Src"
    "${CMAKE_CURRENT_SOURCE_DIR}/Env/ktm"
    "${CMAKE_CURRENT_SOURCE_DIR}/Env/pfr/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/Env/preprocessor/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/Env/glslang"
    "${CMAKE_CURRENT_SOURCE_DIR}/Env/SPIRV-Cross"
)

target_link_options(${PROJECT_NAME} PRIVATE
    $<$<AND:$<CONFIG:MinSizeRel>,$<PLATFORM_ID:Linux>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:LINKER:--gc-sections>
    $<$<AND:$<CONFIG:MinSizeRel>,$<PLATFORM_ID:Darwin>>:-dead_strip>
    $<$<AND:$<CONFIG:MinSizeRel>,$<CXX_COMPILER_ID:MSVC>>:/LTCG>
    $<$<AND:$<CONFIG:MinSizeRel>,$<CXX_COMPILER_ID:MSVC>>:/OPT:REF>
    $<$<AND:$<CONFIG:MinSizeRel>,$<CXX_COMPILER_ID:MSVC>>:/OPT:ICF>
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glslang
    glslang-default-resource-limits
    spirv-cross-core
    spirv-cross-c
    spirv-cross-cpp
    spirv-cross-util
)