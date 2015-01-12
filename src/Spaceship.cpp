#include "Spaceship.h"
#include "visuals.h"
#include <iostream>

Spaceship::Spaceship(GLdouble look) : Model(), look(look)
{
	this->ship = new ObjectModel("resources/spaceship.obj");
	this->torus = new ObjectModel("resources/torus.obj");
	this->torus2 = new ObjectModel("resources/torus.obj");
	this->minInit = { -4, -4, -4 };
	this->maxInit = { 4, 4, 4 };
	this->positionBound = &this->position;
	this->ship->scale = { 0.7, 0.7, 0.7 };
	this->torus->scale = this->torus2->scale = { 5, 5, 5 };
	this->torus->rspeed = { 0, 0, 0.05f };
	this->torus2->rspeed = { 0, 0, -0.05f };
	this->torus2->position = { 0.0, 0.0, -3.0 };
}


Spaceship::~Spaceship()
{
	delete this->ship;
	delete this->torus;
}

void Spaceship::draw()
{
	glPushMatrix();

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	float mat_specular[] = { 1, 1, 1, 1.0 };
	float mat_emission[] = { 0.0, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);

	glColor4f(0.2, 0.1, 0.1, 1);

	Model::draw();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	this->ship->draw();
	glPopMatrix();

	glPushMatrix();
	this->torus->draw();
	glPopMatrix();

	glPushMatrix();
	this->torus2->draw();
	glPopMatrix();

	glDisable(GL_COLOR_MATERIAL);
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