#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "vertex.h"
#include "texture.hpp"

class Mesh {
    public:
    //Mesh Data
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

    void Draw(Shader &shader);

    private:
    //Render Data
    unsigned int VAO, VBO, EBO;

    void setupMesh();
}

#endif