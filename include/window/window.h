#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <input/input.h>

struct Window {
public:
	Window(int width, int height, const char* title, bool depth = true) {

		handle = nullptr;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
		w = width;
		h = height;
		handle = glfwCreateWindow(w, h, title, NULL, NULL);
		if (!handle) {
			std::cerr << "Failed to create GLFW window\n";
			return;
		}
		glfwMakeContextCurrent(handle);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cerr << "Failed to init GLAD\n";
			return;
		}

		glfwSwapInterval(1); // default interval is zero -> set it to one for better CPI and GPU performance (less cycles)

		glfwSetWindowUserPointer(handle, this);
		glfwSetFramebufferSizeCallback(handle, [](GLFWwindow* window, int width, int height) {
			auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
			self->framebuffer_size_callback(width, height);
		});

		glViewport(0, 0, w, h);
		if (depth) glEnable(GL_DEPTH_TEST); 
		valid = true;
		input.window = handle;
	}

	~Window() { glfwDestroyWindow(handle); }

	bool shouldClose() { return glfwWindowShouldClose(handle); }

	void swapBuffers() { glfwSwapBuffers(handle); }

	int width() const { return w; }

	int height() const { return h; }

	bool isValid() { return valid; }

	void makeContextCurrent() { glfwMakeContextCurrent(handle); }

	Input& getInput() { return input; }

private:
	GLFWwindow* handle;
	int w, h;
	bool valid = false; // switches to true if window creation has no errors
	Input input;

	// Window size change
	void framebuffer_size_callback(int width, int height) {
		w = width;
		h = height;
		glViewport(0, 0, width, height);
	}
};