#include "Sun.h"
#include <iostream>

using namespace std;

Sun::Sun() {
	this->innerSphere = new ObjectModel("resources/sun.obj", "resources/sun.jpg");

	this->position = { 50, 20, -60.0 };
	this->outerRadiusMin = 21.0;
	this->outerRadiusMax = 23.0;
	this->outerRadius = this->outerRadiusMin;

	this->addition = true;
}

	

Sun::~Sun() {}

void Sun::draw() {
	glPushMatrix();

	glScalef(1.0, 1.1, 1.0);
	glTranslatef(this->position.x, this->position.y, this->position.z);
	
	//Inner Sphere	
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	float mat_specular[] = { 0.992157, 0.941176, 0.807843, 1.0 };
	float mat_emission[] = { 1, 0.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);

	glPushMatrix();
	glEnable(GL_SMOOTH);
	glScalef(20, 20, 20);
	this->innerSphere->draw();
	glDisable(GL_SMOOTH);
	glPopMatrix();

	

	glDisable(GL_COLOR_MATERIAL);

	//Outer Sphere
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glColor4f(0.8, 0.35, 0.0, 0.4 - ((this->outerRadius - this->outerRadiusMin + 1) / this->outerRadiusMax));
	float mat_specular2[] = { 0.992157, 0.941176, 0.807843, 1.0 };
	float mat_emission2[] = { 0.5, 0.5, 0.0, 1.0 };
	float shininess2 = 10;

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular2);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission2);

	glutSolidSphere(this->outerRadius, 300.0, 300.0);	

	glDisable(GL_COLOR_MATERIAL);

	glPopMatrix();
}

void Sun::animate() {
	this->outerRadius += (this->addition) ? 0.03 : -0.03;
	this->addition = (this->outerRadius >= this->outerRadiusMax) ? (false) : ((this->outerRadius <= this->outerRadiusMin) ? (true) : (this->addition));
}

void Sun::print() {
	printf("Position: %f %f %f \n", this->position[0], this->position[1], this->position[2]);
	cout << "Outer radius: " << this->outerRadius << endl;
}