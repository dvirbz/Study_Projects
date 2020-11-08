#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ERROR -1
int countFires(char* forestString)
{
	int numberOfFires = 0;
	char currChar = *forestString;
	while (currChar != '\0')
	{
		if (currChar == 'F')
			numberOfFires++;
		forestString++;
		currChar = *forestString;
	}
}
int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Mismatching number of arguments: %d", argc);
		return ERROR;
	}
	char* forestString =argv[1];	
	return countFires(forestString);
}

























#endif