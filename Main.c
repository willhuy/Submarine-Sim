#include "Main.h"

void myDisplay()
{
	// clear the screen 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	// Set the camera position to look at the origin, with the Y-axis as up
	gluLookAt(cameraPosition[0], cameraPosition[1], cameraPosition[2], cameraCenterX, cameraCenterY, cameraCenterZ, 0, 1, 0);

	// Render scene axis
	renderCoorAxis();

	// Swap the double buffers
	glutSwapBuffers();
}

void myKey(unsigned char key, int x, int y) {
	// User press 'q' to quit
	if (key == 'q') {
		printf("User press 'q'!\n");
		exit(0);
	}

	// User press 'f' to toggle fullscreen on/off
	if (key == 'f') {
		printf("User press 'f'!\n");
		if (!fullscreen) {
			glutFullScreen();
			fullscreen = 1;
		}
		else {
			glutReshapeWindow(WIDTH, HEIGHT);
			glutPositionWindow(100, 150);
			fullscreen = 0;
		}
	}
}

void mySpecialKey(unsigned char key, int x, int y) {
	
}

void update() {
	glutPostRedisplay();
	glutTimerFunc(FRAME_EXIST_TIME, update, 0);
}

void initializeGL() {
	// enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// set background color to be black
	glClearColor(0, 0, 0, 1.0);
}

void myResize(int newWidth, int newHeight) {
	// update the new width
	windowWidth = newWidth;
	// update the new height
	windowHeight = newHeight;

	// update the viewport to still be all of the window
	glViewport(0, 0, windowWidth, windowHeight);

	// change into projection mode so that we can change the camera properties
	glMatrixMode(GL_PROJECTION);

	// load the identity matrix into the projection matrix
	glLoadIdentity();

	// gluPerspective(fovy, aspect, near, far)
	gluPerspective(45, (float)windowWidth / (float)windowHeight, 1, 20);

	// change into model-view mode so that we can change the object positions
	glMatrixMode(GL_MODELVIEW);
}

void printMenu() {
	// Print out the control instructions
	printf("\n\n\nControls:\n");
	printf("W: Move foward\n");
	printf("A: Move left\n");
	printf("S: Move back\n");
	printf("D: Move right\n");
	printf("----------------------\n");
	printf("Q: Move down\n");
	printf("E: Move up\n");
	printf("----------------------\n");
	printf("U: Wireframe toggle\n");
	printf("----------------------\n");
	printf("B: Boid Circling (Method 1)\n");
	printf("N: Boid Swimming (Method 2)\n");
	printf("M: Boid flocking (Method 3)\n");
	printf("----------------------\n");
	printf("P: Quit\n\n");

}

void main(int argc, char** argv) {
	printMenu();

	// Set the seed for rand() function
	srand(time(NULL));

	// initialize the toolkit
	glutInit(&argc, argv);

	// Set inital display properties
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(100, 150);

	// open the screen window
	glutCreateWindow("Submarine");

	// register redraw function
	glutDisplayFunc(myDisplay);

	// register timer callback function
	glutTimerFunc(FRAME_EXIST_TIME, update, 0);

	// register the resize function
	glutReshapeFunc(myResize);

	// register normal keyboard input function
	glutKeyboardFunc(myKey);

	// register special keyboard input function
	glutSpecialFunc(mySpecialKey);

	// Initialize OpenGL settings
	initializeGL();

	// Initialize the scene
	initScene();

	// Enter the program main loop
	glutMainLoop();
}