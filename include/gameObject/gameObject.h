#pragma once

#include <memory>
#include "../rendering/mesh/mesh.h"
#include "../rendering/shader/shader.h"

struct GameObject {
public:
	virtual ~GameObject() = default;
    std::unique_ptr<Mesh>mesh;   
    std::unique_ptr<Shader> shader;  
    enginemath::Mat4 transform = enginemath::Mat4::identity();

    virtual void draw() {
        if (mesh && shader) mesh->Draw(*shader);
    }
};
