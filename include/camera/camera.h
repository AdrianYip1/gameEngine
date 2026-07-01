#pragma once

#include <glad/glad.h>
#include <math.h>
#include <enginemath/mathutils.hpp>
#include <enginemath/vec3.hpp>
#include <enginemath/mat4.hpp>

struct Camera {
public:
	enginemath::Vec3 cameraPos;
	enginemath::Vec3 cameraTarget;
	enginemath::Vec3 cameraDir;

	enginemath::Vec3 up = enginemath::Vec3(0.0f, 1.0f, 0.0f);
	enginemath::Vec3 cameraUp = enginemath::Vec3(0.0f, 1.0f, 0.0f);
	enginemath::Vec3 cameraFront = enginemath::Vec3(0.0f, 0.0f, -1.0f);

	enginemath::Mat4 getView(enginemath::Vec3 cameraPos, enginemath::Vec3 cameraTarget, 
							 enginemath::Vec3 up, enginemath::Vec3 cameraFront) {
		return enginemath::Mat4::lookAtM(cameraPos, cameraTarget + cameraFront, up);
	}

	enginemath::Vec3 getDir(float yaw, float pitch, float roll) { 
		//params in degrees, convert with enginemth. roll not used here, but included for future implementation
		enginemath::Vec3 dir;
		dir.x = std::cos(enginemath::toRad(yaw)) * std::cos(enginemath::toRad(pitch));
		dir.y = std::sin(enginemath::toRad(pitch));
		dir.z = std::sin(enginemath::toRad(yaw)) * std::cos(enginemath::toRad(pitch));

		return dir;
	}

	// mouse inputs


};