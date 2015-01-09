#pragma once

#include "Model.h"

class RandomItem : public Model {
public:
	glm::vec3 color;
	int shape;

	RandomItem();
	~RandomItem();

	void draw();
	void randomize();
};