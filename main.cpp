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
#include <camera/camera.hpp>
#include "stb_image.h"

enginemath::Vec3 cameraPos = enginemath::Vec3(0.0f, 0.0f, 3.0f);
enginemath::Vec3 cameraFront = enginemath::Vec3(0.0f, 0.0f, -1.0f);
enginemath::Vec3 cameraUp = enginemath::Vec3(0.0f, 1.0f, 0.0f);
enginemath::Vec3 cameraAngles(0.0f, -90.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;
enginemath::Vec3 lightColour(1.0f, 1.0f, 1.0f);

Camera camera;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
};

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
};

void movementInput(GLFWwindow *window) {
	const float cameraSpeed = 2.5f * deltaTime;
	const float cameraRotationSpeed = 30.0f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.directionalInput(cameraPos, cameraFront, cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.directionalInput(cameraPos, -cameraFront, cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.directionalInput(cameraPos, -cameraFront.cross(cameraUp).normalized(), cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.directionalInput(cameraPos, cameraFront.cross(cameraUp).normalized(), cameraSpeed);
	}

	//Camera Angles
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {	
		cameraAngles.x += cameraRotationSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		cameraAngles.y -= cameraRotationSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
		cameraAngles.x -= cameraRotationSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		cameraAngles.y += cameraRotationSpeed;
	}

	camera.angularInput(cameraFront, cameraAngles);

}


Vertex vertices[] = { //pos, normal, colour, texture
    // Back face
    { { -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
    { {  0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },
    { {  0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },
    { {  0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },
    { { -0.5f,  0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
    { { -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },

    // Front face
    { { -0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
    { {  0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },
    { {  0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },
    { {  0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },
    { { -0.5f,  0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
    { { -0.5f, -0.5f,  0.5f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },

    // Left face
    { { -0.5f,  0.5f,  0.5f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },
    { { -0.5f,  0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },
    { { -0.5f, -0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
    { { -0.5f, -0.5f, -0.5f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
    { { -0.5f, -0.5f,  0.5f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
    { { -0.5f,  0.5f,  0.5f }, { -1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },

    // Right face
    { {  0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },
    { {  0.5f,  0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },
    { {  0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
    { {  0.5f, -0.5f, -0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
    { {  0.5f, -0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
    { {  0.5f,  0.5f,  0.5f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },

    // Bottom face
    { { -0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
    { {  0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },
    { {  0.5f, -0.5f,  0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },
    { {  0.5f, -0.5f,  0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },
    { { -0.5f, -0.5f,  0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
    { { -0.5f, -0.5f, -0.5f }, { 0.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },

    // Top face
    { { -0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
    { {  0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },
    { {  0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },
    { {  0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f } },
    { { -0.5f,  0.5f,  0.5f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f } },
    { { -0.5f,  0.5f, -0.5f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
};

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


	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	stbi_set_flip_vertically_on_load(true);

	Mesh cube(vertices, 36);
	Mesh lightSource(vertices, 36);

	Shader lightingShader("shaders/lighting.vert", "shaders/lighting.frag");
	Shader lightSourceShader("shaders/lighting.vert", "shaders/lightSource.frag");


	enginemath::Vec3 colour1(1.0f, 1.0f, 1.0f);

	lightingShader.use();


	// Texture
	Texture texture1("textures/rubiks_cube_diffuse.jpg");
	Texture texture2("textures/sees.png");
	

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

	while (!glfwWindowShouldClose(window)) {
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);
		movementInput(window);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// cube

		enginemath::Mat4 projectionM = enginemath::Mat4::projectionM(enginemath::toRad(30.0f), 800.0f / 600.0f, 0.1f, 100.0f);
		enginemath::Mat4 viewM = enginemath::Mat4::lookAtM(cameraPos, cameraPos + cameraFront, cameraUp);

		enginemath::Vec3 lightDir(-1.0f, 0.0f, 0.0f);

		cube.bind();
		lightingShader.use();

		lightingShader.setInt("material.diffuse", 0);
		lightingShader.setInt("material.specular", 1);
		lightingShader.setFloat("material.shininess", 32.0f);

		texture1.bind(0);
		texture2.bind(1);

		lightingShader.setVec3("lights.direction", lightDir);
		lightingShader.setVec3("viewPos", cameraPos);

		lightingShader.setVec3("lights.ambient",  enginemath::Vec3(0.2f, 0.2f, 0.2f));
		lightingShader.setVec3("lights.diffuse",  enginemath::Vec3(0.5f, 0.5f, 0.5f));
		lightingShader.setVec3("lights.specular", enginemath::Vec3(1.0f, 1.0f, 1.0f));
	
		enginemath::Mat4 modelM = enginemath::Mat4::translationM(cubePositions[0]);
		renderer.setPosition(lightingShader, projectionM, viewM, modelM);
		renderer.draw(cube);

		enginemath::Mat4 modelLS = enginemath::Mat4::translationM(lightDir) * enginemath::Mat4::scaleM(0.1f, 0.1f, 0.1f);
		lightSource.bind();
		lightSourceShader.use();
		lightSourceShader.setVec3("lightColor", lightColour);
		renderer.setPosition(lightSourceShader, projectionM, viewM, modelLS);
		renderer.draw(lightSource);

		renderer.endFrame(window);

	}

	glfwTerminate();
	return 0;
}