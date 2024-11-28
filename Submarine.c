#include "Submarine.h"

void loadSubmarine(const char* fileName) {
    FILE* file = fopen(fileName, "r");

    if (!file) {
        printf("Could not open file\n");
        exit(1);
    }

    vertexCount = 0;
    vertexNormalCount = 0;
    facesCount = 0;

    char line[128];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'v' && line[1] == ' ') {
            // Parse vertex
            sscanf_s(line, "v %f %f %f", &vertices[vertexCount][0], &vertices[vertexCount][1], &vertices[vertexCount][2]);
            vertexCount++;
        }
        else if (line[0] == 'v' && line[1] == 'n') {
            // Parse vertex normal
            sscanf_s(line, "vn %f %f %f", &verticesNormal[vertexNormalCount][0], &verticesNormal[vertexNormalCount][1], &verticesNormal[vertexNormalCount][2]);
            vertexNormalCount++;
        }
        else if (line[0] == 'f') {
            // Parse faces
            sscanf_s(line, "f %d//%d %d//%d %d//%d", &faces[facesCount][0], &faces[facesCount][1], &faces[facesCount][2], &faces[facesCount][3], &faces[facesCount][4], &faces[facesCount][5]);
            facesCount++;
        }
    }

    fclose(file);
}