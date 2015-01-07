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
	// Position in [(-100,-100), (100,100)]
	this->position = { randFloat(-10.0, 10.0), randFloat(-10.0, 10.0), -50.0 };
	
	// Size: Scale factor in [5,8]
	this->scaleFactor += randFloat(0.4, 5.0);

	// Shape
	this->scaleFactorX = randFloat(0.3, 3);
	this->scaleFactorY = randFloat(0.3, 3);
	this->scaleFactorZ = randFloat(0.3, 3);

	// Surface(optional)
}

AABB* Asteroid::getAABB() {
	float x_max = X_MIN, y_max = Y_MIN, z_max = Z_MIN, x_min = X_MAX, y_min = Y_MAX, z_min = Z_MAX;

	for (int i = 0; i < this->vertices * 3; i += 3) {
		glm::vec3 vertex = { this->_vertices[i], this->_vertices[i + 1], this->_vertices[i + 2] };
		
		float x = vertex.x + this->position.x;
		float y = vertex.y + this->position.y;
		float z = vertex.z + this->position.z;

		if (x > x_max) x_max = x;
		if (x < x_min) x_min = x;
		if (y > y_max) y_max = y;
		if (y < y_min) y_min = y;
		if (z > z_max) z_max = z;
		if (z < z_min) z_min = z;
	}

	x_max *= scaleFactor*scaleFactorX;
	x_min *= scaleFactor*scaleFactorX;
	y_max *= scaleFactor*scaleFactorY;
	y_min *= scaleFactor*scaleFactorY;
	z_max *= scaleFactor*scaleFactorZ;
	z_min *= scaleFactor*scaleFactorZ;

	return new AABB(x_max, y_max, z_max, x_min, y_min, z_min);
}