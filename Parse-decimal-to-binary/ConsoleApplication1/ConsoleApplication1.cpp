// ConsoleApplication1.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <cstdio>
#include "limits.h"
using namespace std;

char* parseBinary(unsigned long dec, char*);
const int dig = CHAR_BIT * sizeof(unsigned long);

int main()
{
	while (1) {
		printf("Input you decimal number:\n");
		unsigned long decimal;
		scanf("%ud", &decimal);
		char arrBinary[dig];
		char* binary = parseBinary(decimal, arrBinary);
		printf("%s\n", binary);
	}
}
char* parseBinary(unsigned long dec, char* bin) {
	int i = dig -1;
	while (dec > 0)	{
		bin[i] = (dec & 1) + '0';
		dec >>= 1;
		i--;
	}
	bin[dig] = 0;
	while (*bin != '1')
		bin++;
	return bin;
}
