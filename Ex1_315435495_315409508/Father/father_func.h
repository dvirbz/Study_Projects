#pragma once
#ifndef FATHER_FUNC
#define FATHER_FUNC
void zero2DArray(int** dest, int rows, int cols);
void init2DArray(int** dest, int rows, int cols);
void free2DArray(int** dest, int rows, int cols);
void copy2DArrat(int** dest, int** src, int rows, int cols);

int getSquareInt(char* c);
char* getSquareChar(int square, char* squareC);
void setForestDimension(char* firstLine, int* forestDimension, char* secondLine, int* generations);

void getForestLineFrom2DArray(int** forestArray, int forestDimension, char* forestLine);
int calculateNextGenSquare(int** forestArray, int forestDimension, int row, int coulmn);

void updateArrayAndLine(char* line, char* forestLine, int** forestArray, int row, int dimension);
void advanceForestgenertaion(int** forestArray, int forestDimension);

#endif 
