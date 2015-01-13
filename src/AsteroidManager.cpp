#include "AsteroidManager.h"
#include "visuals.h"
#include <queue>
#include <iostream>

using namespace std;

AsteroidManager::AsteroidManager(char *filename, Score *scorePtr) {
	this->mainModel = new Asteroid(filename);
	this->lastTimestamp = glutGet(GLUT_ELAPSED_TIME) - ASTEROID_INITIAL_GEN_FREQUENCY;
	this->asteroidSpeed = ASTEROID_INITIAL_SPEED;
	this->genFrequency = ASTEROID_INITIAL_GEN_FREQUENCY;
	this->asteroidsPerGen = 1;
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

	glColor4f(0.5, 0.5, 0.5, 1);

	for (Asteroid *asteroid : this->asteroids) 
		asteroid->draw();

	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
}

bool AsteroidManager::withinBounds(glm::vec3 position) {
	if (position.z > Z_MAX)
		return false;
	return true;
}


void AsteroidManager::update() {
	if (glutGet(GLUT_ELAPSED_TIME) - this->lastTimestamp > this->genFrequency)
		this->generate(this->asteroidsPerGen);

	if (!asteroids.empty()) {
		Asteroid * asteroid = asteroids.front();
		if (!withinBounds(asteroid->position)) {
			this->currentScore->score += asteroid->getScore();
			asteroids.pop_front();
			delete asteroid;
		}
	}
}

void AsteroidManager::generate(int times) {
	for (int i = 0; i < times; i++) {
		Asteroid * a = new Asteroid(*this->mainModel);
		a->randomize();
		a->updateBounds();
		a->speed = { 0, 0, this->asteroidSpeed };
		asteroids.push_back(a);
		this->lastTimestamp = glutGet(GLUT_ELAPSED_TIME);
	}
}

void AsteroidManager::drawBounds() {
	for (Asteroid *a : this->asteroids) {
		a->doPhysics();
		a->drawBounds();
	}
}