#include "Boid.h"

void initializeBoids() {
	for (int i = 0; i < FLOCK_SIZE; i++) {
		currentFlock[i].position[0] = ((float)rand() / RAND_MAX) * 100 - 50; // Random x between -50 and 50
		currentFlock[i].position[1] = ((float)rand() / RAND_MAX) * 100 - 0; // Random y between 0 and 50
		currentFlock[i].position[2] = ((float)rand() / RAND_MAX) * 100 - 50; // Random z between -50 and 50

		currentFlock[i].velocity[0] = ((float)rand() / RAND_MAX) * 2 - 1; // Random x velocity between -1 and 1
		currentFlock[i].velocity[1] = ((float)rand() / RAND_MAX) * 2 - 1;
		currentFlock[i].velocity[2] = ((float)rand() / RAND_MAX) * 2 - 1;

		currentFlock[i].acceleration[0] = currentFlock[i].acceleration[1] = currentFlock[i].acceleration[2] = 0.0f;
	}

	// Initiallize current speed
	currentSetSpeed = BOID_BASE_SPEED;
}

void updateBoids() {
	// Copy boids from current to previous flock
	for (int boidIndex = 0; boidIndex < FLOCK_SIZE; boidIndex++) {
		previousFlock[boidIndex] = currentFlock[boidIndex];
	}

	for (int boidIndex = 0; boidIndex < FLOCK_SIZE; boidIndex++) {
		// Find nearest neighbors
		findNearestNeighbors(&previousFlock[boidIndex], boidIndex, &nearestNeighbors);

		avoidCylinderBoundary(boidIndex);

		alignWithNearestNeighborDirection(boidIndex);

		moveAwayFromNearestNeighbor(boidIndex);

		speedLimit(&currentFlock[boidIndex]);
		currentFlock[boidIndex].position[0] += currentFlock[boidIndex].velocity[0]; // x coor
		currentFlock[boidIndex].position[1] += currentFlock[boidIndex].velocity[1]; // y coor
		currentFlock[boidIndex].position[2] += currentFlock[boidIndex].velocity[2]; // z coor
	}
}

void findNearestNeighbors(Boid* currentBoid, int indexOfCurrentBoid) {

	// Iterate through all boids
	float minDistance = 9999.0f;
	float distance[FLOCK_SIZE] = { 0 };
	for (int boidIndex = 0; boidIndex < FLOCK_SIZE; boidIndex++) {

		// Skip itself
		if (boidIndex == indexOfCurrentBoid) {
			distance[boidIndex] = -1; // Euclidean distance can't be negative
			continue;
		}

		// Find euclidean distance
		distance[boidIndex] = findEuclideanDistance(currentBoid->position[0], previousFlock[boidIndex].position[0],
			currentBoid->position[1], previousFlock[boidIndex].position[1], currentBoid->position[2], previousFlock[boidIndex].position[2]);
	}

	for (int nearestNeighborIndex = 0; nearestNeighborIndex < NUM_OF_NEAREST_NEIGHBORS; nearestNeighborIndex++) {
		int minDistanceIndex = 0;
		for (int boidIndex = 0; boidIndex < FLOCK_SIZE; boidIndex++) {
			if (distance[boidIndex] < minDistance && distance[boidIndex] != -1) {
				minDistance = distance[boidIndex];
				minDistanceIndex = boidIndex;
			}
		}

		// Add the Boid from the flock mith min distance to the list
		nearestNeighbors[nearestNeighborIndex] = previousFlock[minDistanceIndex];
		distance[minDistanceIndex] = -1; // Flag the value has been recorded
		minDistance = 9999.0f; // Reset minDistance
	}
}

float findEuclideanDistance(float x1, float x2, float y1, float y2, float z1, float z2) {
	float xDistance = x1 - x2;
	float yDistance = y1 - y2;
	float zDistance = z1 - z2;
	return sqrt(pow(xDistance, 2) + pow(yDistance, 2) + pow(zDistance, 2));
}

