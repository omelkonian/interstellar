#include "Star.h"
#include "visuals.h"
#include <iostream>

using namespace std;

Star::Star() : Model() {
	this->size = randFloat(0.05, 0.2);
}	

Star::~Star() {}
	
void Star::draw() {
	glPushMatrix();
	Model::draw();

	glColor3f(1, 1, 1);
	glutSolidSphere(this->size, 500, 500);

	glPopMatrix();
}

void Star::randomize() {
	this->position = { randFloat(X_MIN, X_MAX), randFloat(X_MIN, X_MAX), this->initialZ };
	this->speed = { randFloat(-0.1, 0.1), randFloat(-0.1, 0.1), randFloat(0.05, 0.1) };
	this->acceleration = { 0, 0, 0 };
}