#include "Spaceship.h"
#include <iostream>

Spaceship::Spaceship(GLdouble look) : Model(), look(look)
{
	this->ship = new ObjectModel("resources/spaceship.obj");
	this->torus = new ObjectModel("resources/torus.obj");
	this->torus2 = new ObjectModel("resources/torus.obj");
	this->torus->rspeed = { 0, 0, 0.05f };
	this->torus2->rspeed = { 0, 0, -0.05f };
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
	glScalef(0.7,0.7,0.7);
	this->ship->draw();
	glPopMatrix();

	glPushMatrix();
	glScalef(5, 5, 5); // make torus big enough to surround ship
	this->torus->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, 0.0, -3);
	glScalef(5, 5, 5); // make torus big enough to surround ship
	this->torus2->draw();
	glPopMatrix();

	glPopMatrix();
}

AABB* Spaceship::getAABB() {
	float x = position.x, y = position.y, z = position.z;
	return new AABB(x + 4, y + 4, z + 3, x - 4, y - 4, z - 4);
}

void Spaceship::animate() {

}

void Spaceship::printPosition() {
	printf("Space Position: %f %f %f \n", position.x, position.y, position.z);
}

void Spaceship::doPhysics() {
	//bind within a square defined in the header
	Model::doPhysics();
	if (this->position.x >= SPACESHIP_X) {
		this->position.x = SPACESHIP_X;
		this->speed.x = 0;
	}
	else if (this->position.x <= -SPACESHIP_X) {
		this->position.x = -SPACESHIP_X;
		this->speed.x = 0;
	}
	if (this->position.y >= SPACESHIP_Y) {
		this->position.y = SPACESHIP_Y;
		this->speed.y = 0;
	}
	else if (this->position.y <= -SPACESHIP_Y) {
		this->position.y = -SPACESHIP_Y;
		this->speed.y = 0;
	}
	if (this->look != 0.0f) {
		//this->rposition.y = sin(this->position.x / this->look * 1000) * 10;
		//this->rposition.x = sin(this->position.y / this->look * 1000) * 10;
	}
}