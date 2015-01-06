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
	//printf("Spaceship_pos = {%f,%f,%f}\n", this->position.x, this->position.y, this->position.z);
	glPushMatrix();
		glTranslatef(this->position.x, this->position.y, this->position.z);
		glRotatef(180, 0, 1, 0);
		this->ship->draw();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(this->position.x, this->position.y, this->position.z);
		glScalef(5, 5, 5); // make torus big enough to surround ship
		this->torus->draw();
	glPopMatrix();
}

void Spaceship::animate() {

}
