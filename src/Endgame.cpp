#include "Endgame.h"

Endgame::Endgame(GLfloat ambientLight[4], GLfloat diffuseLight[4], GLfloat specularLight[4], GLfloat lightPos[4]) {
	this->ambient[0] = ambientLight[0]; this->ambient[1] = ambientLight[1]; this->ambient[2] = ambientLight[2];
	this->diffuse[0] = diffuseLight[0]; this->diffuse[1] = diffuseLight[1]; this->diffuse[2] = diffuseLight[2];
	this->specular[0] = specularLight[0]; this->specular[1] = specularLight[1]; this->specular[2] = specularLight[2];
	this->lightPos[0] = lightPos[0]; this->lightPos[1] = lightPos[1]; this->lightPos[2] = lightPos[2];
	this->timesDarkened = 0;

	this->quitText = new Text("Press Escape to quit game.", TEXT_SIZE, { -SPACESHIP_X, -SPACESHIP_Y, TEXT_Z });
	this->restartText = new Text("Press R to restart game.", TEXT_SIZE, { -SPACESHIP_X, -SPACESHIP_Y + 3, TEXT_Z });
}

Endgame::~Endgame() {
	delete this->quitText;
	delete this->restartText;
	delete this->gameOverText;
	delete this->well;
}

void Endgame::updateLighting() {
	float dec = DARKEN_DECREMENT;
	if (this->timesDarkened++ < DARKEN_TIMES) {
		this->ambient[0] -= dec; this->ambient[1] -= dec; this->ambient[2] -= dec;
		this->diffuse[0] -= dec; this->diffuse[1] -= dec; this->diffuse[2] -= dec;
		this->specular[0] -= dec; this->specular[1] -= dec; this->specular[2] -= dec;
		this->lightPos[0] -= dec; this->lightPos[1] -= dec; this->lightPos[2] -= dec;
	}
}

void Endgame::renderEndgame(AsteroidManager *md, Sun *sun, StarManager *stars, float rotx, float roty, float zoomIn, float zoomOut, Environment *env, Level *level, Score *score) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window and the depth buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0, 0, -30); // Move camera a bit back.

	level->draw();
	score->draw();
	this->quitText->draw();
	this->restartText->draw();


	glTranslatef(0, 0, zoomIn);
	glTranslatef(0, 0, -zoomOut);

	glRotatef(rotx, 1, 0, 0);
	glRotatef(roty, 0, 1, 0);

	env->draw();

	// Asteroid && ship.
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glColor4f(0.1, 0.1, 0.1, 1);
	float mat_specular[] = { 0.992157, 0.941176, 0.807843, 1.0 };
	float shininess = 10;

	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	md->draw();

	if (this->getAge() > 2000) {
		this->gameOverText->draw();
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

void Endgame::restart() {
	Setup();
}
