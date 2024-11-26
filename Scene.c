#include "Scene.h"

void initScene() {
	originBall = gluNewQuadric();
}

void renderCoorAxis() {

	glColor3f(1.0f, 1.0f, 1.0f);
	gluSphere(originBall, 0.1f, Z_SUBDIVISION, Z_SUBDIVISION);

	// Set line width
	glLineWidth(AXIS_WIDTH);

	// Start rendering
	glPushMatrix();
	glBegin(GL_LINES);

	// X axis
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);

	// Y axis
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	// Z axis
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);

	glEnd();
	glPopMatrix();
}