#pragma once
#include <vector>

typedef unsigned long long ul;

void align(char**, int, int);

struct Numset
{
	ul num1;
	ul num2;
	ul res;
	int col;
	Numset(ul, ul, ul, int);
};

