#include <cstdlib>
#include "Asteroid.h"
#include "visuals.h"

#include <iostream>

using namespace std;

Asteroid::Asteroid(const char * file) : ObjectModel(file) 
{
	this->scaleFactor = 1;
	this->scaleFactorX = 1;
	this->scaleFactorY = 1;
	this->scaleFactorZ = 1;
}

Asteroid::~Asteroid() {}

void Asteroid::draw() {
	glPushMatrix();
	glScalef(this->scaleFactor, this->scaleFactor, this->scaleFactor);
	glScalef(this->scaleFactorX, this->scaleFactorY, this->scaleFactorZ);
	ObjectModel::draw();
	glPopMatrix();
}

void Asteroid::randomize() 
{
	// Position in [(-10,-10), (10,10)]
	this->position = { randFloat(-1.0, 1.0), randFloat(-1.0, 1.0), -50.0 };
	
	// Size: Scale factor in [5,8]
	this->scaleFactor += randFloat(0.4, 5.0);

	// Shape
	this->scaleFactorX = randFloat(0.3, 3);
	this->scaleFactorY = randFloat(0.3, 3);
	this->scaleFactorZ = randFloat(0.3, 3);
}

void Asteroid::printPosition() {
	printf("Asteroid Position: %f %f %f \n", position.x, position.y, position.z);
}