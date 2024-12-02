#pragma once

#define _CRT_SECURE_NO_DEPRECATE

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <freeglut.h>

// Submarine related
float vertices[17781][3];
float verticesNormal[14463][3];
int faces[34123][6];
int vertexCount;
int vertexNormalCount;
int facesCount;

// Texture related
// image size
int imageWidth, imageHeight;

// the image data
GLubyte* imageData;

int sandTextureID;

void loadSubmarine(const char*);

void loadTexture(const char*);