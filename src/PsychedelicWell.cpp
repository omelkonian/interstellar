#include "PsychedelicWell.h"
#include "visuals.h"
#include "../gl/glm/glm.hpp"
#include "../gl/glut.h" 

#include <iostream>

#define ITEM_NO 30

using namespace std;

PsychedelicWell::PsychedelicWell(glm::vec3 pos) {
	this->position = pos;
	this->boundingBox = new AABB(pos.x + 10, pos.y + 10, pos.z + 20, pos.x - 20, pos.y - 10, pos.z - 10);

	for (int i = 0; i < ITEM_NO; i++) {
		RandomItem *s = new RandomItem();
		s->randomize();
		s->position = this->position;
		randoms.push_back(s);
	}
}

PsychedelicWell::~PsychedelicWell() {}

void PsychedelicWell::draw() {
	glPushMatrix();
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	for (RandomItem *random : this->randoms) {
		random->draw();
	}

	glDisable(GL_COLOR_MATERIAL);
	glPopMatrix();
}

bool PsychedelicWell::withinBounds(glm::vec3 pos) {
	if ((pos.x > this->boundingBox->x_max) || (pos.x < this->boundingBox->x_min))
		return false;
	if ((pos.y > this->boundingBox->y_max) || (pos.y < this->boundingBox->y_min))
		return false;
	if ((pos.z > this->boundingBox->z_max) || (pos.z < this->boundingBox->z_min))
		return false;
	return true;
}


void PsychedelicWell::update() {
	if (randoms.empty()) {
		return;
	}
	
	RandomItem * random = randoms.front();
	if (!withinBounds(random->position)) {
		randoms.pop_front();
		delete random;

		RandomItem *s = new RandomItem();
		s->randomize();
		s->position = this->position;
		randoms.push_back(s);
	}
}

