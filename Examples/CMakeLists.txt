file(GLOB_RECURSE EXAMPLES_SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${EXAMPLES_SOURCE_FILES})
add_executable(HeliconExamples ${EXAMPLES_SOURCE_FILES})

# 设置VS启动项目
set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT HeliconExamples)

set_target_properties(HeliconExamples PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/$<CONFIG>
    PDB_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin/$<CONFIG>
    VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:HeliconExamples>
)

target_link_libraries(HeliconExamples PRIVATE Helicon)

file(GLOB SLANG_DLLS "${PROJECT_SOURCE_DIR}/Env/slang/bin/*.dll")

if(SLANG_DLLS)
    message(STATUS "Found Slang DLLs: ${SLANG_DLLS}")

    add_custom_command(
        TARGET HeliconExamples POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SLANG_DLLS} # 源文件列表
        $<TARGET_FILE_DIR:HeliconExamples> # 目标目录
        COMMENT "Copying Slang DLLs to the output directory"
    )
endif()