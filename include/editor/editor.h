#pragma once

#include "../application/application.h"
#include "../window/window.h"
#include <memory>

struct Editor : public Application {
public:
	Editor() { // constructor that populates window once with the main screen
		onInit();
	}
protected:
	void onInit() override {
		windows.push_back(std::make_unique<Window>(640, 480, "main"));
	}

private:

};