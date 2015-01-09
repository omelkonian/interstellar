#pragma once

#include <deque>
#include "RandomItem.h"

class PsychedelicWell {
	std::deque<RandomItem*> randoms;
	AABB *boundingBox;
	glm::vec3 position;

	bool withinBounds(glm::vec3 position);
public:
	PsychedelicWell(glm::vec3 position);
	~PsychedelicWell();

	void draw();
	void update();
};