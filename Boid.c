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



