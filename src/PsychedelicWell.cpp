#include "PsychedelicWell.h"
#include "visuals.h"
#include "../gl/glm/glm.hpp"
#include "../gl/glut.h" 

#include <iostream>

using namespace std;

PsychedelicWell::PsychedelicWell(glm::vec3 pos) : position(pos), AABB({ 40, 40, 40 }, {-40,-40,-40}, &position) {
	for (int i = 0; i < RANDOM_ITEM_NO; i++) {
		RandomItem *s = new RandomItem();
		s->randomize();
		s->position = this->position;
		randoms.push_back(s);
	}
}

PsychedelicWell::~PsychedelicWell() {
	randoms.erase(randoms.begin(), randoms.end());
}

void PsychedelicWell::draw() {
	glPushMatrix();
	//glDisable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	for (RandomItem *random : this->randoms) 
		random->draw();

	glDisable(GL_COLOR_MATERIAL);
	//glDisable(GL_LIGHTING);
	glPopMatrix();
}

bool PsychedelicWell::withinBounds(glm::vec3 pos) {
	if ((pos.x > this->max.x) || (pos.x < this->min.x))
		return false;
	if ((pos.y > this->max.y) || (pos.y < this->min.y))
		return false;
	if ((pos.z > this->max.z) || (pos.z < this->min.z))
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

