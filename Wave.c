#include "Wave.h"

void initializeWave() {
    // wave time
    waveDelta = 0.0;
    wavePhase = WAVE_PHASE;
    waveAmplitude = WAVE_AMPLITUDE;

    for (int i = 0; i < WAVE_GRID_SIZE; i++) {
        for (int j = 0; j < WAVE_GRID_SIZE; j++) {
            waveVertices[i][j][0] = (float)i - WAVE_GRID_SIZE / 2;
            waveVertices[i][j][1] = 0.0;
            waveVertices[i][j][2] = (float)j - WAVE_GRID_SIZE / 2;
        }
    }
}

void updateWave() {
    for (int i = 0; i < WAVE_GRID_SIZE; i++) {
        for (int j = 0; j < WAVE_GRID_SIZE; j++) {

            // Move along z axis
            float z = waveVertices[i][j][2];
            float valueBasedOnPosition = z;
            waveVertices[i][j][1] = sin(valueBasedOnPosition + wavePhase + waveDelta) * waveAmplitude;
        }

        // Random the phase
        wavePhase = ((float)rand() / RAND_MAX) * 0.09f + 0.01f;
    }

}