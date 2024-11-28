#pragma once

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

float vertices[17781][3];
float verticesNormal[14463][3];
int faces[34123][6];

int vertexCount;
int vertexNormalCount;
int facesCount;

void loadSubmarine(const char*);