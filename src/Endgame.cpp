#include "Endgame.h"

Endgame::Endgame(GLfloat ambientLight[4], GLfloat diffuseLight[4], GLfloat specularLight[4], GLfloat lightPos[4]) {
	this->ambient[0] = ambientLight[0]; this->ambient[1] = ambientLight[1]; this->ambient[2] = ambientLight[2];
	this->diffuse[0] = diffuseLight[0]; this->diffuse[1] = diffuseLight[1]; this->diffuse[2] = diffuseLight[2];
	this->specular[0] = specularLight[0]; this->specular[1] = specularLight[1]; this->specular[2] = specularLight[2];
	this->lightPos[0] = lightPos[0]; this->lightPos[1] = lightPos[1]; this->lightPos[2] = lightPos[2];
}

Endgame::~Endgame() {}

void Endgame::updateLighting() {
	float dec = 0.005;
	this->ambient[0] -= dec; this->ambient[1] -= dec; this->ambient[2] -= dec;
	this->diffuse[0] -= dec; this->diffuse[1] -= dec; this->diffuse[2] -= dec;
	this->specular[0] -= dec; this->specular[1] -= dec; this->specular[2] -= dec;
	this->lightPos[0] -= dec; this->lightPos[1] -= dec; this->lightPos[2] -= dec;
}

void Endgame::renderEndgame(Asteroid *md, Sun *sun, StarManager *stars, float rotx, float roty, float zoomIn, float zoomOut) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window and the depth buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0, 0, -30); // Move camera a bit back.

	glTranslatef(0, 0, zoomIn);
	glTranslatef(0, 0, -zoomOut);

	glRotatef(rotx, 1, 0, 0);
	glRotatef(roty, 0, 1, 0);

	// Asteroid && ship.
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glColor4f(0.1, 0.1, 0.1, 1);
	float mat_specular[] = { 0.992157, 0.941176, 0.807843, 1.0 };
	float mat_emission[] = { 0.0, 0.0, 0.0, 1.0 };
	float shininess = 10;

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);

	md->draw();

	if (this->getAge() > 2000) {
		glEnable(GL_LIGHT0);
		this->text->draw();
		glDisable(GL_LIGHT0);
	}

	glDisable(GL_COLOR_MATERIAL);

	sun->draw();

	stars->draw();

	this->well->draw();


	glutSwapBuffers();
}

long Endgame::getAge() {
	return glutGet(GLUT_ELAPSED_TIME) - this->timeCreated;
}