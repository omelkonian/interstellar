#include <cstdlib>
#include "Asteroid.h"

Asteroid::Asteroid(const char * file) : ObjectModel(file) 
{
	this->scaleFactor = 1;
}

Asteroid::~Asteroid() {}

void Asteroid::draw() {
	glPushMatrix();
	glScalef(this->scaleFactor, this->scaleFactor, this->scaleFactor);
	ObjectModel::draw();
	glPopMatrix();
}

float rand_FloatRange(float a, float b)
{
	return ((b - a)*((float)rand() / RAND_MAX)) + a;
}

void Asteroid::randomize() 
{
	// Position in [(-100,-100), (100,100)]
	this->position = { rand_FloatRange(-10.0, 10.0), rand_FloatRange(-10.0, 10.0), -50.0 };
	
	// Size: Scale factor in [5,8]
	this->scaleFactor += rand_FloatRange(0.0, 10.0);

	// Geometry

	// Color

	// Speed

}