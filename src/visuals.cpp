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

// Gamification
Score *score;
Level *level;
LevelManager *levelManager;


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

	level->draw();
	score->draw();

	glTranslatef(0, 0, zoomIn);
	glTranslatef(0, 0, -zoomOut);

	glRotatef(rotx, 1, 0, 0);
	glRotatef(roty, 0, 1, 0);

	
	//DrawAxes();
	//globalBox->draw();

	// Asteroid && ship.

	asteroidManager->draw();

	ship->draw();
	ship->drawBounds();

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
		if (endGame->getAge() > 0 && endGame->getAge() < 500)
		endGame->well->update();

		if (endGame->getAge() > 1500 && endGame->getAge() < 5000)
			zoomOut += 0.1;

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
		//AABB *shipBox = ship->getAABB();
		for (Asteroid *a : asteroidManager->asteroids) {
			//AABB *asteroidBox = a->getAABB();
			if (ship->intersects(a)) {
				ended = true;
				animate = true;

				endGame->timeCreated = glutGet(GLUT_ELAPSED_TIME);
				endGame->well = new PsychedelicWell(ship->position);
				endGame->text = new Text("GAME OVER", 0.05, { ship->position[0] - 5, ship->position[1], ship->position[2] + 25});
			}
			//delete asteroidBox;
		}
		
		stars->generate(0);
		asteroidManager->update();
	}

	// Update stars,asteroids and levelManager each frame.
	if (score->score > levelManager->currentLevel * 1000) {
		levelManager->update();
		level->level = levelManager->currentLevel;
		asteroidManager->asteroidSpeed += ASTEROID_SPEED_INCREMENT;
	}

	
	stars->update();
	// Sun animation.
	sun->animate();

	// Left-click animation.
	if (animate) {
		rotx += 0.02;
		roty += 0.02;
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
	score = new Score();
	level = new Level();
	levelManager = new LevelManager(score);
	asteroidManager = new AsteroidManager("resources/asteroid_2.obj", score);
	

	// Create light components
	GLfloat ambientLight[] = { 0, 0, 0, 1.0 };
	GLfloat diffuseLight[] = { 1, 1, 1, 1.0 };
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
	case 0:
		glutFullScreen();
		break;
	case 1:
		ended = false;
		rotx = roty = zoomIn = zoomIn = 0.0f;
		break;
	default:
		break;
	}

}

float randFloat(float a, float b)
{
	return ((b - a)*((float)rand() / RAND_MAX)) + a;
}
string NumberToString(int number) {
	ostringstream ss;
	ss << number;
	return ss.str();
}