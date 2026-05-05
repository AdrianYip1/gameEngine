#include "render.hpp"

void Render::draw(const Mesh& mesh) {
    mesh.bind();

    if (mesh.checkElementArray()) {
        glDrawElements(GL_TRIANGLES, mesh.getIndices(), GL_UNSIGNED_INT, 0);
    }
    else {
        glDrawArrays(GL_TRIANGLES, 0, mesh.getVertices());
    }
}