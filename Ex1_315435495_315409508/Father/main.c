#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "HardCodedData.h"
#include "father_func.h"
#include "sonProcessCreation.h"

void WriteToOutput(FILE* output, char* forestLine, int numberOfFires)
{	
	sprintf(forestLine, "%s - %d", forestLine, numberOfFires);
	fputs(forestLine,output);
}
int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Mismatching number of arguments: %d", argc);
		return ERROR_CODE;
	}
	FILE* inputF, *outputF;
	inputF = fopen(argv[1], "r");
	if (inputF == NULL)
	{
		printf("File could'nt be opened1");
		return ERROR_CODE;
	}
	char* firstLine = (char*)malloc(sizeof(char)* MAX_LINE_LENGTH);
	char* SecondLine = (char*)malloc(sizeof(char)* MAX_LINE_LENGTH);
	int* forestDimension = (int*)malloc(sizeof(int));
	int* generations = (int*)malloc(sizeof(int));

	if (fgets(firstLine, MAX_LINE_LENGTH, inputF) == NULL)
		return ERROR_CODE;
	if (fgets(SecondLine, MAX_LINE_LENGTH, inputF) == NULL)
		return ERROR_CODE;
	setForestDimension(firstLine, forestDimension, SecondLine, generations);

	int** forestArray = (int**)malloc(sizeof(int*) * (*forestDimension));
	char* line = (char*)malloc(sizeof(char) * ((*forestDimension) * COMMAFACTOR + END_OF_LINE_FACTOR));
	char* forestLine = (char*)calloc(sizeof(char),(*forestDimension) * (*forestDimension));
	char* square = (char*)malloc(sizeof(char));

	init2DArray(forestArray, *forestDimension, *forestDimension);
	//strcpy(forestLine, END_OF_LINE);
	for (int i = 0; i < *forestDimension && line != NULL; i++)
	{
		if (fgets(line, (*forestDimension) * COMMAFACTOR + END_OF_LINE_FACTOR, inputF) == NULL)
			return ERROR_CODE;
		updateArrayAndLine(line, forestLine, forestArray, i, *forestDimension);		
	}
	fclose(inputF);
	int numberOfFires = CreateProcessSon(forestLine);
	if (numberOfFires == ERROR_CODE)
	{
		printf("ERROR");
		return ERROR_CODE;
	}

	outputF = fopen("output.txt", "w");
	if (outputF == NULL)
	{
		printf("File could'nt be opened");
		return ERROR_CODE;
	}
	printf("%s - %d\n", forestLine, *generations);	
	WriteToOutput(outputF, forestLine, numberOfFires);
	
	advanceForestgenertaion(forestArray, *forestDimension);
	(*generations)--;

	while (*generations != 0)
	{
		fputs("\n", outputF);
		getForestLineFrom2DArray(forestArray,*forestDimension,forestLine);
		printf("%s - %d\n", forestLine, *generations);
		numberOfFires = CreateProcessSon(forestLine);
		WriteToOutput(outputF, forestLine, numberOfFires);

		advanceForestgenertaion(forestArray, *forestDimension);		
		(*generations)--;
	}
	fclose(outputF);
	free2DArray(forestArray, *forestDimension, *forestDimension);
	free(firstLine);
	free(SecondLine);
	free(forestDimension);
	free(generations);
	free(line);
	free(forestLine);
	free(square);
	
}

#endif