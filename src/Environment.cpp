#include "Environment.h"


Environment::Environment() : ObjectModel("resources/environment.obj","resources/background4.jpg")
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
	glDisable(GL_LIGHTING);
	glTranslatef(0, 0, -500);
	glColor3f(0.6, 0.6, 0.6);
	ObjectModel::draw();
	glEnable(GL_LIGHTING);
	glPopMatrix();
}
