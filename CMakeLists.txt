cmake_minimum_required(VERSION 3.20)
project(gameEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(libraries/enginemath)

add_executable(gameEngine
    libraries/include/shader/shader.cpp
    libraries/include/mesh/mesh.cpp
    libraries/include/render/render.cpp
    libraries/include/texture/texture.cpp
    libraries/include/camera/camera.cpp
    stb_image.cpp
    main.cpp
    glad.c
)

file(COPY textures DESTINATION ${CMAKE_BINARY_DIR})
file(COPY shaders  DESTINATION ${CMAKE_BINARY_DIR})


target_include_directories(gameEngine PRIVATE
    ${CMAKE_SOURCE_DIR}/libraries/include
)

if (WIN32)
    target_link_libraries(gameEngine PRIVATE
        opengl32
        ${CMAKE_SOURCE_DIR}/libraries/lib/glfw3.lib
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