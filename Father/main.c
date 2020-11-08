#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ERROR -1

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Mismatcing number of arguments: %d", argc);
		return -1;
	}
	FILE* forest = fopen (argv[1], "r");
	char *firstLine = fgets("\n", 1, forest);
	char *SecondLine = fgets("\n", 1, forest);
	int* forestDimension;
	int* generations;
	char *str;
	char* forestString = (char*)malloc(sizeof(char) * (*forestDimension) * (*forestDimension));
	strcpy(forestString, "");
	for (int i = 0; i< *forestDimension && str != NULL; i++)
	{
		str = fgets("\n", *forestDimension*2, forest);
		str = strtok_s(str, ",","");
		strcat(forestString, str);
		//lishloach lason
		int numberOfFires;
		if (numberOfFires == -1)
		{
			printf("ERROR");
			return ERROR;
		}


	}
}
#endif