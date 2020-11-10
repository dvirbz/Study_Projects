#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ERROR_CODE -1
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
	return numberOfFires;
}
int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Mismatching number of arguments: %d", argc);
		return ERROR_CODE;
	}
	char* forestString =argv[1];	
	int fires = countFires(forestString);
	printf("Num = %d\n", fires);
	return fires;
}

























#endif