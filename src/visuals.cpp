#include <stdio.h>     // - Just for some ASCII messages
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../gl/glut.h"   // - An interface and windows management library
#include "visuals.h"   // Header file for our OpenGL functions

// The models of the scene.
Asteroid *md;
Sun *sun;
Spaceship *ship;

// Variables for rotating (up, down, left, right) and zooming in/out (i, o).
static float rotx = 0.0;
static float roty = 0.0;
static float zoomIn = 0.0;
static float zoomOut = 0.0;

// Booleans for animating (rotating) and pausing.
static bool animate = false;
static bool paused = false;

static long oldTime = glutGet(GLUT_ELAPSED_TIME);

using namespace std;

void DrawAxes()
{
	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_LINES);
	glVertex2f(-1000.0, 0.0);
	glVertex2f(1000.0, 0.0);
	glVertex2f(0.0, -1000.0);
	glVertex2f(0.0, 1000.0);
	glVertex3f(0.0, 0.0, -1000.0);
	glVertex3f(0.0, 0.0, 1000.0);
	glEnd();
}

void Render()
{
	if (paused)
		return;
	//CLEARS FRAME BUFFER ie COLOR BUFFER& DEPTH BUFFER (1.0)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
	// and the depth buffer
	glMatrixMode(GL_MODELVIEW);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLoadIdentity();

	glTranslatef(0, 0, -100);

	glTranslatef(0, 0, zoomIn);
	glTranslatef(0, 0, -zoomOut);

	glRotatef(rotx, 1, 0, 0);
	glRotatef(roty, 0, 1, 0);
	DrawAxes();

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
	ship->draw();

	glDisable(GL_COLOR_MATERIAL);

	sun->draw();

	glutSwapBuffers();             // All drawing commands applied to the 
	// hidden buffer, so now, bring forward
	// the hidden buffer and hide the visible one
}

//-----------------------------------------------------------

void Resize(int w, int h)
{
	// define the visible area of the window ( in pixels )
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);

	// Setup viewing volume

	glMatrixMode(GL_PROJECTION);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLoadIdentity();

	gluPerspective(60.0, (float)w / (float)h, 1.0, 5000.0f);
}

void Idle()
{
	if (paused)
		return;

	long curTime = glutGet(GLUT_ELAPSED_TIME);
	if (curTime - oldTime > 2000) {
		// generate asteroid
		// randomize
		oldTime = curTime;
	}

	// Sun animation.
	sun->animate();

	// Left-click animation.
	if (animate) {
		rotx += 0.04;
		roty += 0.04;
	}

	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'i':
		zoomIn += 10;
		break;
	case 'o':
		zoomOut += 10;
		break;
	case 'w':
		ship->position[1] += 1.5;
		break;
	case 's':
		ship->position[1] -= 1.5;
		break;
	case 'a':
		ship->position[0] -= 1.5;
		break;
	case 'd':
		ship->position[0] += 1.5;
		break;
	case SPACEBAR:
		paused = !paused;
		break;
	case ESCAPE:
		exit(0);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void SpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		rotx += 5;
		break;
	case GLUT_KEY_DOWN:
		rotx -= 5;
		break;
	case GLUT_KEY_LEFT:
		roty += 5;
		break;
	case GLUT_KEY_RIGHT:
		roty -= 5;
		break;
	}
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		animate = !animate;
		glutPostRedisplay();
	}
}


void Setup()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);  //renders a fragment if its z value is less or equal of the stored value
	glClearDepth(1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	sun = new Sun();
	ship = new Spaceship();
	md = new Asteroid("resources/asteroid_2.obj");
	md->randomize();

	md->speed = { 0.0f, -0.000f, 0.01f };
	md->rspeed = { 0.0f, -0.050f, 0.05f };


	// Create light components
	GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat position[] = { sun->position[0], sun->position[1], sun->position[2], 1.0f }; // Place light source inside the sun.

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
}

void MenuSelect(int choice)
{
	switch (choice) {
	default:
		break;
	}

}