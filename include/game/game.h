#pragma once

#include "../application/application.h"
#include "../window/window.h"
#include "../gameObject/gameObject.h"
#include "../scene/scene.h"
#include "../rendering/renderer/render.h"
#include "../rendering/texture/texture.h"
#include "../camera/camera.h"
#include "../camera/cameraController.h"
#include "../input/keybindings.h"
#include "../input/input.h"
#include <memory>
#include <vector>

struct Game : public Application {
public:
protected:
	Render renderer;
	Scene scene;

	Camera camera;
	CameraMode current = CameraMode::staticCam;
	std::unique_ptr<CameraController> controller = std::make_unique<StaticController>();
	Keybindings<CameraAction> camBinds;

	void onInit() override {
		camBinds.bind(CameraAction::moveForward, GLFW_KEY_W);
		camBinds.bind(CameraAction::moveLeft, GLFW_KEY_A);
		camBinds.bind(CameraAction::moveRight, GLFW_KEY_D);
		camBinds.bind(CameraAction::moveBackward, GLFW_KEY_S);
		controller->setKeybinds(camBinds);

		windows.push_back(std::make_unique<Window>(640, 480, "game"));

		auto cube = std::make_unique<GameObject>();
		cube->shader = std::make_unique<Shader>("basic.vert", "basic.frag");

		// triangle in NDC so it is visible with an identity model and no camera yet
		// Vertex layout: position, normal, texCoords, tangent
		std::vector<Vertex> verts = {
			{{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
			{{ 0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}},
			{{ 0.0f,  0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.5f, 1.0f}, {1.0f, 0.0f, 0.0f}},
		};
		std::vector<unsigned int> indices = { 0, 1, 2 };
		std::vector<std::shared_ptr<Texture>> textures = {};

		cube->mesh = std::make_unique<Mesh>(verts, indices, textures);
		scene.add(std::move(cube));
	}
	void renderInto(Window* w) override {
		// how the game window(s) get rendered
		renderer.draw(scene);
	}

	void onUpdate(float dt) override {
		Input& in = windows[0]->getInput();
		// code for changig camera mode with keybinds
		if (in.isKeyDown(GLFW_KEY_1)) setCameraMode(CameraMode::staticCam);
		if (in.isKeyDown(GLFW_KEY_2)) setCameraMode(CameraMode::keyboard);
		if (in.isKeyDown(GLFW_KEY_3)) setCameraMode(CameraMode::mouse);
		// update camera view
		controller->update(camera, in, dt);
	}
	
private:
	void setCameraMode(CameraMode m) {
		if (m == current) return;
		current = m;
		switch (m) {
			case CameraMode::staticCam: controller = std::make_unique<StaticController>(); break;
			case CameraMode::keyboard: controller = std::make_unique<KeyboardController>(); break;
			case CameraMode::mouse: controller = std::make_unique<MouseController>(); break;
		}
		controller->setKeybinds(camBinds);
	}

};