void avoidCylinderBoundary(int boidIndex) {

	// Approaching positive x axis limit
	float distanceToPosXLimit = findEuclideanDistance(-70.0f, previousFlock[boidIndex].position[0], 0.0f, 0.0f, 0.0f, 0.0f);
	if (distanceToPosXLimit <= EDGE_AVOIDANCE_DISTANCE) {
		currentFlock[boidIndex].velocity[0] += (1.0f / distanceToPosXLimit) * VELOCITY_CHANGE_CONSTANT; // Update xVelocity
	}

	// Approaching negative x axis limit
	float distanceToNegXLimit = findEuclideanDistance(70.0f, previousFlock[boidIndex].position[0], 0.0f, 0.0f, 0.0f, 0.0f);
	if (distanceToNegXLimit <= EDGE_AVOIDANCE_DISTANCE) {
		currentFlock[boidIndex].velocity[0] -= (1.0f / distanceToNegXLimit) * VELOCITY_CHANGE_CONSTANT; // Update xVelocity
	}

	// Approaching positive y axis limit
	float distanceToPosYLimit = findEuclideanDistance(0.0f, 0.0f, 0.0f, previousFlock[boidIndex].position[1], 0.0f, 0.0f);
	if (distanceToPosYLimit <= EDGE_AVOIDANCE_DISTANCE) {
		currentFlock[boidIndex].velocity[1] += (1.0f / distanceToPosYLimit) * VELOCITY_CHANGE_CONSTANT; // Update xVelocity
	}

	// Approaching negative y axis limit
	float distanceToNegYLimit = findEuclideanDistance(0.0f, 0.0f, 90.0f, previousFlock[boidIndex].position[1], 0.0f, 0.0f);
	if (distanceToNegYLimit <= EDGE_AVOIDANCE_DISTANCE) {
		currentFlock[boidIndex].velocity[1] -= (1.0f / distanceToNegYLimit) * VELOCITY_CHANGE_CONSTANT; // Update xVelocity
	}

	// Approaching positive z axis limit
	float distanceToPosZLimit = findEuclideanDistance(0.0f, 0.0f, 0.0f, 0.0f, -70.0f, previousFlock[boidIndex].position[2]);
	if (distanceToPosZLimit <= EDGE_AVOIDANCE_DISTANCE) {
		currentFlock[boidIndex].velocity[2] += (1.0f / distanceToPosZLimit) * VELOCITY_CHANGE_CONSTANT; // Update xVelocity
	}

	// Approaching negative z axis limit
	float distanceToNegZLimit = findEuclideanDistance(0.0f, 0.0f, 0.0f, 0.0f, 70.0f, previousFlock[boidIndex].position[2]);
	if (distanceToNegZLimit <= EDGE_AVOIDANCE_DISTANCE) {
		currentFlock[boidIndex].velocity[2] -= (1.0f / distanceToNegZLimit) * VELOCITY_CHANGE_CONSTANT; // Update xVelocity
	}

	speedLimit(&currentFlock[boidIndex]);
}

void speedLimit(Boid* boid) {
	float magnitude = findEuclideanDistance(boid->velocity[0], 0, boid->velocity[1], 0, boid->velocity[2], 0);
	if (boid->velocity[0] > currentSetSpeed) {
		boid->velocity[0] = (boid->velocity[0] / magnitude) * currentSetSpeed;
	}

	if (boid->velocity[1] > currentSetSpeed) {
		boid->velocity[1] = (boid->velocity[1] / magnitude) * currentSetSpeed;
	}

	if (boid->velocity[2] > currentSetSpeed) {
		boid->velocity[2] = (boid->velocity[2] / magnitude) * currentSetSpeed;
	}

	if (boid->velocity[0] < currentSetSpeed) {
		boid->velocity[0] = (boid->velocity[0] / magnitude) * currentSetSpeed;
	}

	if (boid->velocity[1] < currentSetSpeed) {
		boid->velocity[1] = (boid->velocity[1] / magnitude) * currentSetSpeed;
	}

	if (boid->velocity[2] < currentSetSpeed) {
		boid->velocity[2] = (boid->velocity[2] / magnitude) * currentSetSpeed;
	}
}

