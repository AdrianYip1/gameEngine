#pragma once

#include "gameObject/gameObject.h"
#include <memory>
#include <vector>

class Scene {
public:
	void add(std::unique_ptr<GameObject> obj) {
		objects.push_back(std::move(obj)); }

	std::vector<std::unique_ptr<GameObject>> objects;
};
