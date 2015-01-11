#pragma once


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