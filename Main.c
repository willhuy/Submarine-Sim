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
		shipPosition[0], shipPosition[1], shipPosition[2],
		0, 1, 0);

	// position light 0
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	// Render scene
	renderScene();

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

	// Toggle quadric render mode
	if (key == 'u') {
		isWireFrame = !isWireFrame;
	}

	// Toggle fog

	if (key == 'b') {
		fogOn = !fogOn;
	}

	// Move camera up
	if (key == 'q') {
		cameraPosition[1] += SHIP_INCREMENT;
		shipPosition[1]   += SHIP_INCREMENT;
	}

	// Move camera down
	if (key == 'e') {
		cameraPosition[1] -= SHIP_INCREMENT;
		shipPosition[1]   -= SHIP_INCREMENT;
	}

	// Move camera left
	if (key == 'a') {
		cameraPosition[0] -= SHIP_INCREMENT;
		shipPosition[0]   -= SHIP_INCREMENT;
	}

	// Move camera right
	if (key == 'd') {
		cameraPosition[0] += SHIP_INCREMENT;
		shipPosition[0]   += SHIP_INCREMENT;
	}

	// Move camera foward
	if (key == 'w') {
		cameraPosition[2] -= SHIP_INCREMENT;
		shipPosition[2]   -= SHIP_INCREMENT;
	}

	// Move camera backward
	if (key == 's') {
		cameraPosition[2] += SHIP_INCREMENT;
		shipPosition[2]   += SHIP_INCREMENT;
	}

	glutPostRedisplay();
}

void myMouseMotion(int x, int y) {
	if (lastMouseX == -1 && lastMouseY == -1) {
		// First call, initialize the last mouse position
		lastMouseX = x;
		lastMouseY = y;
		return;
	}

	// Calculate movement delta
	float dx = (float)(x - lastMouseX);
	float dy = (float)(y - lastMouseY);

	// Update vertical and horizontal angle based on deltas
	horizontalAngle += dx * horizontalSensitivity;
	verticalAngle += dy * verticalSensitivity;

	// Update the camera position
	cameraPosition[0] = shipPosition[0] + cameraRadius * cosf(verticalAngle * PI / 180.0f) * sinf(horizontalAngle * PI / 180.0f);
	cameraPosition[1] = shipPosition[1] + cameraRadius * sinf(verticalAngle * PI / 180.0f);
	cameraPosition[2] = shipPosition[2] + cameraRadius * cosf(verticalAngle * PI / 180.0f) * cosf(horizontalAngle * PI / 180.0f);

	// Update last mouse position
	lastMouseX = x;
	lastMouseY = y;

	glutPostRedisplay();
}

void mySpecialKey(unsigned char key, int x, int y) {
	
}

void update() {
	waveDelta += WAVE_SPEED;
	updateWave();
	glutPostRedisplay();
	glutTimerFunc(FRAME_EXIST_TIME, update, 0);
}

void initializeGL() {

	// enable texture 2D
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// define texture id
	glGenTextures(1, &sandTextureID);
	glBindTexture(GL_TEXTURE_2D, sandTextureID);

	// mipmap builder
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, imageWidth, imageHeight, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

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
	gluPerspective(100, (float)windowWidth / (float)windowHeight, Z_NEAR, Z_FAR);

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
	printf("B: Fog toggle\n");
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

	// Load sand texture
	loadTexture("object_files/sand_ascii.ppm");

	// Initiallize the sim scene
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

	glutPassiveMotionFunc(myMouseMotion);

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

	// wave
	initializeWave();

	// quadrics
	originBall = gluNewQuadric();
	cylinder   = gluNewQuadric();
	disk       = gluNewQuadric();

	gluQuadricTexture(cylinder, GL_TRUE);
	gluQuadricTexture(disk, GL_TRUE);
}

void renderScene() {
	
	// render axis
	renderCoorAxis();

	// render quadrics
	renderQuadrics();

	// render fog
	if (fogOn) {
		glEnable(GL_FOG);
		renderFog();
	}
	else {
		glDisable(GL_FOG);
	}

	// render submarine
	renderSubmarine();

	// render wave
	renderWave();
}

