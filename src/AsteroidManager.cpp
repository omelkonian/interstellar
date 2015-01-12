#include "AsteroidManager.h"
#include "visuals.h"
#include <queue>
#include <iostream>

using namespace std;

AsteroidManager::AsteroidManager(char *filename, Score *scorePtr) {
	this->mainModel = new Asteroid(filename);
	this->lastTimestamp = glutGet(GLUT_ELAPSED_TIME) - 2000;
	this->asteroidSpeed = ASTEROID_INITIAL_SPEED;
	this->currentScore = scorePtr;
}

AsteroidManager::~AsteroidManager() {
	this->mainModel->freeResources();
	delete this->mainModel;
}

void AsteroidManager::draw() {
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	float mat_specular[] = { 1, 1, 1, 1.0 };
	float mat_emission[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);

	glColor4f(0.1, 0.1, 0.1, 1);

	// Generate an asteroid each 2 seconds.
	if (glutGet(GLUT_ELAPSED_TIME) - this->lastTimestamp > 2000)
		this->generate();

	for (Asteroid *asteroid : this->asteroids) {
		asteroid->draw();
		asteroid->printBounds();
	}

	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
}

bool AsteroidManager::withinBounds(glm::vec3 position) {
	if (position.z > Z_MAX) 
		return false;
	return true;
}


void AsteroidManager::update() {
	if (asteroids.empty()) {
		return;
	}
	Asteroid * asteroid = asteroids.front();
	if (!withinBounds(asteroid->position)) {
		this->currentScore->score += asteroid->getScore();
		asteroids.pop_front();
		delete asteroid; 
	}
}

void AsteroidManager::generate() {
	Asteroid * a = new Asteroid(*this->mainModel);
	a->randomize();
	a->updateBounds();
	a->speed = { 0, 0, this->asteroidSpeed };
	asteroids.push_back(a);
	this->lastTimestamp = glutGet(GLUT_ELAPSED_TIME);
}