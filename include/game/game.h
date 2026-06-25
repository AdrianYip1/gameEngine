#pragma once

#include "../application/application.h"
#include "../window/window.h"
#include "../gameObject/gameObject.h"
#include "../scene/scene.h"
#include "../rendering/renderer/render.h"
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
		cube->mesh = std::make_unique<Mesh>(/* verts, indices, textures */);
		scene.add(std::move(cube));
	}
	void renderInto(Window* w) override {
		// how the game window(s) get rendered
		renderer.draw(scene);
	}
	
private:

};