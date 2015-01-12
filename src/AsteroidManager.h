#pragma once
#include "Asteroid.h"
#include "Score.h"
#include <deque>

class AsteroidManager {
public:
	std::deque<Asteroid*> asteroids;
	Asteroid *mainModel; // Only for copying, not displaying
	Score *currentScore;

	float asteroidSpeed;

	long lastTimestamp;

	AsteroidManager(char *filename, Score *scorePtr);
	~AsteroidManager();
	void generate();
	void draw();
	void update();

private:
	bool withinBounds(glm::vec3 position);
};