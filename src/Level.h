#pragma once
#include "Text.h"

class Level : public Text {
public:
	int level;

	Level();
	~Level();

	void draw();
};