#include <cstdlib>
#include "Asteroid.h"
#include "visuals.h"

#include <iostream>

using namespace std;

Asteroid::Asteroid(Asteroid *cpy) : ObjectModel(cpy)
{
	this->scaleFactorX = 1;
	this->scaleFactorY = 1;
}

Asteroid::Asteroid(const char * file) : ObjectModel(file) 
{
	this->scaleFactorX = 1;
	this->scaleFactorY = 1;
}

Asteroid::~Asteroid() {}

void Asteroid::draw() {
	glPushMatrix();
	glScalef(this->scaleFactorX, this->scaleFactorY, 1);
	ObjectModel::draw();
	glPopMatrix();
}

void Asteroid::randomize() {
	// Shape
	this->scaleFactorX = randFloat(1, 10);
	this->scaleFactorY = randFloat(1, 10);

	// Position in spaceship's movement boundaries.
	float boundX = SPACESHIP_X * (1.0 / (this->scaleFactorX));
	float boundY = SPACESHIP_Y * (1.0 / (this->scaleFactorY));
	this->position = { randFloat(-boundX, boundX), randFloat(-boundY, boundY), -100.0 };

	// Rotation Speed
	this->rspeed = { 0, -0.5, 0.5 };
}

int Asteroid::getScore() {
	return 10 * this->scaleFactorX + 10 * this->scaleFactorY;
}

void Asteroid::printPosition() {
	printf("Asteroid Position: %f %f %f \n", position.x, position.y, position.z);
}