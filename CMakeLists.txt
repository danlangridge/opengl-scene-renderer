cmake_minimum_required (VERSION 2.8)
project (RENDERER)

link_directories(${RENDERER_SOURCE_DIR}/gravel-engine)

include_directories(${RENDERER_SOURCE_DIR})
include_directories(${RENDERER_SOURCE_DIR}/src)
include_directories(${RENDERER_SOURCE_DIR}/gravel-engine)
include_directories(${RENDERER_SOURCE_DIR}/externals)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${RENDERER_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${RENDERER_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RENDERER_SOURCE_DIR}/bin)

add_subdirectory( ${RENDERER_SOURCE_DIR}/gravel-engine )
add_subdirectory( ${RENDERER_SOURCE_DIR}/shaders )
add_subdirectory( ${RENDERER_SOURCE_DIR}/externals )
add_subdirectory( ${RENDERER_SOURCE_DIR}/tests )
add_subdirectory( ${RENDERER_SOURCE_DIR}/src )