void alignWithNearestNeighborDirection(int boidIndex) {
	//printf("Boid %d align\n", boidIndex);
	// Average all the nearest neighbor x and y component
	float sumX = 0, sumY = 0, sumZ = 0, avgX = 0, avgY = 0, avgZ = 0;
	for (int neighborIndex = 0; neighborIndex < NUM_OF_NEAREST_NEIGHBORS; neighborIndex++) {
		sumX += nearestNeighbors[neighborIndex].velocity[0];
		sumY += nearestNeighbors[neighborIndex].velocity[1];
		sumZ += nearestNeighbors[neighborIndex].velocity[2];
	}

	avgX = sumX / NUM_OF_NEAREST_NEIGHBORS;
	avgY = sumY / NUM_OF_NEAREST_NEIGHBORS;
	avgZ = sumZ / NUM_OF_NEAREST_NEIGHBORS;

	// Gradually align with the nearest neighbors's direction
	currentFlock[boidIndex].velocity[0] = (1 - DIRECTION_CHANGE_CONSTANT) * currentFlock[boidIndex].velocity[0] + DIRECTION_CHANGE_CONSTANT * avgX;
	currentFlock[boidIndex].velocity[1] = (1 - DIRECTION_CHANGE_CONSTANT) * currentFlock[boidIndex].velocity[1] + DIRECTION_CHANGE_CONSTANT * avgY;
	currentFlock[boidIndex].velocity[2] = (1 - DIRECTION_CHANGE_CONSTANT) * currentFlock[boidIndex].velocity[2] + DIRECTION_CHANGE_CONSTANT * avgZ;

	speedLimit(&currentFlock[boidIndex]);
}

void moveAwayFromNearestNeighbor(int boidIndex) {
	float distanceToNeighborHorizontal = -1.0f;
	float distanceToNeighborVertical = -1.0f;
	for (int neighborIndex = 0; neighborIndex < NUM_OF_NEAREST_NEIGHBORS; neighborIndex++) {

		// Approaching neighbor on x axis => update xVelocity
		distanceToNeighborHorizontal = findEuclideanDistance(nearestNeighbors[neighborIndex].position[0], previousFlock[boidIndex].position[0], 0, 0, 0, 0);
		if (distanceToNeighborHorizontal <= MIN_NEIGHBORS_DISTANCE) {
			//printf("Boid %d move horizontal\n", boidIndex);
			// Neighbor on the left

			if (nearestNeighbors[neighborIndex].position[0] < previousFlock[boidIndex].position[0]) {
				currentFlock[boidIndex].velocity[0] += (1.0f / distanceToNeighborHorizontal) * MOVE_AWAY_CONSTANT;
			}
			else { // right
				currentFlock[boidIndex].velocity[0] -= (1.0f / distanceToNeighborHorizontal) * MOVE_AWAY_CONSTANT;
			}
		}

		// Approaching neighbor on y axis => update yVelocity
		distanceToNeighborVertical = findEuclideanDistance(0, 0, nearestNeighbors[neighborIndex].position[1], previousFlock[boidIndex].position[1], 0, 0);
		if (distanceToNeighborVertical <= MIN_NEIGHBORS_DISTANCE) {
			//printf("Boid %d move vertical\n", boidIndex);

			// Neighbor on the bottom
			if (nearestNeighbors[neighborIndex].position[1] < previousFlock[boidIndex].position[1]) {
				currentFlock[boidIndex].velocity[1] += (1.0f / distanceToNeighborVertical) * MOVE_AWAY_CONSTANT;
			}
			else { // top
				currentFlock[boidIndex].velocity[1] -= (1.0f / distanceToNeighborVertical) * MOVE_AWAY_CONSTANT;
			}
		}

		// Approaching neighbor on z axis => update zVelocity
		distanceToNeighborVertical = findEuclideanDistance(0, 0, nearestNeighbors[neighborIndex].position[2], previousFlock[boidIndex].position[2], 0, 0);
		if (distanceToNeighborVertical <= MIN_NEIGHBORS_DISTANCE) {
			//printf("Boid %d move vertical\n", boidIndex);

			// Neighbor on the bottom
			if (nearestNeighbors[neighborIndex].position[2] < previousFlock[boidIndex].position[2]) {
				currentFlock[boidIndex].velocity[2] += (1.0f / distanceToNeighborVertical) * MOVE_AWAY_CONSTANT;
			}
			else { // top
				currentFlock[boidIndex].velocity[2] -= (1.0f / distanceToNeighborVertical) * MOVE_AWAY_CONSTANT;
			}
		}
	}

	speedLimit(&currentFlock[boidIndex]);
}

