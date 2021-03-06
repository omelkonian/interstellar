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
	void generate(glm::vec3 spaceshipPos);
	void draw();
	void update(glm::vec3 spaceshipPos);

	void levelUp(int level);

	void erase();

	void drawBounds();

private:
	bool withinBounds(glm::vec3 position);
};