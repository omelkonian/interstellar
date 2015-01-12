#pragma once

#include "ObjectModel.h"
#include "AABB.h"

class Asteroid : public ObjectModel {
public:
	void randomize();
	void draw();
	void printPosition();

	int getScore();

	Asteroid(const char * file);
	Asteroid(Asteroid *cpy); // copy constructor
	Asteroid(const Asteroid &cpy); //correct copy constructor
	virtual ~Asteroid();
};