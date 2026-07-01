#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct Input {
public:
	// window is set when the window is created
	GLFWwindow* window = nullptr;

	bool isKeyDown(int key) const {
		return glfwGetKey(window, key) == GLFW_PRESS;
	}
};