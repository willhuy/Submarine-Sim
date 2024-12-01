#pragma once

#include <freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Submarine.h"

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
GLfloat cameraPosition[3];
GLfloat shipPosition[3];
GLfloat distanceFromSubmarine;
GLfloat verticalAngle;
GLfloat horizontalAngle;
GLfloat horizontalSensitivity = 0.3f;
GLfloat verticalSensitivity = 0.3f;
GLfloat cameraRadius = 50.0f;
int lastMouseX = -1;
int lastMouseY = -1;

//  position the light source directly on top of origin
GLfloat lightPosition[] = { 1.0, 1.0, 1.0, 0.0 };

// white ball at origin
GLUquadric* originBall;


/* -- different type of materials -- */

// a material that is all zeros
GLfloat zeroMaterial[] = { 0.0, 0.0, 0.0, 1.0 };

// a blue diffuse material
GLfloat blueDiffuse[] = { 0.1, 0.5, 0.8, 1.0 };

// a red diffuse material
GLfloat redDiffuse[] = { 1.0, 0.0, 0.0, 1.0 };

// a green diffuse material
GLfloat greenDiffuse[] = { 0.0, 1.0, 0.0, 1.0 };

// a white diffuse material
GLfloat whiteDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };

// a yellow diffuse material for submarine
GLfloat yellowDiffuse[] = { 1.0, 1.0, 0.0, 1.0 };


// shininess
GLfloat noShininess = 0.0;
GLfloat highShininess = 100.0;

// window dimensions
GLint windowWidth = WIDTH;
GLint windowHeight = HEIGHT;
int fullscreen = 0;

void printMenu();

void myDisplay();

void myKey(unsigned char, int, int);

void mySpecialKey(unsigned char, int, int);

void myMouseMotion(int, int);

void initializeGL();

void myResize(int, int);

void update();

void renderCoorAxis();

void initScene();

void renderSubmarine();

void setMaterialHelper(GLfloat[], GLfloat[], GLfloat[], GLfloat);