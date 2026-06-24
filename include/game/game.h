#pragma once

#include "../application/application.h"
#include "../window/window.h"
#include "../gameObject/gameObject.h"
#include "../scene/scene.h"
#include <memory>
#include <vector>

struct Game : public Application {
public:
protected:
	Scene scene;

	void onInit() override {
		// the windows for the game
		windows.push_back(std::make_unique<Window>(640, 480, "game"));
		scene.add(std::make_unique<Cube>());
	}
	void renderInto(Window* w) override {
		// how the game window(s) get rendered
		for (auto& obj : scene.objects) {
			obj->draw();
		}
	}

private:

};