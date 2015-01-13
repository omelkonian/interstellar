#pragma once

#include "../gl/glm/glm.hpp"
#include "../gl/glut.h"  
#include "visuals.h"
#include "PsychedelicWell.h"
#include "Text.h"
#include "AsteroidManager.h"
#include "Environment.h"
#include "Level.h"
#include "Score.h"

class Endgame {
public:
	long timeCreated;

	PsychedelicWell *well;
	Text *gameOverText;
	Text *quitText;
	Text *restartText;

	// Lighting parameters.
	GLfloat ambient[3];
	GLfloat diffuse[3];
	GLfloat specular[3];
	GLfloat lightPos[3];

	int timesDarkened;

	void updateLighting();

	Endgame(GLfloat ambient[4], GLfloat diffuse[4], GLfloat specular[4], GLfloat lightPos[4]);
	~Endgame();

	long getAge();

	void renderEndgame(AsteroidManager *md, Sun *sun, StarManager *stars, float rotx, float roty, float zoomIn, float zoomOut, Environment *env, Level *level, Score *score);

	void restart();
};