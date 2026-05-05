#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "vertex.h"


class Mesh {
    public:
    static_assert(sizeof(Vertex) == 8 * sizeof(float), "Vertex struct has unexpected padding!");

        // Constructors
        Mesh(const Vertex* vertices, size_t countV);
        Mesh(const Vertex* vertices, const int* indices, size_t countV, size_t countI);

        void bind() const;

        // Getters
        int getVertices() const;
        int getIndices() const;
        bool checkElementArray() const;

    private:

        unsigned int VBO, VAO, EBO;
        unsigned int numVertices, numIndices;
        bool usesElementArray;
};

#endif