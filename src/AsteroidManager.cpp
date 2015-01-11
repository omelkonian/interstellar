#include "AsteroidManager.h"
#include "visuals.h"
#include <queue>
#include <iostream>

using namespace std;

AsteroidManager::AsteroidManager(char *filename) {
	this->mainModel = new Asteroid(filename);
	this->lastTimestamp = glutGet(GLUT_ELAPSED_TIME) - 2000;
}

AsteroidManager::~AsteroidManager() {
	this->mainModel->freeResources();
	delete this->mainModel;
}

void AsteroidManager::draw() {
	// Generate an asteroid each 2 seconds.
	if (glutGet(GLUT_ELAPSED_TIME) - this->lastTimestamp > 1000)
		this->generate();

	for (Asteroid *asteroid : this->asteroids) 
		asteroid->draw();
}

bool AsteroidManager::withinBounds(glm::vec3 position) {
	if (position.z > Z_MAX + 50)
		return false;
	return true;
}


void AsteroidManager::update() {
	if (asteroids.empty()) {
		return;
	}
	Asteroid * asteroid = asteroids.front();
	if (!withinBounds(asteroid->position)) {
		asteroids.pop_front();
		delete asteroid; 
	}
}

void AsteroidManager::generate() {
	Asteroid * a = new Asteroid(this->mainModel);
	a->randomize();
	asteroids.push_back(a);
	this->lastTimestamp = glutGet(GLUT_ELAPSED_TIME);
}