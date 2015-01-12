#include "LevelManager.h"

LevelManager::LevelManager(Score *scorePtr) {
	this->currentScore = scorePtr;
	this->currentLevel = 1;
}

LevelManager::~LevelManager() {}

void LevelManager::update() {
	this->currentLevel++;
}