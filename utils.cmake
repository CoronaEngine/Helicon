function(set_source_groups SOURCE_FILES SOURCE_DIR SOURCE_DIR_NAME)
    # 验证输入参数
    if(NOT SOURCE_FILES)
        message(WARNING "Empty SOURCE_FILES passed to set_source_groups")
        return()
    endif()

    # 确定平台适配的分隔符（Windows用\，其他平台用/）
    if(CMAKE_GENERATOR MATCHES "Visual Studio" OR CMAKE_HOST_WIN32)
        set(SEP "\\")
    else()
        set(SEP "/")
    endif()

    # 处理根目录名称的空值情况
    if("${SOURCE_DIR_NAME}" STREQUAL "")
        set(SOURCE_DIR_NAME "Source Files")
    endif()

    foreach(each_source_file IN LISTS SOURCE_FILES)
        # 获取文件的规范化和绝对路径
        get_filename_component(abs_path "${each_source_file}" ABSOLUTE)

        # 计算相对于源目录的相对路径
        file(RELATIVE_PATH rel_path "${SOURCE_DIR}" "${abs_path}")

        # 提取目录部分（去掉文件名）
        get_filename_component(dir_path "${rel_path}" DIRECTORY)

        if(dir_path STREQUAL "")
            # 根目录下的文件
            source_group("${SOURCE_DIR_NAME}" FILES ${each_source_file})
        else()
            # 转换路径分隔符并创建分组
            string(REPLACE "/" "${SEP}" group_path "${dir_path}")
            source_group("${SOURCE_DIR_NAME}${SEP}${group_path}" FILES ${each_source_file})
        endif()
    endforeach()
endfunction()

function(set_library_properties TARGET_NAME)
    set_target_properties(${TARGET_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib/$<CONFIG>
    )

    target_compile_options(${TARGET_NAME} PRIVATE
        $<$<AND:$<CONFIG:RelWithDebInfo>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-fno-omit-frame-pointer -g>
        $<$<AND:$<CONFIG:MinSizeRel>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-ffunction-sections -fdata-sections>
        $<$<AND:$<CONFIG:MinSizeRel>,$<CXX_COMPILER_ID:Clang>>:-Oz>
        $<$<AND:$<CONFIG:MinSizeRel>,$<CXX_COMPILER_ID:MSVC>>:/GL>
        $<$<CXX_COMPILER_ID:MSVC>:/W1 /source-charset:utf-8 /execution-charset:utf-8>
    )

    target_compile_definitions(${TARGET_NAME}
        PRIVATE
        $<$<CONFIG:RelWithDebInfo>:ENABLE_DETAILED_LOGGING=1>
        $<$<CONFIG:RelWithDebInfo>:CABBAGE_ENGINE_DEBUG>
        $<$<CONFIG:MinSizeRel>:DISABLE_EXTRA_FEATURES=1>
        $<$<CONFIG:MinSizeRel>:CABBAGE_ENGINE_RELEASE>
        $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>
        NOMINMAX
    )
endfunction()

function(set_binary_properties TARGET_NAME)
    set_target_properties(${TARGET_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/$<CONFIG>
        PDB_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/$<CONFIG>
        VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${TARGET_NAME}>
    )

    target_compile_options(${TARGET_NAME} PRIVATE
        $<$<AND:$<CONFIG:RelWithDebInfo>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-fno-omit-frame-pointer -g>
        $<$<AND:$<CONFIG:MinSizeRel>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:-ffunction-sections -fdata-sections>
        $<$<AND:$<CONFIG:MinSizeRel>,$<CXX_COMPILER_ID:Clang>>:-Oz>
        $<$<AND:$<CONFIG:MinSizeRel>,$<CXX_COMPILER_ID:MSVC>>:/GL>
        $<$<CXX_COMPILER_ID:MSVC>:/W1 /source-charset:utf-8 /execution-charset:utf-8>
    )

    target_compile_definitions(${TARGET_NAME} PRIVATE
        $<$<CONFIG:RelWithDebInfo>:ENABLE_DETAILED_LOGGING=1>
        $<$<CONFIG:RelWithDebInfo>:CABBAGE_ENGINE_DEBUG>
        $<$<CONFIG:MinSizeRel>:DISABLE_EXTRA_FEATURES=1>
        $<$<CONFIG:MinSizeRel>:CABBAGE_ENGINE_RELEASE>
        $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>
        NOMINMAX
    )

    target_link_options(${TARGET_NAME} PRIVATE
        $<$<AND:$<CONFIG:MinSizeRel>,$<PLATFORM_ID:Linux>,$<NOT:$<CXX_COMPILER_ID:MSVC>>>:LINKER:--gc-sections>
        $<$<AND:$<CONFIG:MinSizeRel>,$<PLATFORM_ID:Darwin>>:-dead_strip>
        $<$<AND:$<CONFIG:MinSizeRel>,$<CXX_COMPILER_ID:MSVC>>:/LTCG;/OPT:REF;/OPT:ICF>
    )
endfunction()