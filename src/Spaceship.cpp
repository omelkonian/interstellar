#include "Spaceship.h"


Spaceship::Spaceship() : Model()
{
	this->ship = new ObjectModel("resources/spaceship.obj");
	this->torus = new ObjectModel("resources/torus.obj");
	this->torus->rspeed = { 0, 0, 0.5f };
}


Spaceship::~Spaceship()
{
	delete this->ship;
	delete this->torus;
}

void Spaceship::draw() 
{
	this->ship->draw();
	this->torus->draw();
}

void Spaceship::animate() {

}
