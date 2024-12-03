#pragma once

#include <freeglut.h>
#include <math.h>
#include <time.h>

// Wave related macros
#define WAVE_GRID_SIZE 100
#define WAVE_AMPLITUDE 1.5f
#define WAVE_SPEED 0.05f
#define WAVE_PHASE 0.5f

GLfloat waveVertices[WAVE_GRID_SIZE][WAVE_GRID_SIZE][3];

// wave related variables
float waveDelta;
float waveAmplitude;
float wavePhase;

void initializeWave();

void updateWave();