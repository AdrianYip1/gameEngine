#pragma once

#include "../application/application.h"
#include "../window/window.h"
#include "../gameObject/gameObject.h"
#include "../scene/scene.h"
#include "../rendering/renderer/render.h"
#include "../rendering/texture/texture.h"
#include <memory>
#include <vector>

struct Game : public Application {
public:
protected:
	Render renderer;
	Scene scene;

	void onInit() override {
		windows.push_back(std::make_unique<Window>(640, 480, "game")); 

		auto cube = std::make_unique<GameObject>();
		cube->shader = std::make_unique<Shader>("basic.vert", "basic.frag");

		// triangle in NDC so it is visible with an identity model and no camera yet
		// Vertex layout: position, normal, texCoords, tangent
		std::vector<Vertex> verts = {
			{{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
			{{ 0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
			{{ 0.0f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.5f, 1.0f}, {1.0f, 0.0f, 0.0f}},
		};
		std::vector<unsigned int> indices = { 0, 1, 2 };
		std::vector<std::shared_ptr<Texture>> textures = {};

		cube->mesh = std::make_unique<Mesh>(verts, indices, textures);
		scene.add(std::move(cube));
	}
	void renderInto(Window* w) override {
		// how the game window(s) get rendered
		renderer.draw(scene);
	}

	void onUpdate(float dt) override {

	}
	
private:

};