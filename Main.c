#include "Main.h"

void myDisplay()
{
	// set shading mode
	glShadeModel(GL_SMOOTH);

	// clear the screen 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	// Set the camera position to look at the origin, with the Y-axis as up
	gluLookAt(cameraPosition[0], cameraPosition[1], cameraPosition[2], 
		cameraCenterX, cameraCenterY, cameraCenterZ, 
		0, 1, 0);

	// position light 0
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	// Render scene axis
	renderCoorAxis();

	// render submarine
	renderSubmarine();

	// Swap the double buffers
	glutSwapBuffers();
}

void myKey(unsigned char key, int x, int y) {
	// User press 'q' to quit
	if (key == 'p') {
		printf("User press 'p'!\n");
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

	// Move camera up
	if (key == 'q') {
		cameraPosition[1] += CAMERA_INCREMENT;
		cameraCenterY += CAMERA_INCREMENT;
	}

	// Move camera down
	if (key == 'e') {
		cameraPosition[1] -= CAMERA_INCREMENT;
		cameraCenterY -= CAMERA_INCREMENT;
	}

	// Move camera left
	if (key == 'a') {
		cameraPosition[0] -= CAMERA_INCREMENT;
		cameraCenterX -= CAMERA_INCREMENT;
	}

	// Move camera right
	if (key == 'd') {
		cameraPosition[0] += CAMERA_INCREMENT;
		cameraCenterX += CAMERA_INCREMENT;
	}

	// Move camera foward
	if (key == 'w') {
		cameraPosition[2] -= CAMERA_INCREMENT;
		cameraCenterZ -= CAMERA_INCREMENT;
	}

	// Move camera backward
	if (key == 's') {
		cameraPosition[2] += CAMERA_INCREMENT;
		cameraCenterZ += CAMERA_INCREMENT;
	}
}

void mySpecialKey(unsigned char key, int x, int y) {
	
}

void update() {
	glutPostRedisplay();
	glutTimerFunc(FRAME_EXIST_TIME, update, 0);
}

void initializeGL() {
	// enable lighting 
	glEnable(GL_LIGHTING);
	// define the light color and intensity
	GLfloat ambientLight[] = { 0.0, 0.0, 0.0, 1.0 };  // relying on global ambient
	GLfloat diffuseLight[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat specularLight[] = { 1.0, 1.0, 1.0, 1.0 };

	//  the global ambient light level
	GLfloat globalAmbientLight[] = { 0.4, 0.4, 0.4, 1.0 };

	// set the global ambient light level
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientLight);

	// define the color and intensity for light 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, diffuseLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, specularLight);

	// enable light 0
	glEnable(GL_LIGHT0);

	// enable unit normals
	glEnable(GL_NORMALIZE);

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
	gluPerspective(45, (float)windowWidth / (float)windowHeight, Z_NEAR, Z_FAR);

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

	// print keyboard menu
	printMenu();

	// Load the submarine object file
	loadSubmarine("object_files/submarine.obj");

	// Initialize the scene
	initScene();

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

	// Enter the program main loop
	glutMainLoop();
}

void setMaterialHelper(GLfloat diffuse[], GLfloat specular[], GLfloat ambient[], GLfloat shininess) {
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

void initScene() {
	originBall = gluNewQuadric();

	// Init camera position
	cameraPosition[0] = 0.0f;
	cameraPosition[1] = 50.0f;
	cameraPosition[2] = 50.0f;
	cameraCenterX = 0;
	cameraCenterY = 0;
	cameraCenterZ = 0;
}

void renderCoorAxis() {

	// white diffuse ball
	setMaterialHelper(whiteDiffuse, zeroMaterial, zeroMaterial, noShininess);
	gluSphere(originBall, 0.1f, Z_SUBDIVISION, Z_SUBDIVISION);

	// Set line width
	glLineWidth(AXIS_WIDTH);

	// Start rendering
	glPushMatrix();
	glBegin(GL_LINES);

	// X axis with red material
	setMaterialHelper(redDiffuse, zeroMaterial, zeroMaterial, noShininess);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(5.0f, 0.0f, 0.0f);

	// Y axis with bkue material
	setMaterialHelper(greenDiffuse, zeroMaterial, zeroMaterial, noShininess);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 5.0f, 0.0f);

	// Z axis
	setMaterialHelper(blueDiffuse, zeroMaterial, zeroMaterial, noShininess);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 5.0f);

	glEnd();
	glPopMatrix();
}

void renderSubmarine() {
	glPushMatrix();

	// This will make the ship move with camera
	glScalef(0.05f, 0.05f, 0.05f);
	glTranslatef(cameraCenterX * 20, cameraCenterY * 20, cameraCenterZ * 20);
	glRotatef(-90, 0, 1, 0);

	// Set the ship material to yellow and render
	setMaterialHelper(yellowDiffuse, zeroMaterial, zeroMaterial, noShininess);
	for (int i = 0; i < facesCount; i++) {

		// Each vertices has its own normal for smooth shading;
		glBegin(GL_TRIANGLES);
		glNormal3f(verticesNormal[faces[i][1] - 1][0], verticesNormal[faces[i][1] - 1][1], verticesNormal[faces[i][1] - 1][2]);
		glVertex3f(vertices[faces[i][0] - 1][0], vertices[faces[i][0] - 1][1], vertices[faces[i][0] - 1][2]);

		glNormal3f(verticesNormal[faces[i][3] - 1][0], verticesNormal[faces[i][3] - 1][1], verticesNormal[faces[i][3] - 1][2]);
		glVertex3f(vertices[faces[i][2] - 1][0], vertices[faces[i][2] - 1][1], vertices[faces[i][2] - 1][2]);

		glNormal3f(verticesNormal[faces[i][5] - 1][0], verticesNormal[faces[i][5] - 1][1], verticesNormal[faces[i][5] - 1][2]);
		glVertex3f(vertices[faces[i][4] - 1][0], vertices[faces[i][4] - 1][1], vertices[faces[i][4] - 1][2]);
		glEnd();
	}

	glPopMatrix();
}