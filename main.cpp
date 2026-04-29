#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <enginemath/vec3.hpp>

int main() {

	enginemath::Vec3 a(1, 4, 6);
	enginemath::Vec3 b(4, 6, 2);

	auto c = a + b;
	auto d = a.cross(b);
	auto e = a.dot(b);

	std::cout << c.x << ", " << c.y << ", " << c.z << std::endl;
	std::cout << d.x << ", " << d.y << ", " << d.z << std::endl;
	std::cout << e << std::endl;
	return 0;
}