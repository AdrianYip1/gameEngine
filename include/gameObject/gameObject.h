#pragma once

#include <memory>

struct GameObject {
public:
	virtual void draw() = 0;
};

class Cube : public GameObject {
	void draw() override {

	}
};