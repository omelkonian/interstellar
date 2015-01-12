#include <cstdlib>
#include "Asteroid.h"
#include "visuals.h"

#include <iostream>

using namespace std;

Asteroid::Asteroid(Asteroid const &cpy) : ObjectModel(cpy)
{
	this->positionBound = &this->position;
	this->timeOld = glutGet(GLUT_ELAPSED_TIME);
}

Asteroid::Asteroid(const char * file) : ObjectModel(file) 
{

}

Asteroid::~Asteroid() {}

void Asteroid::draw() {
	glPushMatrix();
	glColor3f(0.3, 0.15, 0);
	ObjectModel::draw();
	glPopMatrix();
	this->drawBounds();
}

void Asteroid::randomize() {
	// Shape
	this->scale.x = randFloat(2.0, 8.0);
	this->scale.y = randFloat(2.0, 8.0);
	this->scale.z = randFloat(2.0, 8.0);
	// Position in spaceship's movement boundaries.
	float boundX = SPACESHIP_X * (1.0 / (this->scale.x));
	float boundY = SPACESHIP_Y * (1.0 / (this->scale.y));
	this->position = { randFloat(-boundX, boundX), randFloat(-boundY, boundY), -100.0 };

	// Rotation Speed
	this->rspeed = { 0, -0.05, 0.05 };
}

int Asteroid::getScore() {
	return 10 * this->scale.x + 10 * this->scale.y;
}

void Asteroid::printPosition() {
	printf("Asteroid Position: {%.1f,%.1f,%1.f} Speed={%.1f,%.1f,%.1f}", position.x, position.y, position.z,speed.x,speed.y,speed.z);
	printf("Rposition: {%.1f,%.1f,%1.f} Rspeed={%.1f,%.1f,%.1f}\n", rposition.x, rposition.y, rposition.z, rspeed.x, rspeed.y, rspeed.z);
	this->printBounds();
}