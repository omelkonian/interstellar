#include "Star.h"
#include "visuals.h"
#include <iostream>

using namespace std;

Star::Star() : Model() {
	float angle = randFloat(-4.0, 4.0);
	this->size = randFloat(0.01, 0.3);
	this->acceleration = { 0.00001 * cos(angle), 0.00001 * sin(angle), 0 };
	this->position.z = STAR_INITIAL_Z;
	this->speed = { STAR_SPEED * cos(angle), STAR_SPEED * sin(angle), 0.001f };
}	

Star::~Star() {}
	
void Star::draw() {
	glPushMatrix();
	Model::draw();

	glDisable(GL_LIGHTING);
	glColor3f(1, 1, 1);

	glutSolidSphere(this->size, 50, 50);

	glEnable(GL_LIGHTING);

	glPopMatrix();
}

void Star::randomize() {}