#pragma once
#include "Asteroid.h"
#include <deque>

class AsteroidManager {
public:
	std::deque<Asteroid*> asteroids;
	Asteroid *mainModel; // Only for copying, not displaying

	long lastTimestamp;

	AsteroidManager(char *filename);
	~AsteroidManager();
	void generate();
	void draw();
	void update();

private:
	bool withinBounds(glm::vec3 position);
};