#pragma once

#include "Point.h"
#include "Face.h"
#include "Model.h"
#include "ObjectModel.h"
#include "Sun.h"
#include "Spaceship.h"
#include "Asteroid.h"
#include "Star.h"
#include "StarManager.h"
#include "Endgame.h"
#include "Text.h"


//-------- Functions --------------------------------

void Render();
// The function responsible for drawing everything in the 
// OpenGL context associated to a window. 

void Resize(int w, int h);
// Handle the window size changes and define the world coordinate 
// system and projection type

void Setup();
// Set up the OpenGL state machine and create a light source

void Idle();

Model* ReadFile();
//Function for reading a model file

void DisplayModel(Model*);
// Function for displaying a model

void Keyboard(unsigned char key,int x,int y);
// Function for handling keyboard events.

void KeyboardRelease(unsigned char key, int x, int y);
// Function for releasing keys.

void SpecialKeyboard(int key, int x, int y);
// Function for handling special keyboard events.

void Mouse(int button,int state,int x,int y); 
// Function for handling mouse events

void MenuSelect(int choice);

float randFloat(float min, float max);