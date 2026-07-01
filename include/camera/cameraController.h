#pragma once

#include <glad/glad.h>
#include <camera/camera.h>
#include <input/input.h>
#include <input/keybindings.h>

enum class CameraAction {
	moveForward,
	moveBackward,
	moveRight,
	moveLeft,
	
	zoomIn,
	zoomOut,

	turnPitchUp,
	turnPitchDown,
	turnYawLeft,
	turnYawRight,
	turnRollLeft,
	turnRollRight
};

enum class CameraMode {
	staticCam,
	keyboard,
	mouse
};

struct CameraController {
public:
	virtual ~CameraController() = default;
	virtual void update(Camera& camera, const Input& in, float dt) = 0;
	void setKeybinds(const Keybindings<CameraAction>& kb) { keybinds = kb; }

protected:
	Keybindings<CameraAction> keybinds;
};

struct MouseController : CameraController {
	void update(Camera& camera, const Input& in, float dt) override {

	}
};

struct KeyboardController : CameraController {
	void update(Camera& camera, const Input& in, float dt) override {

	}
};

struct StaticController : CameraController {
	void update(Camera& camera, const Input& in, float dt) override {

	}
};