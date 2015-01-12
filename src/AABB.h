#pragma once
#include "../gl/glm/glm.hpp"
// Axis-aligned bounding box.
class AABB {
public:
	glm::vec3 min;
	glm::vec3 max;
	glm::vec3 minInit;
	glm::vec3 maxInit;
	glm::vec3 *positionBound;
	AABB(glm::vec3 min, glm::vec3 max, glm::vec3 *position);
	AABB(float, float, float, float, float, float);
	//AABB(ObjectModel const &model);
	virtual ~AABB();
	void updateBounds();
	void drawBounds();
	void printBounds();

	bool intersects(AABB *box);
	virtual bool withinBounds(glm::vec3 pos);
};