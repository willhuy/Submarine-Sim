#include "FileIO.h"

void loadObj(const char* fileName, float vertices[][3], float verticesNormal[][3], int faces[][6], int* objFacesCount) {
    FILE* file = fopen(fileName, "r");

    if (!file) {
        printf("Could not open file %s\n", fileName);
        exit(1);
    }

    vertexCount = 0;
    vertexNormalCount = 0;
    int facesCount = 0;

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

	*objFacesCount = facesCount;

    fclose(file);
}

void loadTexture(const char* fileName) {
	// the ID of the image file
	FILE* fileID;

	// maxValue
	int  maxValue;

	// total number of pixels in the image
	int  totalPixels;

	// temporary character
	char tempChar;

	// counter variable for the current pixel in the image
	int i;

	// array for reading in header information
	char headerLine[100];

	// if the original values are larger than 255
	float RGBScaling;

	// temporary variables for reading in the red, green and blue data of each pixel
	int red, green, blue;

	// open the image file for reading
	fileID = fopen(fileName, "r");

	// read in the first header line
	//    - "%[^\n]"  matches a string of all characters not equal to the new line character ('\n')
	//    - so we are just reading everything up to the first line break
	fscanf(fileID, "%[^\n] ", headerLine);

	// make sure that the image begins with 'P3', which signifies a PPM file
	if ((headerLine[0] != 'P') || (headerLine[1] != '3'))
	{
		printf("This is not a PPM file!\n");
		exit(0);
	}

	// we have a PPM file
	printf("This is a PPM file\n");

	// read in the first character of the next line
	fscanf(fileID, "%c", &tempChar);

	// while we still have comment lines (which begin with #)
	while (tempChar == '#')
	{
		// read in the comment
		fscanf(fileID, "%[^\n] ", headerLine);

		// print the comment
		printf("%s\n", headerLine);

		// read in the first character of the next line
		fscanf(fileID, "%c", &tempChar);
	}

	// the last one was not a comment character '#', so we need to put it back into the file stream (undo)
	ungetc(tempChar, fileID);

	// read in the image hieght, width and the maximum value
	fscanf(fileID, "%d %d %d", &imageWidth, &imageHeight, &maxValue);

	// print out the information about the image file
	printf("%d rows  %d columns  max value= %d\n", imageHeight, imageWidth, maxValue);

	// compute the total number of pixels in the image
	totalPixels = imageWidth * imageHeight;

	// allocate enough memory for the image  (3*) because of the RGB data
	imageData = malloc(3 * sizeof(GLuint) * totalPixels);


	// determine the scaling for RGB values
	RGBScaling = 255.0 / maxValue;


	// if the maxValue is 255 then we do not need to scale the 
	//    image data values to be in the range or 0 to 255
	if (maxValue == 255)
	{
		for (i = 0; i < totalPixels; i++)
		{
			// read in the current pixel from the file
			fscanf(fileID, "%d %d %d", &red, &green, &blue);

			// store the red, green and blue data of the current pixel in the data array
			imageData[3 * totalPixels - 3 * i - 3] = red;
			imageData[3 * totalPixels - 3 * i - 2] = green;
			imageData[3 * totalPixels - 3 * i - 1] = blue;
		}
	}
	else  // need to scale up the data values
	{
		for (i = 0; i < totalPixels; i++)
		{
			// read in the current pixel from the file
			fscanf(fileID, "%d %d %d", &red, &green, &blue);

			// store the red, green and blue data of the current pixel in the data array
			imageData[3 * totalPixels - 3 * i - 3] = red * RGBScaling;
			imageData[3 * totalPixels - 3 * i - 2] = green * RGBScaling;
			imageData[3 * totalPixels - 3 * i - 1] = blue * RGBScaling;
		}
	}


	// close the image file
	fclose(fileID);
}