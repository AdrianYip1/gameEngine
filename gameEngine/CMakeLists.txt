cmake_minimum_required(VERSION 3.20)
project(gameEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add enginemath submodule
add_subdirectory(gameEngine/libraries/enginemath)

add_executable(gameEngine
    gameEngine/main.cpp
    gameEngine/glad.c
)

target_include_directories(gameEngine PRIVATE
    gameEngine/libraries/include
    gameEngine/libraries/include/glad
    gameEngine/libraries/include/GLFW
    gameEngine/libraries/include/KHR
)

target_link_libraries(gameEngine PRIVATE
    ${CMAKE_SOURCE_DIR}/gameEngine/libraries/lib/glfw3.lib
    enginemath
    opengl32
)