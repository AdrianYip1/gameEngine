#ifndef RENDER_H
#define RENDER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <mesh/mesh.hpp>


class Render {
    public:
        void draw(const Mesh& mesh);

        // being and end frame
        //begin frame sets up stuff like uniforms, matrices
        //end frame handles buffers, polls
};

#endif