#include "Star.h"
#include "visuals.h"
#include <iostream>

using namespace std;

Star::Star() : Model() {
	float angle = randFloat(-4.0, 4.0);
	this->size = randFloat(0.05, 0.2);
	this->position.z = STAR_INITIAL_Z;
	this->speed = { STAR_SPEED * cos(angle), STAR_SPEED * sin(angle), 1.0f };
}	

Star::~Star() {}
	
void Star::draw() {
	glPushMatrix();
	Model::draw();

	//glColor3f(1, 1, 1);
	//glColor3f(randFloat(0, 1), randFloat(0, 1), randFloat(0, 1));

	int gen = rand() % 3;
	switch (gen) {
	case 0: // red
		glColor3f(1, 0, 0);
		break;
	case 1: // yellow
		glColor3f(1, 1, 0);
		break;
	case 2: // orange
		glColor3f(1, 0.5, 0);
		break;
	}

	glutSolidSphere(this->size, 50, 50);

	glPopMatrix();
}

void Star::randomize() {


	//this->position = { randFloat(X_MIN, X_MAX), randFloat(X_MIN, X_MAX), this->initialZ };
	//this->speed = { randFloat(-0.1, 0.1), randFloat(-0.1, 0.1), randFloat(0.05, 0.1) };
	//this->acceleration = { 0, 0, 0 };
}