// Render the grid as a wireframe
void renderWave() {

	glTranslatef(0, 98, 0);
	glScalef(5, 5, 5);

	setMaterialHelper(blueWater, zeroMaterial, zeroMaterial, noShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, emissionWave);
	for (int i = 0; i < WAVE_GRID_SIZE - 1; i++) {
		for (int j = 0; j < WAVE_GRID_SIZE - 1; j++) {

			// Draw two triangles (cause square)
			glBegin(GL_TRIANGLES);

				// First
				glNormal3f(1.0f, 0.0f, 0.0f);
				glVertex3fv(waveVertices[i][j]);
				glNormal3f(1.0f, 0.0f, 0.0f);
				glVertex3fv(waveVertices[i + 1][j]);
				glNormal3f(1.0f, 0.0f, 0.0f);
				glVertex3fv(waveVertices[i][j + 1]);

				// Second
				glNormal3f(1.0f, 0.0f, 0.0f);
				glVertex3fv(waveVertices[i + 1][j]);
				glNormal3f(1.0f, 0.0f, 0.0f);
				glVertex3fv(waveVertices[i][j + 1]);
				glNormal3f(1.0f, 0.0f, 0.0f);
				glVertex3fv(waveVertices[i + 1][j + 1]);

			glEnd();
		}
	}

}

void renderCoorAxis() {

	// white diffuse ball
	setMaterialHelper(white, zeroMaterial, zeroMaterial, noShininess);
	gluSphere(originBall, 1.0f, Z_SUBDIVISION, Z_SUBDIVISION);

	// Set line width
	glLineWidth(AXIS_WIDTH);

	// Start rendering
	glPushMatrix();
	glBegin(GL_LINES);

	// X axis with red material
	setMaterialHelper(red, zeroMaterial, zeroMaterial, highShininess);
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);

	// Y axis with blue material
	setMaterialHelper(green, zeroMaterial, zeroMaterial, highShininess);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);

	// Z axis
	setMaterialHelper(blue, zeroMaterial, zeroMaterial, highShininess);
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 10.0f);

	glEnd();
	glPopMatrix();

	glLineWidth(1);
}

void renderQuadrics() {

	// set quadric render mode
	if (isWireFrame) {
		gluQuadricDrawStyle(cylinder, GLU_LINE);
		gluQuadricDrawStyle(disk, GLU_LINE);
	}
	else {
		gluQuadricDrawStyle(cylinder, GLU_FILL);
		gluQuadricDrawStyle(disk, GLU_FILL);
	}

	// Quadrics shouldn't be affect by lighting
	gluQuadricNormals(cylinder, GLU_NONE);
	gluQuadricNormals(disk, GLU_NONE);


	glPushMatrix();

	// Both the disk and cylinder need to be rotate in x direction
	glRotatef(-90, 1, 0, 0);

	// cylinder
	setMaterialHelper(zeroMaterial, neutral, zeroMaterial, noShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, emissionCylinder);
	gluCylinder(cylinder, 100, 100, 100, 50, 30);

	// disk
	setMaterialHelper(zeroMaterial, neutral, zeroMaterial, noShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, emissionDisk);
	gluDisk(disk, 0, 100, 50, 1);

	glPopMatrix();
}

void renderSubmarine() {
	glPushMatrix();
	
	// This will make the ship move with camera
	glTranslatef(shipPosition[0], shipPosition[1], shipPosition[2]);
	glScalef(0.05f, 0.05f, 0.05f);
	glRotatef(-90, 0, 1, 0);

	// Set the ship material to yellow and render
	setMaterialHelper(yellow, zeroMaterial, zeroMaterial, highShininess);
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

void renderFog() {
	glFogf(GL_FOG_MODE, GL_EXP);
	glFogf(GL_FOG_DENSITY, 0.007);
	glFogfv(GL_FOG_COLOR, fogColor);
}