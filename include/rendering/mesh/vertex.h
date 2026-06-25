#pragma once

#include <enginemath/vec2.hpp>
#include <enginemath/vec3.hpp>

struct Vertex {
	enginemath::Vec3 position;
	enginemath::Vec3 normal;
	enginemath::Vec2 texCoords;
	enginemath::Vec3 tangent;
};