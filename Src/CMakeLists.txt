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
)

target_link_directories(Helicon PUBLIC
    ${PROJECT_SOURCE_DIR}/Env/slang/lib)

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
)
