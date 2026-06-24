cmake_minimum_required(VERSION 3.20)
project(gameEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(gameEngine
    src/main.cpp
    src/glad.c
    src/createApplication.cpp
 "src/glfwHelpers.h" "include/window/window.h" "include/application/application.h" "include/game/game.h" "include/scene/scene.h" "include/rendering/shader/shader.h")

target_include_directories(gameEngine PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Windows / MSVC: link the vendored GLFW static lib + system OpenGL.
target_link_libraries(gameEngine PRIVATE
    opengl32
    ${CMAKE_SOURCE_DIR}/lib/glfw3.lib
)

target_include_directories(gameEngine PRIVATE
    external/enginemath/include
)