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