#include "visuals.h"   // Header file for our OpenGL functions
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "../gl/glut.h"   // - An interface and windows 

#include <time.h>
#include <Windows.h>
#include <mmsystem.h>

using namespace std;

////////////////// State Variables ////////////////////////

/////////////// Main Program ///////////////////////////

int main(int argc, char* argv[])
{
	srand(time(NULL));

	// initialize GLUT library state
	glutInit(&argc, argv);

	// Set up the display using the GLUT functions to 
	// get rid of the window setup details:
	// - Use true RGB colour mode ( and transparency )
	// - Enable double buffering for faster window update
	// - Allocate a Depth-Buffer in the system memory or 
	//   in the video memory if 3D acceleration available	
	//RGBA//DEPTH BUFFER//DOUBLE BUFFER//
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);


	// Define the main window size and initial position 
	// ( upper left corner, boundaries included )
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(0, 0);

	// Create and label the main window
	glutCreateWindow("Interstellar");
	//glutFullScreen();
	// Configure various properties of the OpenGL rendering context
	Setup();

	// Callbacks for the GL and GLUT events:

	// The rendering function 
	glutDisplayFunc(Render);
	glutReshapeFunc(Resize);
	glutIdleFunc(Idle);
	glutKeyboardFunc(Keyboard); // For special input call glutSpecialFunc instead.
	glutKeyboardUpFunc(KeyboardRelease);
	glutSpecialFunc(SpecialKeyboard); // For special input call glutSpecialFunc instead.
	glutMouseFunc(Mouse);

	glutCreateMenu(MenuSelect);
	glutAddMenuEntry("Full Screen",0);
	glutAddMenuEntry("Restart", 1);

	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Start song loop.
	//PlaySound(TEXT("03. Hallways Of Always.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

	//Enter main event handling loop
	glutMainLoop();
	return 0;
}
