#pragma once

#include <vector>
#include <deque>
#include "Star.h"
#include "Defines.h"

class StarManager {
public: 
	std::deque<Star*> stars;
	//Star* stars[STAR_NUMBER];

	StarManager();
	~StarManager();
	void generate(int value);
	void draw();
	void update();
};