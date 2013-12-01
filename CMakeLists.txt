cmake_minimum_required (VERSION 2.8)
project (RENDERER)

set( EXTERNALS_SOURCE_FILES ${RENDERER_SOURCE_DIR}/externals/gl_libs.h )

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

ADD_DEFINITIONS(
  -lGLEW
  -lGLU
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${RENDERER_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${RENDERER_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RENDERER_SOURCE_DIR}/bin)

MESSAGE("Project Directory is: ${RENDERER_SOURCE_DIR}" )
MESSAGE("GLEW Directory is: ${GLEW_LIBRARIES}" )

include_directories(${RENDERER_SOURCE_DIR})
include_directories(${RENDERER_SOURCE_DIR}/gravel-engine)
include_directories(${RENDERER_SOURCE_DIR}/externals)

link_directories(${RENDERER_SOURCE_DIR}/gravel-engine)

add_subdirectory( ${RENDERER_SOURCE_DIR}/gravel-engine )
add_subdirectory( ${RENDERER_SOURCE_DIR}/shaders )
add_subdirectory( ${RENDERER_SOURCE_DIR}/externals )

add_executable (Renderer main.cpp ${EXTERNALS_SOURCE_FILES} ${RENDERER_SOURCE_DIR}/Sprite.cpp)

target_link_libraries(Renderer Gravel ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} GLEW Graphics Game )

add_library( Graphics STATIC
  GraphicsContext.cpp
  KeyInput.cpp
  MouseInput.cpp
  UserContext.cpp
  PhysicsContext.cpp 
  GameContext.cpp
  Object.cpp
  Camera.cpp
  OBJLoader.cpp
)

target_link_libraries( Graphics GLEW ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} Gravel GLU )

add_library( Game STATIC
  Sprite.cpp
)

target_link_libraries( Game GLEW ${GLUT_LIBRARY} Gravel Graphics )
