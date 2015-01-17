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

Asteroid::Asteroid(const char * file) : ObjectModel(file, "resources/rock.jpg")
{

}

Asteroid::~Asteroid() {}

void Asteroid::draw() {
	glPushMatrix();
	ObjectModel::draw();
	glPopMatrix();
}

void Asteroid::randomize() {
	// Shape
	this->scale.x = randFloat(2.0, 12.0);
	this->scale.y = randFloat(2.0, 12.0);
	this->scale.z = randFloat(2.0, 12.0);
	// Position in spaceship's movement boundaries.
	float boundX = SPACESHIP_X + 5;
	float boundY = SPACESHIP_Y + 5;
	this->position = { randFloat(-boundX, boundX), randFloat(-boundY, boundY), -100.0 };

	// Rotation Speed
	float genRot = randFloat(0.01, 0.1);
	this->rspeed = { 0, -genRot, genRot };

	this->maxInit *= this->scale;
	this->minInit *= this->scale;
}

int Asteroid::getScore() {
	return 10 * this->scale.x + 10 * this->scale.y;
}

void Asteroid::printPosition() {
	printf("Asteroid Position: {%.1f,%.1f,%1.f} Speed={%.1f,%.1f,%.1f}", position.x, position.y, position.z,speed.x,speed.y,speed.z);
	printf("Rposition: {%.1f,%.1f,%1.f} Rspeed={%.1f,%.1f,%.1f}\n", rposition.x, rposition.y, rposition.z, rspeed.x, rspeed.y, rspeed.z);
	this->printBounds();
}