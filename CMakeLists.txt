cmake_minimum_required(VERSION 3.20)
project(gameEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(gameEngine/libraries/enginemath)

add_executable(gameEngine
    gameEngine/main.cpp
    gameEngine/glad.c
)

target_include_directories(gameEngine PRIVATE
    ${CMAKE_SOURCE_DIR}/gameEngine/libraries/include
)

if (WIN32)
    target_link_libraries(gameEngine PRIVATE
        opengl32
        ${CMAKE_SOURCE_DIR}/gameEngine/libraries/lib/glfw3.lib
        enginemath::enginemath
    )
elseif(UNIX)
    find_package(OpenGL REQUIRED)
    find_package(glfw3 REQUIRED)

    target_link_libraries(gameEngine PRIVATE
        OpenGL::GL
        glfw
        enginemath::enginemath
    )
endif()