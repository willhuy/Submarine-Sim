#pragma once

#include <freeglut.h>

#define AXIS_WIDTH 5.0f
#define Z_SUBDIVISION 100

GLUquadric* originBall;

void renderCoorAxis();

void initScene();