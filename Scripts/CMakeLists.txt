file(GLOB_RECURSE SCRIPTS_SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SCRIPTS_SOURCE_FILES})
add_executable(ShaderCompileScripts ${SCRIPTS_SOURCE_FILES})

# 设置VS启动项目
set_property(DIRECTORY ${PROJECT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ShaderCompileScripts)

set_target_properties(ShaderCompileScripts PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:ShaderCompileScripts>
)

target_link_libraries(ShaderCompileScripts PRIVATE Helicon)

helicon_install_runtime_deps(ShaderCompileScripts)