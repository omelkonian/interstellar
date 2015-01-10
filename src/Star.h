#pragma once
// STARS
#define STAR_INITIAL_Z -100
#define STAR_NUMBER 30
#define STAR_SPEED 1.0f

#include "Model.h"

#include "Defines.h"

class Star : public Model {
	const float initialZ = STAR_INITIAL_Z;
	float size;
public:
	Star();
	virtual ~Star();

	void draw();
	void randomize();
};