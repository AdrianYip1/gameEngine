#pragma once

#include "../application/application.h"
#include "../window/window.h"
#include <memory>

struct Editor : public Application {
public:
protected:
	void onInit() override {
		windows.push_back(std::make_unique<Window>(640, 480, "editor"));
	}
	void renderInto(Window* w) override {

	}

private:

};