#pragma once
#include "Asteroid.h"
#include "Score.h"
#include <deque>

class AsteroidManager {
public:
	std::deque<Asteroid*> asteroids;
	Asteroid *mainModel; // Only for copying, not displaying
	Score *currentScore;

	int asteroidsPerGen;
	float asteroidSpeed;
	int genFrequency;

	long lastTimestamp;

	AsteroidManager(char *filename, Score *scorePtr);
	~AsteroidManager();
	void generate(int times);
	void draw();
	void update();

	void drawBounds();

private:
	bool withinBounds(glm::vec3 position);
};