#pragma once

#include "ObjectModel.h"
#include "AABB.h"

class Asteroid : public ObjectModel {
	/*AABB asteroidBox;*/
public:
	float scaleFactor;
	float scaleFactorX;
	float scaleFactorY;
	float scaleFactorZ;

	void randomize();
	void draw();
	void printPosition();

	Asteroid(const char * file);
	virtual ~Asteroid();
};