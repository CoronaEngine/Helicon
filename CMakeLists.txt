# CMake 最低版本
cmake_minimum_required(VERSION 3.16)

#递归搜索文件
function(set_source_groups SOURCE_FILES SOURCE_DIR SOURCE_DIR_NAME)
    foreach(each_source_file IN LISTS SOURCE_FILES)
        get_filename_component(each_source_path "${each_source_file}" PATH)
        file(RELATIVE_PATH each_source_path_rel ${SOURCE_DIR} ${each_source_path})
        # 检查字符串是否为空 空的不分组
        if ("${each_source_path_rel}" STREQUAL "")
            source_group("${SOURCE_DIR_NAME}" FILES ${each_source_file})
            continue() 
        endif()
        string(REPLACE "/" "\\" each_source_group_path ${each_source_path_rel})
        source_group("${SOURCE_DIR_NAME}/${each_source_group_path}" FILES ${each_source_file})
    endforeach()
endfunction()


# 工程名
project(CabbageFramework)

#设置启动项
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT CabbageFramework)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)	# C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

#MSVC的C艹设置
if (MSVC)
    add_compile_options(/Zc:__cplusplus)
    add_compile_options(/Zc:preprocessor)
endif()

# 生成compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置Debug模式
set(CMAKE_BUILD_TYPE "Debug")

# 仅对 Visual Studio 编译器生效
if(MSVC)
    add_compile_options(
        $<$<CONFIG:Debug>:/MD>
        $<$<CONFIG:Release>:/MD>
    )
endif() 

# 设置构建类型输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/build/${CMAKE_HOST_SYSTEM_NAME}/${CMAKE_HOST_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE}/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/build/${CMAKE_HOST_SYSTEM_NAME}/${CMAKE_HOST_SYSTEM_PROCESSOR}/${CMAKE_BUILD_TYPE}/)

# 设置目标输出目录
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG})
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})
endif()

# 头文件目录
include_directories(
    ${PROJECT_SOURCE_DIR}/ktm/
    ${PROJECT_SOURCE_DIR}/pfr/include/
    ${PROJECT_SOURCE_DIR}/preprocessor/include/
    ${PROJECT_SOURCE_DIR}/SourceCode/
)

# 设置源代码目录
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/SourceCode)


# 递归搜索源文件
file(GLOB_RECURSE SOURCE_FILES
    "${SOURCE_DIR}/*.*"
)




# 添加可执行文件
add_executable(${PROJECT_NAME}  ${SOURCE_FILES})
set_source_groups("${SOURCE_FILES}" ${SOURCE_DIR} "SourceCode")
