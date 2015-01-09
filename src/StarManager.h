#pragma once

#include <deque>
#include "Star.h"
#include "Defines.h"

class StarManager {
public: 
	std::deque<Star*> stars;

	StarManager();
	~StarManager();
	void generate(int value);
	void draw();
	void update();
};