#pragma once

#include "ObjectModel.h"

class Asteroid : public ObjectModel {
public:
	float scaleFactor;

	void randomize();
	void draw();

	Asteroid(const char * file);
	virtual ~Asteroid();


};