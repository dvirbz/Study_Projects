#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "HardCodedData.h"
void zero2DArray(int** dest, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			dest[i][j] = 0;
		}
	}
}
void init2DArray(int** dest, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		dest[i] = (int*)malloc(sizeof(int) * cols);
	}
	zero2DArray(dest, rows, cols);
}
void free2DArray(int** dest, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		free(dest[i]);
	}
	free(dest);
}
void copy2DArrat(int** dest, int** src, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			dest[i][j] = src[i][j];
		}
	}
}

int getSquareInt(char* c)
{
	if (!strcmp(c, "F"))
		return FIRE;
	if (!strcmp(c, "G"))
		return GROUND;
	if (!strcmp(c, "T"))
		return TREE;
	return ERROR_CODE;
}
char* getSquareChar(int square, char* squareC)
{
	switch (square)
	{
	case FIRE:strcpy(squareC, "F");
		break;
	case GROUND:strcpy(squareC, "G");
		break;
	case TREE: strcpy(squareC, "T");
		break;
	}
	return squareC;
}
void setForestDimension(char* firstLine, int* forestDimension, char* secondLine, int* generations)
{
	*forestDimension = (int)strtol(firstLine, (char**)NULL, DECIMALBASE);
	*generations = (int)strtol(secondLine, (char**)NULL, DECIMALBASE);
}
void getForestLineFrom2DArray(int** forestArray, int forestDimension, char* forestLine)
{
	char* tmpC = (char*)malloc(sizeof(char) * (1 + END_OF_LINE_FACTOR));
	strcpy(forestLine, "\0");
	for (int i = 0; i < forestDimension; i++)
	{
		for (int j = 0; j < forestDimension; j++)
		{
			strcat(forestLine, getSquareChar(forestArray[i][j], tmpC));
		}
	}
	free(tmpC);
}

int calculateNextGenSquare(int** forestArray, int forestDimension, int row, int coulmn)
{
	int thisSquare = forestArray[row][coulmn];
	if (thisSquare == FIRE)
		return GROUND;
	int numberOfTree = 0;
	for (int i = max(0, row - 1); i <= min(forestDimension - 1, row + 1); i++)
	{
		for (int j = max(0, coulmn - 1); j <= min(forestDimension - 1, coulmn + 1); j++)
		{
			//check if fire is near
			if (thisSquare == TREE && (!(j != coulmn && i != row)) && forestArray[i][j] == FIRE)
				return FIRE;
			if (forestArray[i][j] == TREE && (j != coulmn || i != row))
				numberOfTree++;
		}
	}
	if (numberOfTree >= 2)
		return TREE;
	return thisSquare;
}
void updateArrayAndLine(char* line, char* forestLine, int** forestArray, int row, int dimension)
{
	char* squareC = (char*)malloc(sizeof(char));
	squareC = strtok(line, ",\n");
	int j = 0;
	while (squareC != NULL && strcmp(squareC, "\n"))
	{
		strcat(forestLine, squareC);
		forestArray[row][j] = getSquareInt(squareC);
		j++;
		squareC = strtok(NULL, ",\n");
	}
	free(squareC);
}
void advanceForestgenertaion(int** forestArray, int forestDimension)
{
	int** tempArray = (int**)malloc(sizeof(int) * forestDimension * forestDimension);
	if (tempArray == NULL)
		return;
	init2DArray(tempArray, forestDimension, forestDimension);
	for (int i = 0; i < forestDimension; i++)
	{
		for (int j = 0; j < forestDimension; j++)
		{
			tempArray[i][j] = calculateNextGenSquare(forestArray, forestDimension, i, j);
		}
	}
	copy2DArrat(forestArray, tempArray, forestDimension, forestDimension);
	free(tempArray);
}

#endif