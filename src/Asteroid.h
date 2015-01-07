#pragma once

#include "ObjectModel.h"
#include "AABB.h"

class Asteroid : public ObjectModel {
public:
	float scaleFactor;
	float scaleFactorX;
	float scaleFactorY;
	float scaleFactorZ;

	void randomize();
	void draw();

	Asteroid(const char * file);
	virtual ~Asteroid();

	AABB* getAABB();
};