#pragma once

#include <deque>
#include "RandomItem.h"
#include "AABB.h"

class PsychedelicWell : public AABB {
	std::deque<RandomItem*> randoms;
	glm::vec3 position;

	int generated;

	bool withinBounds(glm::vec3 position);
public:
	PsychedelicWell(glm::vec3 position);
	~PsychedelicWell();

	void draw();
	void update();
};