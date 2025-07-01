# ============================= Helicon CMake 配置 =============================
# 设置 CMake 最低版本要求
cmake_minimum_required(VERSION 4.0)
set(CMAKE_POLICY_VERSION_MINIMUM "4.0")

# -------------------------------------------------------------------------------
# 项目基本信息
# -------------------------------------------------------------------------------
project(
    Helicon
    VERSION 0.5.0
    HOMEPAGE_URL "https://github.com/CoronaEngine/Helicon"
    LANGUAGES C CXX
)

# -------------------------------------------------------------------------------
# 检查是否使用 CMake 预设配置
# -------------------------------------------------------------------------------
if(NOT USED_PRESET_CONFIG)
    message(FATAL_ERROR "[Helicon] 错误: 必须使用 CMake 预设配置 (USED_PRESET_CONFIG)！")
endif()

# -------------------------------------------------------------------------------
# 根目录判定与日志输出
# -------------------------------------------------------------------------------
set(IS_ROOT_DIR FALSE)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(IS_ROOT_DIR TRUE)
endif()

if(IS_ROOT_DIR)
    message(STATUS "[Helicon] 当前为项目根目录: ${CMAKE_CURRENT_SOURCE_DIR}")
else()
    message(STATUS "[Helicon] 当前为子目录: ${CMAKE_CURRENT_SOURCE_DIR}")
endif()

# -------------------------------------------------------------------------------
# CMake 策略配置
# -------------------------------------------------------------------------------
if(POLICY CMP0077)
    cmake_policy(SET CMP0077 NEW) # 使 option() 支持目录作用域
    message(STATUS "[Helicon] 已启用 CMake 策略 CMP0077")
endif()

# -------------------------------------------------------------------------------
# 源代码管理与分组
# -------------------------------------------------------------------------------
# 文件分组函数（用于 IDE 文件夹结构）
function(set_source_groups SOURCE_FILES SOURCE_DIR SOURCE_DIR_NAME)
    foreach(each_source_file IN LISTS SOURCE_FILES)
        get_filename_component(each_source_path "${each_source_file}" PATH)
        file(RELATIVE_PATH each_source_path_rel ${SOURCE_DIR} ${each_source_path})

        # 空路径直接分组到根
        if("${each_source_path_rel}" STREQUAL "")
            source_group("${SOURCE_DIR_NAME}" FILES ${each_source_file})
            continue()
        endif()

        string(REPLACE "/" "\\" each_source_group_path ${each_source_path_rel})
        source_group("${SOURCE_DIR_NAME}/${each_source_group_path}" FILES ${each_source_file})
    endforeach()
endfunction()

# 设置源代码目录
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SourceCode)

# 递归搜索所有源文件
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "${SOURCE_DIR}/*.*")

# -------------------------------------------------------------------------------
# 忽略特定文件/文件夹
# -------------------------------------------------------------------------------
if(IS_ROOT_DIR)
else()
    set(IGNORE_FILES
        "SourceCode/main.cpp"
    )
endif()

# 过滤掉要忽略的文件或文件夹
foreach(file ${IGNORE_FILES})
    list(FILTER SOURCE_FILES EXCLUDE REGEX ${file})
endforeach()

