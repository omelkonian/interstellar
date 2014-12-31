#include <stdio.h>     // - Just for some ASCII messages
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>

#include "../gl/glut.h"   // - An interface and windows management library
#include "visuals.h"   // Header file for our OpenGL functions

Model *md;
static float rotx = 0.0;
static float roty = 0.0;
static bool animate = true;

using namespace std;

void Render()
{    
  //CLEARS FRAME BUFFER ie COLOR BUFFER& DEPTH BUFFER (1.0)
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clean up the colour of the window
													   // and the depth buffer
  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity();
	
  //glRotatef(rotx, 1, 0, 0);


  glTranslatef(0.0, 0.0, -30.0);
  glColor3f(0.3, 0.2, 0.9);                            // Set drawing colour
  glutSolidTorus(5.0, 10.0, 1000, 2540);

  //glColor3f(0.3, 0.2, 0.9);                            // Set drawing colour
  //DisplayModel(md);  
  
  glutSwapBuffers();             // All drawing commands applied to the 
                                 // hidden buffer, so now, bring forward
                                 // the hidden buffer and hide the visible one
}

//-----------------------------------------------------------

void Resize(int w, int h)
{ 
  // define the visible area of the window ( in pixels )
  if (h==0) h=1;
  glViewport(0,0,w,h); 

  // Setup viewing volume

  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity();
 
  gluPerspective(60.0, (float)w/(float)h, 1.0, 500.0);
}

void Idle()
{
	if(animate)
		rotx+=0.4;

	glutPostRedisplay();
}

void Keyboard(unsigned char key,int x,int y)
{
	switch(key)
	{
		case 'q' : 
			exit(0);
			break;
		default : 
			break;
	}

	glutPostRedisplay();
}

void SpecialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		rotx += 1;
		break;
	case GLUT_KEY_DOWN:
		rotx -= 1;
		break;
	case GLUT_KEY_LEFT:
		roty += 1;
		break;
	case GLUT_KEY_RIGHT:
		roty -= 1;
		break;
	}
	glutPostRedisplay();
}

void Mouse(int button,int state,int x,int y)
{
	 if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	 {
		 animate = !animate;
         glutPostRedisplay();
	 }
}


void Setup()
{
	//md = ReadFile();
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

	ifstream obj_file("src/asteroid.obj");                   // Open the file for reading OBJINFO.TXT
   
	if (obj_file.fail()) {
		cout << "ERROR: Could not open .obj file." << endl;
		exit(1);
	}
		

	cout << "SUCCESS: Opened .obj file." << endl;

	int vertices, faces;
	obj_file >> vertices;                               // Get the number of vertices
	obj_file >> faces;									// Get the number of faces

	Model *md = new Model(vertices, faces);

	for (int i = 0; i < md->getVertices(); i++){                        // Get the vertex coordinates
		float x, y, z;
		obj_file >> x;
		obj_file >> y;
		obj_file >> z;
		cout << x << y << z;
		
		md->getObjPoints()[i] = new Point(x, y, z);
   }

   for (int i = 0; i < md->getFaces(); i++){                        // Get the face structure
	   int v1, v2, v3;
	   obj_file >> v1;
	   obj_file >> v2;
	   obj_file >> v3;
	   cout << v1 << v2 << v3 << endl;

	   md->getObjFaces()[i] = new Face(v1, v2, v3);
   }

   obj_file.close();

   return md;
}

void DisplayModel(Model *md)
{
	glPushMatrix();
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < md->getFaces(); i++)
	{
		Point **objPoints = md->getObjPoints();
		Face **objFaces = md->getObjFaces();
		Point *v1 = objPoints[objFaces[i]->getV1() - 1];
		Point *v2 = objPoints[objFaces[i]->getV2() - 1];
		Point *v3 = objPoints[objFaces[i]->getV3() - 1];
		glVertex3f(v1->getX(), v1->getY(), v1->getZ());
		glVertex3f(v2->getX(), v2->getY(), v2->getZ());
		glVertex3f(v3->getX(), v3->getY(), v3->getZ());
	}

	glEnd();
	glPopMatrix();
}