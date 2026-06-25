#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <enginemath/mat4.hpp>
#include "../shader/shader.h"
#include "../../scene/scene.h"
#include "../../gameObject/gameObject.h"

struct Render {
public:	
	// Render draw will determine location of obkects
	// location of camera, which shaders, clears screen
	void draw(Scene& scene) {
		for (auto& obj : scene.objects) {
			if (!obj->shader) continue;
			obj->shader->use();
			obj->shader->setMat4("model", obj->transform);

			obj->draw();
		}
	}
};