#include <cstdlib>
#include "Asteroid.h"
#include "visuals.h"

#include <iostream>

using namespace std;

Asteroid::Asteroid(Asteroid const &cpy) : ObjectModel(cpy)
{
	this->positionBound = &this->position;
}

Asteroid::Asteroid(const char * file) : ObjectModel(file) 
{

}

Asteroid::~Asteroid() {}

void Asteroid::draw() {
	glPushMatrix();
	ObjectModel::draw();
	glPopMatrix();
	this->drawBounds();
}

void Asteroid::randomize() {
	// Shape
	this->scale.x = randFloat(1, 10);
	this->scale.y = randFloat(1, 10);
	// Position in spaceship's movement boundaries.
	float boundX = SPACESHIP_X * (1.0 / (this->scale.x));
	float boundY = SPACESHIP_Y * (1.0 / (this->scale.y));
	this->position = { randFloat(-boundX, boundX), randFloat(-boundY, boundY), -100.0 };

	// Rotation Speed
	this->rspeed = { 0, -0.5, 0.5 };
}

int Asteroid::getScore() {
	return 10 * this->scale.x + 10 * this->scale.y;
}

void Asteroid::printPosition() {
	printf("Asteroid Position: %f %f %f \n", position.x, position.y, position.z);
}