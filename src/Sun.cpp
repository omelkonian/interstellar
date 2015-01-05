#include "Sun.h"
#include <iostream>

using namespace std;

Sun::Sun() {
	this->position = { 150.0, 50.0, -100.0 };
	this->innerRadius = 25.0;
	this->outerRadiusMin = 28.0;
	this->outerRadiusMax = 30.0;
	this->outerRadius = this->outerRadiusMin;

	this->addition = true;
}

	

Sun::~Sun() {}

void Sun::draw() {
	glScalef(1.0, 1.1, 1.0);
	glTranslatef(this->position[0], this->position[1], this->position[2]);
	
	//Inner Sphere	
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glColor4f(1.0, 0.45, 0.0, 1.0);
	float mat_specular[] = { 0.992157, 0.941176, 0.807843, 1.0 };
	float mat_emission[] = { 0.0, 0.0, 0.0, 1.0 };
	float shininess = 10;

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);

	glPushMatrix();
	glutSolidSphere(this->innerRadius, 10000.0, 10000.0);
	glPopMatrix();

	glDisable(GL_COLOR_MATERIAL);

	//Outer Sphere
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glColor4f(0.8, 0.35, 0.0, 1/(this->outerRadius - this->innerRadius));
	float mat_specular2[] = { 0.992157, 0.941176, 0.807843, 1.0 };
	float mat_emission2[] = { 0.5, 0.5, 0.0, 1.0 };
	float shininess2 = 10;

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular2);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess2);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission2);

	glPushMatrix();
	glutSolidSphere(this->outerRadius, 10000.0, 10000.0);
	glPopMatrix();

	glDisable(GL_COLOR_MATERIAL);
}

void Sun::animate() {
	this->outerRadius += (this->addition) ? 0.01 : -0.01;
	this->addition = (this->outerRadius >= this->outerRadiusMax) ? (false) : ((this->outerRadius <= this->outerRadiusMin) ? (true) : (this->addition));
}

void Sun::print() {
	printf("Position: %f %f %f \n", this->position[0], this->position[1], this->position[2]);
	cout << "Inner radius: " << this->innerRadius << endl;
	cout << "Outer radius: " << this->outerRadius << endl;
}