# -------------------------------------------------------------------------------
# 主目标配置（仅根目录下）
# -------------------------------------------------------------------------------
if(IS_ROOT_DIR)
    add_executable(${PROJECT_NAME} ${SOURCE_FILES})
    set_source_groups("${SOURCE_FILES}" ${SOURCE_DIR} "SourceCode")

    # ---------------------------------------------------------------------------
    # 编译器选项
    # ---------------------------------------------------------------------------
    target_compile_options(${PROJECT_NAME} PRIVATE

        # RelWithDebInfo: 保留调试信息
        $<$<AND:$<CONFIG:RelWithDebInfo>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-fno-omit-frame-pointer>
        $<$<AND:$<CONFIG:RelWithDebInfo>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-g>

        # MinSizeRel: 优化体积
        $<$<AND:$<CONFIG:MinSizeRel>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-ffunction-sections>
        $<$<AND:$<CONFIG:MinSizeRel>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-fdata-sections>
        $<$<AND:$<CONFIG:MinSizeRel>,$<CXX_COMPILER_ID:Clang>>:-Oz>
        $<$<AND:$<CONFIG:MinSizeRel>,$<CXX_COMPILER_ID:MSVC>>:/GL>

        # MSVC 通用
        $<$<CXX_COMPILER_ID:MSVC>:/W1>
        $<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>
        $<$<CXX_COMPILER_ID:MSVC>:/execution-charset:utf-8>
    )

    # ---------------------------------------------------------------------------
    # 链接器选项
    # ---------------------------------------------------------------------------
    target_link_options(${PROJECT_NAME} PRIVATE

        # MinSizeRel: 链接优化
        $<$<AND:$<CONFIG:MinSizeRel>,$<PLATFORM_ID:Linux>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:LINKER:--gc-sections>
        $<$<AND:$<CONFIG:MinSizeRel>,$<PLATFORM_ID:Darwin>>:-dead_strip>
        $<$<AND:$<CONFIG:MinSizeRel>,$<CXX_COMPILER_ID:MSVC>>:/LTCG>
        $<$<AND:$<CONFIG:MinSizeRel>,$<CXX_COMPILER_ID:MSVC>>:/OPT:REF>
        $<$<AND:$<CONFIG:MinSizeRel>,$<CXX_COMPILER_ID:MSVC>>:/OPT:ICF>
    )

    # ---------------------------------------------------------------------------
    # 预处理器定义
    # ---------------------------------------------------------------------------
    target_compile_definitions(${PROJECT_NAME} PRIVATE

        # 配置相关
        $<$<CONFIG:RelWithDebInfo>:ENABLE_DETAILED_LOGGING=1>
        $<$<CONFIG:RelWithDebInfo>:CABBAGE_ENGINE_DEBUG>
        $<$<CONFIG:MinSizeRel>:DISABLE_EXTRA_FEATURES=1>
        $<$<CONFIG:MinSizeRel>:CABBAGE_ENGINE_RELEASE>

        # MSVC 特定
        $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>
        NOMINMAX
    )

    # ---------------------------------------------------------------------------
    # 目标属性
    # ---------------------------------------------------------------------------
    set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/$<CONFIG>
        PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<CONFIG>
        VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )

    # ---------------------------------------------------------------------------
    # 全局属性
    # ---------------------------------------------------------------------------
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

    # ---------------------------------------------------------------------------
    # 子仓库与第三方库
    # ---------------------------------------------------------------------------
    set(BUILD_SHARED_LIBS OFF) # 禁用所有第三方库的动态库构建，全部使用静态库

    # 添加 pfr、ktm、preprocessor 子模块
    add_subdirectory(ExternalEnvironment/pfr EXCLUDE_FROM_ALL)
    add_subdirectory(ExternalEnvironment/ktm EXCLUDE_FROM_ALL)
    add_subdirectory(ExternalEnvironment/preprocessor EXCLUDE_FROM_ALL)

    # --- glslang ---
    set(ENABLE_OPT OFF) # 禁用 glslang 的优化模块
    add_subdirectory(ExternalEnvironment/glslang EXCLUDE_FROM_ALL)

    # --- SPIRV-Cross ---
    set(SPIRV_CROSS_SHARED OFF)         # 禁用 SPIRV-Cross 动态库
    set(SPIRV_CROSS_STATIC ON)          # 启用 SPIRV-Cross 静态库
    set(SPIRV_CROSS_ENABLE_TESTS OFF)   # 禁用 SPIRV-Cross 测试
    set(SPIRV_CROSS_CLI OFF)            # 禁用 SPIRV-Cross 命令行工具
    add_subdirectory(ExternalEnvironment/SPIRV-Cross EXCLUDE_FROM_ALL)

    # --- 链接第三方库 ---
    # 链接 glslang 及 SPIRV-Cross 相关静态库
    target_link_libraries(${PROJECT_NAME} PRIVATE
        glslang
        glslang-default-resource-limits
        spirv-cross-core
        spirv-cross-c
        spirv-cross-cpp
        spirv-cross-util
    )

    # ---------------------------------------------------------------------------
    # Windows 平台专用配置
    # ---------------------------------------------------------------------------
    if(WIN32)
        # 添加各依赖的 include 路径
        target_include_directories(${PROJECT_NAME} PRIVATE
            "${CMAKE_CURRENT_SOURCE_DIR}/SourceCode"
            "${CMAKE_CURRENT_SOURCE_DIR}/ExternalEnvironment/ktm"
            "${CMAKE_CURRENT_SOURCE_DIR}/ExternalEnvironment/pfr/include"
            "${CMAKE_CURRENT_SOURCE_DIR}/ExternalEnvironment/preprocessor/include"
            "${CMAKE_CURRENT_SOURCE_DIR}/ExternalEnvironment/glslang"
            "${CMAKE_CURRENT_SOURCE_DIR}/ExternalEnvironment/SPIRV-Cross"
        )
        message(STATUS "[Helicon] 已为 Windows 平台配置 include 路径")
    endif()

    message(STATUS "[Helicon] 主目标与第三方库配置完成")
endif()