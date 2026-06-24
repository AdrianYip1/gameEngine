#pragma once

#include "../application/application.h"
#include "../window/window.h"
#include <memory>

struct Game : public Application {
public:
protected:

	void onInit() override {
		// the windows for the game
		windows.push_back(std::make_unique<Window>(640, 480, "main"));
	}
	void renderInto(Window* w) override {
		// how the game window(s) get rendered
	}

private:

};