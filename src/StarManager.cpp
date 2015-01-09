#include "StarManager.h"
#include "visuals.h"
#include <queue>
#include <iostream>

using namespace std;

StarManager::StarManager() {
	//for (int i = 0; i < STAR_NUMBER; i++) {
	//	this->stars[i] = new Star();
	//	this->stars[i]->randomize();
	//}
}

StarManager::~StarManager() {}

void StarManager::draw() {
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	
	for (Star *star : this->stars) {
		star->draw();
	}
	
	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
}

bool withinBounds(glm::vec3 position) {
	if ((position.x > X_MAX) || (position.x < X_MIN))
		return false;
	if ((position.y > Y_MAX) || (position.y < Y_MIN))
		return false;
	if ((position.z > Z_MAX) || (position.z < Z_MIN))
		return false;
	return true;
}


void StarManager::update() {
	if (stars.empty()) {
		return;
	}
	Star * star = stars.front();
	if (!withinBounds(star->position)) {
		stars.pop_front();
		delete star;
	}
}

void StarManager::generate(int value) {
		Star * s = new Star();
		stars.push_back(s);
}
