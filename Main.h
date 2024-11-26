#pragma once

#include <freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Scene.h"

// GLUT related macros
#define FRAME_EXIST_TIME 1000 / 60
#define WIDTH 900
#define HEIGHT 600
#define Z_NEAR 0.1f 
#define Z_FAR 10000.0f
#define CAMERA_INCREMENT 0.1f

// window dimensions
GLint windowWidth = WIDTH;
GLint windowHeight = HEIGHT;
int fullscreen = 0;

// Initial camera position
GLfloat cameraPosition[] = { 0, 0.5, 5 };
GLdouble cameraCenterX = 0;
GLdouble cameraCenterY = 0;
GLdouble cameraCenterZ = 0;

void printMenu();

void myDisplay();

void myKey(unsigned char, int, int);

void mySpecialKey(unsigned char, int, int);

void initializeGL();

void myResize(int, int);

void update();