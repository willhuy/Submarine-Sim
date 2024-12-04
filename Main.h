#pragma once

#include <freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "FileIO.h"
#include "Wave.h"
#include "Boid.h"

// GLUT related macros
#define FRAME_EXIST_TIME 1000 / 60
#define WIDTH 900
#define HEIGHT 600
#define Z_NEAR 0.1f 
#define Z_FAR 10000.0f
#define SHIP_INCREMENT 0.9f
#define CAMERA_DISTANCE_FROM_SUBMARINE 10.0f
#define PI 3.14159265358979323846

// Scene related macros
#define AXIS_WIDTH 5.0f
#define Z_SUBDIVISION 100

// Initial camera position and parameters for camera transformation
GLfloat cameraPosition[3] = {0.0f, 50.0f, 50.0f};
GLfloat shipPosition[3]   = {0.0f, 40.0f, 10.0f};
GLfloat distanceFromSubmarine;
GLfloat verticalAngle;
GLfloat horizontalAngle;
GLfloat horizontalSensitivity = 0.3f;
GLfloat verticalSensitivity = 0.3f;
GLfloat cameraRadius = 30.0f;
int lastMouseX = -1;
int lastMouseY = -1;

//  position the light source directly on top of origin
GLfloat lightPosition[] = { 1.0, 1.0, 1.0, 0.0 };

// All quadrics in the scene
GLUquadric* originBall;
GLUquadric* cylinder;
GLUquadric* disk;
int isWireFrame = 1;

// Boid related variables
float base = 2.0f;
float height = 4.0f;
float baseVertices[4][3];
float topVertices[3];

/* different type of materials  */

// a material that is all zeros
GLfloat zeroMaterial[] = { 0.0, 0.0, 0.0, 1.0 };

// a blue diffuse material
GLfloat blue[] = { 0.0, 0.0, 1.0, 1.0 };

// a red diffuse material
GLfloat red[] = { 1.0, 0.0, 0.0, 1.0 };

// a green diffuse material
GLfloat green[] = { 0.0, 1.0, 0.0, 1.0 };

// a white diffuse material
GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };

// a yellow diffuse material for submarine
GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };

// a neutral material for texture object
GLfloat neutral[] = { 0.5, 0.5, 0.5, 1.0 };

// a emissive material for disk object
GLfloat emissionDisk[] = { 0.3, 0.3, 0.0, 1.0 };

// a emissive material for cylinder object
GLfloat emissionCylinder[] = { 0.1, 0.1, 0.0, 1.0 };


/* For wave */

// a emissive material for wave (water)
GLfloat emissionWave[] = { 0.0, 0.0, 0.1, 1.0 };

// a blue water material
GLfloat blueWater[] = { 0.0, 0.0, 1.0, 1.0 };


// shininess
GLfloat noShininess = 0.0;
GLfloat highShininess = 100.0;

// window dimensions
GLint windowWidth = WIDTH;
GLint windowHeight = HEIGHT;
int fullscreen = 0;

// fog related variables
int fogOn = 1;
GLfloat fogColor[] = { 0.0, 0.0, 1.0, 1.0 };

void printMenu();

void myDisplay();

void myKey(unsigned char, int, int);

void mySpecialKey(unsigned char, int, int);

void myMouseMotion(int, int);

void initializeGL();

void initScene();

void myResize(int, int);

void update();

void renderScene();

void renderCoorAxis();

void renderQuadrics();

void renderFog();

void renderWave();

void renderBoids();

void renderSubmarine();

void renderCorals(float vertices[][3], float verticesNormal[][3], int faces[][6], int coralFacesCount,
	float translateX, float translateY, float translateZ, float scaleX, float scaleY, float scaleZ);

void setMaterialHelper(GLfloat[], GLfloat[], GLfloat[], GLfloat);