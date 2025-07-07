file(GLOB_RECURSE EXAMPLES_SOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

add_executable(HeliconExamples ${EXAMPLES_SOURCE_FILES})
set_source_groups(${EXAMPLES_SOURCE_FILES} ${PROJECT_SOURCE_DIR} "Source Code")

set_binary_properties(HeliconExamples)

target_link_libraries(HeliconExamples PRIVATE Helicon)