#pragma once
#include "Text.h"

class Score : public Text {
public:
	int score;

	Score();
	~Score();

	void draw();
};