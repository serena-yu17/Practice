// Heron formula.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <string.h>
using namespace std;

double heron(int*);
int checkTriangle(int, int, int);

int main()
{
	while (1)
	{
		cout << "Input the lengths of 3 sides:" << endl;
		int length[3];
		char temp_str[1024];
		cin.getline(temp_str, 1024);
		int i = 0, count = 0;
		while (i < strlen(temp_str) && count < 3)
		{
			int buffer = 0;
			while (isdigit(temp_str[i]))
			{
				buffer *= 10;
				buffer += temp_str[i];
				i++;
			}
			if (buffer)
				length[count++] = buffer;
			i++;
		}
		if (!checkTriangle(length[0], length[1], length[2]))
		{
			cout << "This is not a valid triangle." << endl;
			continue;
		}
		double s = heron(length);
		cout << "The lengths of sides are: " << length[0] << ',' << length[1] << ',' << length[2] << ',' << '\n' << "The area is: " << s << endl;
		cin.clear();
		cin.ignore(10000, '\n');
	}
}

double heron(int* length)
{
	double p = (double)(length[0] + length[1] + length[2]) / 2;
	double s = sqrt(p*(p - length[0])*(p - length[1])*(p - length[2]));
	return s;
}

int checkTriangle(int a, int b, int c)
{
	if (a + b < c)
		return 0;
	if (a + c < b)
		return 0;
	if (b + c < a)
		return 0;
	return 1;
}