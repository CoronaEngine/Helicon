file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

add_library(Helicon STATIC ${SOURCE_FILES})
set_source_groups(${SOURCE_FILES} ${PROJECT_SOURCE_DIR} "Source Code")

set_library_properties(Helicon)

target_compile_definitions(Helicon PUBLIC HELICON_ROOT_PATH="${PROJECT_SOURCE_DIR}")

target_include_directories(Helicon PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/Env/ktm"
    "${PROJECT_SOURCE_DIR}/Env/pfr/include"
    "${PROJECT_SOURCE_DIR}/Env/preprocessor/include"
    "${PROJECT_SOURCE_DIR}/Env/glslang"
    "${PROJECT_SOURCE_DIR}/Env/SPIRV-Cross"
)

target_link_libraries(Helicon PUBLIC
    glslang
    glslang-default-resource-limits
    spirv-cross-core
    spirv-cross-c
    spirv-cross-cpp
    spirv-cross-util
)
