#include "Spaceship.h"
#include <iostream>

Spaceship::Spaceship() : Model()
{
	this->ship = new ObjectModel("resources/spaceship.obj");
	this->torus = new ObjectModel("resources/torus.obj");
	this->torus->rspeed = { 0, 0, 0.05f };
}


Spaceship::~Spaceship()
{
	delete this->ship;
	delete this->torus;
}

void Spaceship::draw() 
{	
	glPushMatrix();
	Model::draw();
	glPushMatrix();
		glRotatef(180, 0, 1, 0);
		this->ship->draw();
	glPopMatrix();

	glPushMatrix();
		glScalef(5, 5, 5); // make torus big enough to surround ship
		this->torus->draw();
	glPopMatrix();
	glPopMatrix();
}

AABB* Spaceship::getAABB() {
	float x = position.x, y = position.y, z = position.z;
	return new AABB(x+4,y+4,z+3,x-4,y-4,z-4);
}

void Spaceship::animate() {

}

void Spaceship::printPosition() {
	printf("Space Position: %f %f %f \n", position.x, position.y, position.z);
}