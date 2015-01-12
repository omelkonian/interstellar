#pragma once
#include "Score.h"

class LevelManager {
public:
	int currentLevel;
	Score *currentScore;

	LevelManager(Score *scorePtr);
	~LevelManager();

	void update();
};