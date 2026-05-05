#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <enginemath/vec3.hpp>
#include <enginemath/vec4.hpp>
#include <enginemath/mat4.hpp>
#include <enginemath/mathutils.hpp>
#include <shader/shader.hpp>
#include <render/render.hpp>
#include <mesh/mesh.hpp>
#include <texture/texture.hpp>
#include <mesh/vertex.h>
#include "stb_image.h"

enginemath::Vec3 cameraPos = enginemath::Vec3(0.0f, 0.0f, 3.0f);
enginemath::Vec3 cameraFront = enginemath::Vec3(0.0f, 0.0f, -1.0f);
enginemath::Vec3 cameraUp = enginemath::Vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 400.0f;
float lastY = 300.0f;
bool firstMouse = true;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
};

float processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
		return 0.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		return 0.001f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		return -0.001f;
	}
	return 0.0f;
};

void movementInput(GLFWwindow *window) {
	const float cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cameraPos += cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * cameraFront.cross(cameraUp).normalized();
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPos += cameraSpeed * cameraFront.cross(cameraUp).normalized();
	}
}


Vertex vertices[] = {
// back face
{{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
{{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
{{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},

{{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
{{-0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
{{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},

// front face
{{-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
{{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
{{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},

{{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
{{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
{{-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},

// left face
{{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
{{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
{{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
{{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},

// right face
{{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
{{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f}},
{{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},

{{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
{{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
{{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},

// bottom face
{{-0.5f, -0.5f, -0.5f}, {0.5f, 0.0f, 1.0f}, {0.0f, 1.0f}},
{{ 0.5f, -0.5f, -0.5f}, {0.5f, 0.0f, 1.0f}, {1.0f, 1.0f}},
{{ 0.5f, -0.5f,  0.5f}, {0.5f, 0.0f, 1.0f}, {1.0f, 0.0f}},

{{ 0.5f, -0.5f,  0.5f}, {0.5f, 0.0f, 1.0f}, {1.0f, 0.0f}},
{{-0.5f, -0.5f,  0.5f}, {0.5f, 0.0f, 1.0f}, {0.0f, 0.0f}},
{{-0.5f, -0.5f, -0.5f}, {0.5f, 0.0f, 1.0f}, {0.0f, 1.0f}},

// top face
{{-0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
{{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
{{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},

{{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
{{-0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
{{-0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f}}
};

unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	float sensitivity = 0.01f;

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if(pitch > 89.0f) pitch = 89.0f;
	if(pitch < -89.0f) pitch = -89.0f;

	enginemath::Vec3 direction;
	direction.x = cos(enginemath::toRad(yaw)) * cos(enginemath::toRad(pitch));
	direction.y = sin(enginemath::toRad(pitch));
	direction.z = sin(enginemath::toRad(yaw)) * cos(enginemath::toRad(pitch));
	cameraFront = direction.normalized();
}


int main() {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Main", NULL, NULL);
	glfwMakeContextCurrent(window);

	// Load Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialized GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);


	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	stbi_set_flip_vertically_on_load(true);

	Mesh cube(vertices, 36);

	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char *data = stbi_load("textures/container.jpg", &width, &height, &nrChannels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "ERROR GENERATING TEXTURE" << std::endl;
	}
	stbi_image_free(data); 

	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("textures/awesomeface.png", &width, &height, &nrChannels, 0);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "ERROR GENERATING TEXTURE" << std::endl;
	}
	stbi_image_free(data); 

	//Shader
	Shader shader("shaders/basic.vert", "shaders/basic.frag");
	shader.use();
	shader.setInt("texture1", 0);
	shader.setInt("texture2", 1);

	int success;
	glGetProgramiv(shader.ID, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(shader.ID, 512, NULL, infoLog);
		std::cout << "SHADER LINK ERROR: " << infoLog << std::endl;
	}

	float smileyVisibility = 0.5;
	unsigned int modelLoc = glGetUniformLocation(shader.ID, "modelM");
	unsigned int viewLoc = glGetUniformLocation(shader.ID, "viewM");
	unsigned int projectionLoc = glGetUniformLocation(shader.ID, "projectionM");

	enginemath::Vec3 cubePositions[] = {
		enginemath::Vec3(0.0f, 0.0f, 0.0f),
		enginemath::Vec3(2.0f, 5.0f, -15.0f),
		enginemath::Vec3(-1.5f, -2.2f, -2.5f),
		enginemath::Vec3(-3.8f, -2.0f, -12.3f),
		enginemath::Vec3( 2.4f, -0.4f, -3.5f),
		enginemath::Vec3(-1.7f, 3.0f, -7.5f),
		enginemath::Vec3( 1.3f, -2.0f, -2.5f),
		enginemath::Vec3( 1.5f, 2.0f, -2.5f),
		enginemath::Vec3( 1.5f, 0.2f, -1.5f),
		enginemath::Vec3(-1.3f, 1.0f, -1.5f)
	};


	Render renderer;
	// Render Loop
	while (!glfwWindowShouldClose(window)) {


		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		cube.bind();

		movementInput(window);
		smileyVisibility += processInput(window);
		if (smileyVisibility < 0.0) smileyVisibility = 0.0;
		if (smileyVisibility > 1.0) smileyVisibility = 1.0;


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();
		shader.setFloat("faceVisibility", smileyVisibility);

		enginemath::Mat4 projectionM = enginemath::Mat4::projectionM(enginemath::toRad(30.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		enginemath::Mat4 viewM = enginemath::Mat4::lookAtM(cameraPos, cameraPos + cameraFront, cameraUp);
	

		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projectionM.data());
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, viewM.data());

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		for (unsigned int i = 0; i < 10; i++) {
			enginemath::Mat4 modelM = enginemath::Mat4::translationM(cubePositions[i]);

			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, modelM.data());

			renderer.draw(cube);

		}
		
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwTerminate();
	return 0;
}