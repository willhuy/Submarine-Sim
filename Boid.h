#pragma once

#include <stdio.h>
#include <stdlib.h>

// Boid related macros
#define BOID_SIZE 0.03f
#define FLOCK_SIZE 20

#define BOID_BASE_SPEED 0.001f
#define MAX_SPEED 0.009f
#define SPEED_STEP 0.0001f

#define NUM_OF_NEAREST_NEIGHBORS 6
#define EDGE_AVOIDANCE_DISTANCE 0.05f
#define VELOCITY_CHANGE_CONSTANT 0.00001f
#define DIRECTION_CHANGE_CONSTANT 0.09f
#define MOVE_AWAY_CONSTANT 0.00001f
#define MIN_NEIGHBORS_DISTANCE 0.04f

// Randomization related macros
#define MAX_RANDOM_RANGE 0.5f
#define MIN_RANDOM_RANGE -0.3f
#define PI 3.14159265f

// boid struct
typedef struct Boid {
	float position[3];
	float acceleration[3];
	float velocity[3];
} Boid;

Boid currentFlock[FLOCK_SIZE];
Boid previousFlock[FLOCK_SIZE];
Boid nearestNeighbors[NUM_OF_NEAREST_NEIGHBORS];

float currentSetSpeed;

void initializeBoids();

void createBoids();