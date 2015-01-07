#pragma once

#include <vector>
#include "Star.h"
#include "Defines.h"

class StarManager {
public: 
	Star* stars[STAR_NUMBER];

	StarManager();
	~StarManager();

	void draw();

	void update();
};