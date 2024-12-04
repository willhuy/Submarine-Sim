#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Boid related macros
#define BOID_SIZE 0.03f
#define FLOCK_SIZE 100

#define BOID_BASE_SPEED 0.5f
#define MAX_SPEED 1.0f
#define SPEED_STEP 0.01f

#define NUM_OF_NEAREST_NEIGHBORS 5
#define EDGE_AVOIDANCE_DISTANCE 2.0f
#define VELOCITY_CHANGE_CONSTANT 0.5f
#define DIRECTION_CHANGE_CONSTANT 0.5f
#define MOVE_AWAY_CONSTANT 0.5f
#define MIN_NEIGHBORS_DISTANCE 1.0f

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

void updateBoids();

void avoidCylinderBoundary(int boidIndex);

void findNearestNeighbors(Boid*, int);

float findEuclideanDistance(float, float, float, float, float, float);

void speedLimit(Boid*);

void alignWithNearestNeighborDirection(int);

void moveAwayFromNearestNeighbor(int);