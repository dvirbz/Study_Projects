#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define ERROR -1
#define COMMAFACTOR 2
#define DECIMALBASE 10
enum Forest{
	Ground,
	Fire,
	Tree
};
int getSquareInt(char c)
{
	int square;
	switch (c)
	{
	case 'F':square = Fire;
		break;
	case 'G':square = Ground;
		break;
	case 'T':square = Tree;
	default:square = ERROR;
		break;
	}
	return square;
}
char* getSquareChar(int square , char *squareC)
{
	
	switch (square)
	{
	case Fire:strcpy(squareC, "F");
		break;
	case Ground:strcpy(squareC, "G");
		break;
	case Tree: strcpy(squareC,"T");	
		break;
	}
	return squareC;
}
void setForestDimension(char *firstLine, int* forestDimension, char* secondLine, int* generations)
{
	*forestDimension = (int)strtol(firstLine, (char**)NULL, DECIMALBASE);
	*generations = (int)strtol(secondLine, (char**)NULL, DECIMALBASE);
}
void advanceForest(int **forestArray,int forestDimension)
{
	for (int i = 0; i < forestDimension; i++)
	{
		for (int j = 0; j < forestDimension; j++)
		{
			//forestArray + i*forestDimension + j;
		}
	}
}
int calculateNextGenSquare(int** forestArray, int forestDimension, int row, int coulmn)
{
	if (**(forestArray + row * forestDimension + coulmn) == Fire)
		return Ground;
	int numberOfTree = 0;
	for (int i = min(0, row - 1); i <= max(forestDimension - 1, row + 1); i++)
	{
		for (int j = min(0, coulmn - 1); j <= max(forestDimension - 1, coulmn + 1); j++)
		{
			//check if fire is near
			if ((j != coulmn && i != row) && **(forestArray + i * forestDimension + j) == Fire)
				return Fire;
			if (**(forestArray + i * forestDimension + j) == Tree)
				numberOfTree++;
		}
	}
	if (numberOfTree >= 2)
		return Tree;
	return **(forestArray + row * forestDimension + coulmn);
}
void getForestLineFrom2DArray(int** forestArray, int forestDimension, char* forestLine)
{
	char* squareC = (char*)malloc(sizeof(char));
	strcpy(forestLine, "\0");
	for (int i = 0; i < forestDimension; i++)
	{
		for (int j = 0; j < forestDimension; j++)
		{
			strcat(forestLine, getSquareChar(**(forestArray + i * forestDimension + j),squareC));
		}
	}	
	free(squareC);
}
int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Mismatching number of arguments: %d", argc);
		return ERROR;
	}
	FILE* forest = fopen(argv[1], "r");
	if (forest == NULL)
	{
		printf("File could'nt be opened");
		return ERROR;
	}
	char* firstLine = fgets("\n", 1, forest);
	char* SecondLine = fgets("\n", 1, forest);
	int* forestDimension = (int*)malloc(sizeof(int));
	int* generations = (int*)malloc(sizeof(int));

	setForestDimension(firstLine, forestDimension, SecondLine, generations);

	int** forestArray = (int**)malloc(sizeof(int) * (*forestDimension) * (*forestDimension));
	char* line = (char*)malloc(sizeof(char) * (*forestDimension) * COMMAFACTOR);
	char* forestLine = (char*)malloc(sizeof(char) * (*forestDimension) * (*forestDimension));
	char* square = (char*)malloc(sizeof(char));
	strcpy(forestLine, "\0");
	for (int i = 0; i < *forestDimension && line != NULL; i++)
	{
		line = fgets("\n", *(forestDimension) * COMMAFACTOR, forest);
		square = strtok(line, ",");
		strcat(forestLine, square);
		//update 2D array in the correct position Row,0
		while (square != NULL)
		{
			square = strtok(NULL, ",");
			strcat(forestLine, square);
			//update 2D array in the correct position
		}

		//lishloach lason
		int numberOfFires = 0;
		if (numberOfFires == ERROR)
		{
			printf("ERROR");
			return ERROR;
		}
	}
	//AdvanceGeneration();
	(*generations)--;
	while (*generations != 0)
	{
		//getForestLineFrom2DArray();
		//lishloach lason
		//Print to Output
		//AdvanceGeneration();
		(*generations)--;
	}
}














#endif