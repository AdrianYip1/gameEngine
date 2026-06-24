// Everything that runs once for the whole program
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../src/glfwHelpers.h"
#include "../window/window.h"
#include <iostream>
#include <vector>
#include <memory>

struct Application {
public:
	Application() {
		glfwSetErrorCallback(error_callback);
		if (!glfwInit()) {
			std::cerr << "Failed to init GLFW\n";
			return;
		}
	}

	virtual ~Application() {
		windows.clear();
		glfwTerminate();
	}

	void run() {
		onInit();
		if (windows.empty() || !windows[0]->isValid()) return;
		float last = (float)glfwGetTime();

		// onInit should populate the window vector so window[0] will always have something
		while (!windows[0]->shouldClose()) {
			float now = (float)glfwGetTime();
			float dt = now - last;
			last = now;

			glfwPollEvents();
			onUpdate(dt);

			// remove any closed windows
			for (size_t i = windows.size(); i-- > 1;) {
				if (windows[i]->shouldClose()) {
					windows.erase(windows.begin() + i);
				}
			}

			// render remaining windows
			for (auto& w : windows) {
				w->makeContextCurrent();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				renderInto(w.get());
				w->swapBuffers();
			}
		}
	}

private:
	virtual void onUpdate(float dt) {};
	virtual void renderInto(Window* w) {};

protected:
	std::vector<std::unique_ptr<Window>> windows;
	virtual void onInit() {}; // makes the windows


};