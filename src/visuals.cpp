#include <stdio.h>     // - Just for some ASCII messages
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../gl/glut.h"   // - An interface and windows management library
#include "visuals.h"   // Header file for our OpenGL functions

Model *md;
static float rotx = 0.0;
static float roty = 0.0;
static bool animate = false;

using namespace std;

void DrawAxes()
{
	glColor3f(0.6, 0.6, 0.6);
	glBegin(GL_LINES);
	glVertex2f(-100.0, 0.0);
	glVertex2f(100.0, 0.0);
	glVertex2f(0.0, -100.0);
	glVertex2f(0.0, 100.0);
	glEnd();
}

void Render()
{
	//CLEARS FRAME BUFFER ie COLOR BUFFER& DEPTH BUFFER (1.0)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
	// and the depth buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0, 0, -100);
	glRotatef(rotx, 1, 0, 0);
	glRotatef(roty, 0, 1, 0);

	DrawAxes();

	glScalef(0.05, 0.05, 0.05);
	glColor3f(0.54, 0.27, 0.07);   // Saddle Brown
	DisplayModel(md);  

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
	glLoadIdentity();

	gluPerspective(60.0, (float)w / (float)h, 1.0, 500.0);
}

void Idle()
{
	/*if (animate) {
		rotx += 0.4;
		roty += 0.4;
		}*/

	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
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
	md = ReadFile();
	// TODO Lighting 
}

void MenuSelect(int choice)
{
	switch (choice) {
	default:
		break;
	}

}

Model* ReadFile()
{
	cout << "Reading object file." << endl;

	ifstream obj_file("resources/asteroid.obj");                

	if (obj_file.fail()) {
		cout << "ERROR: Could not open .obj file." << endl;
		exit(1);
	}


	cout << "SUCCESS: Opened .obj file." << endl;

	int vertices, faces;
	obj_file >> vertices;                               // Get the number of vertices
	obj_file >> faces;									// Get the number of faces
	cout << "Vertices: " << vertices << endl;
	cout << "Faces: " << faces << endl;

	Model *md = new Model(vertices, faces);

	for (int i = 0; i < vertices; i++){                        // Get the vertex coordinates
		char type;
		obj_file >> type;
		float x, y, z;
		obj_file >> x;
		obj_file >> y;
		obj_file >> z;

		md->getObjPoints()[i] = new Point(x, y, z);
		//md->getObjPoints()[i]->print();
	}
	cout << "Read points." << endl;

	string line;
	int i = 0;
	while (getline(obj_file, line)) {									// Get the face structure
		//cout << "line: " << line << endl;
		if (line[0] != 'f')
			continue;
		istringstream iss(line);
		string token;
		getline(iss, token, ' ');
		getline(iss, token, ' ');
		getline(iss, token, ' ');
		istringstream iss1(token);
		string token1;
		getline(iss1, token1, '/');
		//cout << "token1: " << token1 << endl;
		getline(iss, token, ' ');
		istringstream iss2(token);
		string token2;
		getline(iss2, token2, '/');
		//cout << "token2: " << token2 << endl;
		getline(iss, token, ' ');
		istringstream iss3(token);
		string token3;
		getline(iss3, token3, '/');
		//cout << "token3: " << token3 << endl;

		md->getObjFaces()[i] = new Face(atoi(token1.c_str()), atoi(token2.c_str()), atoi(token3.c_str()));
		//md->getObjFaces()[i]->print();
		i++;
	}
	cout << "Read faces." << endl;


	obj_file.close();

	return md;
}

void DisplayModel(Model *md)
{
	glPushMatrix();

	glBegin(GL_TRIANGLES);

	Point **objPoints = md->getObjPoints();
	Face **objFaces = md->getObjFaces();
	for (int i = 0; i < md->getFaces(); i++)
	{
		Face *face = objFaces[i];
		Point *v1 = objPoints[face->getV1() - 1];
		Point *v2 = objPoints[face->getV2() - 1];
		Point *v3 = objPoints[face->getV3() - 1];

		glVertex3f(v1->getX(), v1->getY(), v1->getZ());
		glVertex3f(v2->getX(), v2->getY(), v2->getZ());
		glVertex3f(v3->getX(), v3->getY(), v3->getZ());
	}

	glEnd();
	glPopMatrix();
}