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
Environment * environment;
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
		endGame->renderEndgame(asteroidManager, sun, stars, rotx, roty, zoomIn, zoomOut, environment, level, score);
		return;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window and the depth buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0, 0, -30); // Move camera a bit back.

	// Display Texts.
	level->draw();
	score->draw();

	glTranslatef(0, 0, zoomIn);
	glTranslatef(0, 0, -zoomOut);

	glRotatef(rotx, 1, 0, 0);
	glRotatef(roty, 0, 1, 0);

	//DrawAxes();
	//globalBox->draw();

	// Background.	
	environment->draw();

	sun->draw();

	stars->draw();

	// Asteroid.
	asteroidManager->draw();
	//asteroidManager->drawBounds();

	// Ship.
	ship->draw();
	//ship->drawBounds();

	glutSwapBuffers();
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
		glDisable(GL_LIGHT0);
		animate = true;

		endGame->well->update();
	
		zoomOut += 0.2;
		if (endGame->getAge() > 5000)
			zoomOut += 0.1*((endGame->getAge() - 5000) / 2000);

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
	}

	// Collision detection.
	if (!ended) {
		for (Asteroid *a : asteroidManager->asteroids) {
			if (ship->intersects(a)) {
				ended = true;
				animate = true;

				endGame->timeCreated = glutGet(GLUT_ELAPSED_TIME);
				endGame->well = new PsychedelicWell(ship->position);
				endGame->gameOverText = new Text("GAME OVER", 0.05, { ship->position[0] - 5, ship->position[1] - 10, ship->position[2] + 25 });
				endGame->gameOverText->color = { 1, 0, 0 };
			}
		}
		
		stars->generate(0);
	}

	// Update stars,asteroids and levelManager each frame.
	if (score->score > levelManager->currentLevel * 1000) {
		levelManager->update();
		level->level = levelManager->currentLevel;
		asteroidManager->levelUp(levelManager->currentLevel);
	}

	if (!ended)
		asteroidManager->update(ship->position);
	
	stars->update();

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
	case 'r':
		if (ended)
			endGame->restart();
		break;
 	case SPACEBAR:
		paused = !paused;
		break;
	case ESCAPE:
		// Free resources
		delete ship;
		delete asteroidManager;
		delete stars;
		delete sun;
		delete environment;
		delete globalBox;
		if (!ended) {
			delete level;
			delete score;
			delete levelManager;
		}

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
	if (!ended) {
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);  //renders a fragment if its z value is less or equal of the stored value
		glClearDepth(1);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		globalBox = new AABB(X_MAX, Y_MAX, Z_MAX, X_MIN, Y_MIN, Z_MIN);
		printf("Creating the stars \n");
		stars = new StarManager();
		printf("Creating the sun \n");
		sun = new Sun();
		printf("Creating the background \n");
		environment = new Environment();
		printf("Creating the spaceship \n");
		ship = new Spaceship(1.0f);
		score = new Score();
		level = new Level();
		levelManager = new LevelManager(score);
		printf("Creating the asteroids \n");
		asteroidManager = new AsteroidManager("resources/asteroid_2.obj", score);
		endGame = new Endgame();

		// Create light components
		GLfloat ambientLight[] = { AMBIENT_RED, AMBIENT_GREEN, AMBIENT_BLUE, 1.0 };
		GLfloat diffuseLight[] = { DIFFUSE_RED, DIFFUSE_GREEN, DIFFUSE_BLUE, 1.0 };
		GLfloat specularLight[] = { SPECULAR_RED, SPECULAR_GREEN, SPECULAR_BLUE, 1.0 };
		GLfloat position[] = { SUN_POSITION_X, SUN_POSITION_Y, SUN_POSITION_Z, 1.0 }; // Place light source inside the sun.		

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
		glLightfv(GL_LIGHT0, GL_POSITION, position);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_NORMALIZE);


		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);

		printf("Game created \n");
	}
	else { // restarting
		
		// Song reset.
		PlaySound(NULL, 0, 0);
		PlaySound(TEXT("03. Hallways Of Always.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

		// Static variables reset.
		ended = false;
		paused = false;
		animate = false;
		rotx = 0;
		roty = 0;
		zoomIn = 0;
		zoomOut = 0;

		// Lighting reset.
		glDisable(GL_LIGHT1);
		glEnable(GL_LIGHT0);

		// Asteroid manager reset.
		asteroidManager->erase();
		asteroidManager->asteroidSpeed = ASTEROID_INITIAL_SPEED;
		asteroidManager->genFrequency = ASTEROID_INITIAL_GEN_FREQUENCY;
		asteroidManager->asteroidsPerGen = 1;

		// Level, Score reset.
		delete levelManager;
		delete score;
		delete level;

		score = new Score();
		asteroidManager->currentScore = score;
		level = new Level();
		levelManager = new LevelManager(score);

		
		// Spaceship position reset.
		ship->position = { 0, 0, 0 };

		// Environment reset.
		environment->position = { 5, 5, -10 };
		environment->scale = { 500, 500, 500 };
		environment->rposition = { 0, 180, 0 };
		environment->rspeed = { 0.0001f, 0.001f, -0.001f };
	}
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