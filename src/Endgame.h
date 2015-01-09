#pragma once

#include "../gl/glm/glm.hpp"
#include "../gl/glut.h"  
#include "visuals.h"
#include "PsychedelicWell.h"
#include "Text.h"

class Endgame {
public:
	long timeCreated;

	PsychedelicWell *well;
	Text *text;

	// Lighting parameters.
	GLfloat ambient[3];
	GLfloat diffuse[3];
	GLfloat specular[3];
	GLfloat lightPos[3];

	void updateLighting();

	Endgame(GLfloat ambient[4], GLfloat diffuse[4], GLfloat specular[4], GLfloat lightPos[4]);
	~Endgame();

	long getAge();

	void renderEndgame(Asteroid *md, Sun *sun, StarManager *stars, float rotx, float roty, float zoomIn, float zoomOut);
};