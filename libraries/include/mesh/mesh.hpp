#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "vertex.h"


class Mesh {
    public:
        
    // Constructors
    Mesh(const Vertex* vertices, size_t count);
    Mesh(const Vertex* vertices, const int* indices, size_t count);

    private:

    unsigned int VBO, VAO, EBO;
};

#endif