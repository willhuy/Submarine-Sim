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
int subFacesCount;

// coral 1
float coral1Vertices[935][3];
float coral1VerticesNormal[935][3];
int coral1Faces[1866][6];
int coral1FacesCount;

// coral 2
float coral2Vertices[20902][3];
float coral2VerticesNormal[43182][3];
int coral2Faces[43185][6];
int coral2FacesCount;

// coral 3
float coral3Vertices[3810][3];
float coral3VerticesNormal[7616][3];
int coral3Faces[7616][6];
int coral3FacesCount;

// coral 4
float coral4Vertices[4179][3];
float coral4VerticesNormal[8833][3];
int coral4Faces[8834][6];
int coral4FacesCount;

// coral 5
float coral5Vertices[1871][3];
float coral5VerticesNormal[3738][3];
int coral5Faces[3738][6];
int coral5FacesCount;

// coral 6
float coral6Vertices[1374][3];
float coral6VerticesNormal[2744][3];
int coral6Faces[2744][6];
int coral6FacesCount;

// coral 7
float coral7Vertices[1820][3];
float coral7VerticesNormal[3635][3];
int coral7Faces[3636][6];
int coral7FacesCount;

// coral 8
float coral8Vertices[886][3];
float coral8VerticesNormal[1766][3];
int coral8Faces[1766][6];
int coral8FacesCount;

// coral 9
float coral9Vertices[1560][3];
float coral9VerticesNormal[2200][3];
int coral9Faces[2200][6];
int coral9FacesCount;

// coral 10
float coral10Vertices[3089][3];
float coral10VerticesNormal[6244][3];
int coral10Faces[6245][6];
int coral10FacesCount;

// coral 11
float coral11Vertices[1308][3];
float coral11VerticesNormal[2605][3];
int coral11Faces[2611][6];
int coral11FacesCount;

// coral 12
float coral12Vertices[2092][3];
float coral12VerticesNormal[4178][3];
int coral12Faces[4178][6];
int coral12FacesCount;

// coral 13
float coral13Vertices[2631][3];
float coral13VerticesNormal[5222][3];
int coral13Faces[5222][6];
int coral13FacesCount;

// coral 14
float coral14Vertices[3742][3];
float coral14VerticesNormal[7348][3];
int coral14Faces[7348][6];
int coral14FacesCount;


int vertexCount;
int vertexNormalCount;


// Texture related
// image size
int imageWidth, imageHeight;

// the image data
GLubyte* imageData;

int sandTextureID;

void loadObj(const char*, float vertices[][3], float verticesNormal[][3], int faces[][6], int* facesCount);

void loadTexture(const char*);