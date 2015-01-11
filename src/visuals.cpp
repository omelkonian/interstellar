#include <stdio.h>     // - Just for some ASCII messages
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../gl/glut.h"   // - An interface and windows management library
#include "visuals.h"   // Header file for our OpenGL functions
#include "Defines.h"

// Bounding box.
AABB *globalBox;

// The models of the scene.
AsteroidManager *asteroidManager;
Sun *sun;
Spaceship *ship;
StarManager *stars;

// Variables for rotating (up, down, left, right) and zooming in/out (i, o).
static float rotx = 0.0;
static float roty = 0.0;
static float zoomIn = 0.0;
static float zoomOut = 0.0;

// Booleans for animating (rotating), pausing, game over.
static bool animate = false;
static bool paused = false;
static bool ended = false;

// Endgame
Endgame *endGame;

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

	if (ended) {
		endGame->renderEndgame(asteroidManager, sun, stars, rotx, roty, zoomIn, zoomOut);
		return;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window and the depth buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0, 0, -30); // Move camera a bit back.

	glTranslatef(0, 0, zoomIn);
	glTranslatef(0, 0, -zoomOut);

	glRotatef(rotx, 1, 0, 0);
	glRotatef(roty, 0, 1, 0);

	//DrawAxes();
	//globalBox->draw();

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

	asteroidManager->draw();

	ship->draw();
	ship->getAABB()->draw();

	glDisable(GL_COLOR_MATERIAL);

	// Background.
	sun->draw();

	stars->draw();

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

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, (float)w / (float)h, 1.0, 5000.0f);
}

void Idle()
{
	if (paused)
		return;

	// Update psychedelic well.
	if (ended) {
		endGame->well->update();

		if (endGame->getAge() > 1500 && endGame->getAge() < 7000)
			zoomOut += 0.5;

		// Darken atmosphere (reset lighting).
		GLfloat ambientLight[] = { endGame->ambient[0], endGame->ambient[1], endGame->ambient[2], 1.0 };
		GLfloat diffuseLight[] = { endGame->diffuse[0], endGame->diffuse[1], endGame->diffuse[2], 1.0 };
		GLfloat specularLight[] = { endGame->specular[0], endGame->specular[1], endGame->specular[2], 1.0 };
		GLfloat position[] = { endGame->lightPos[0], endGame->lightPos[1], endGame->lightPos[2], 1.0f };

		glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specularLight);
		glLightfv(GL_LIGHT1, GL_POSITION, position);

		endGame->updateLighting();

		glEnable(GL_LIGHT1);

		if (endGame->getAge() > 25000)
			exit(1);
	}

	// Collision detection.
	if (!ended) {
		AABB *shipBox = ship->getAABB();
		for (Asteroid *a : asteroidManager->asteroids) {
			AABB *asteroidBox = a->getAABB();
			if (shipBox->intersects(asteroidBox)) {
				ended = true;
				animate = true;

				endGame->timeCreated = glutGet(GLUT_ELAPSED_TIME);
				endGame->well = new PsychedelicWell(ship->position);
				endGame->text = new Text("GAME OVER", 0.05, ship->position);
			}
			delete asteroidBox;
		}

		delete shipBox;
	}

	// Update stars and asteroids each frame.
	stars->update();
	stars->generate(0);

	asteroidManager->update();

	// Sun animation.
	sun->animate();

	// Left-click animation.
	if (animate) {
		rotx += 0.05;
		roty += 0.05;
	}

	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	if (key >= 65 && key <= 90) // accept CAPS also
		key += 32;

	switch (key)
	{
	case 'i':
		zoomIn += 10;
		break;
	case 'o':
		zoomOut += 10;
		break;
	case 'w':
		ship->speed[1] = 0.055;
		break;
	case 's':
		ship->speed[1] = -0.055;
		break;
	case 'a':
		ship->speed[0] = -0.055;
		break;
	case 'd':
		ship->speed[0] = 0.055;
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

void KeyboardRelease(unsigned char key, int x, int y)
{
	if (key >= 65 && key <= 90) // accept CAPS also
		key += 32;

	switch (key)
	{
	case 'w':
		ship->speed[1] = 0;
		break;
	case 's':
		ship->speed[1] = 0;
		break;
	case 'a':
		ship->speed[0] = 0;
		break;
	case 'd':
		ship->speed[0] = 0;
		break;
	default:
		break;
	}
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

	globalBox = new AABB(X_MAX, Y_MAX, Z_MAX, X_MIN, Y_MIN, Z_MIN);
	stars = new StarManager();
	sun = new Sun();
	ship = new Spaceship(1.0f);
	asteroidManager = new AsteroidManager("resources/asteroid_2.obj");
	

	// Create light components
	GLfloat ambientLight[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat diffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat position[] = { sun->position[0], sun->position[1], sun->position[2], 1.0f }; // Place light source inside the sun.

	endGame = new Endgame(ambientLight, diffuseLight, specularLight, position);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);

	glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CW); // everything drawn by glut primitives has cw orientation, asteroid is cw
	glFrontFace(GL_CCW);
}

void MenuSelect(int choice)
{
	switch (choice) {
	default:
		break;
	}

}

float randFloat(float a, float b)
{
	return ((b - a)*((float)rand() / RAND_MAX)) + a;
}