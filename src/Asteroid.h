#pragma once

#include "ObjectModel.h"
#include "AABB.h"

class Asteroid : public ObjectModel {
public:
	float scaleFactorX;
	float scaleFactorY;

	void randomize();
	void draw();
	void printPosition();

	Asteroid(const char * file);
	Asteroid(Asteroid *cpy); // copy constructor
	virtual ~Asteroid();
};