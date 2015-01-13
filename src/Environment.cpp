#include "Environment.h"


Environment::Environment() : ObjectModel("resources/environment.obj","resources/universe.png")
{
	this->position = { 5, 5, -10 };
	this->scale = { 500, 500, 500 };
	this->rposition = { 0, 180, 0 };
}


Environment::~Environment()
{
	
}

void Environment::draw() {
	glPushMatrix();
	glColor3f(0.6, 0.6, 0.6);
	ObjectModel::draw();
	glPopMatrix();
}
