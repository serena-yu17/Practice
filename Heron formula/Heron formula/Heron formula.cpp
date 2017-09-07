// Heron formula.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
using namespace std;

double heron(int*);
int checkTriangle(int, int, int);

int main()
{
	while (1)
	{
		cout << "Input the lengths of 3 sides:" << endl;
		int length[3];
		char temp_str[256], segment[256];
		cin.getline(temp_str, 256);
		int i = 0, j = 0, count = 0;
		while (i < strlen(temp_str) && count < 3)
		{
			while (isdigit(temp_str[i]))
			{
				segment[j] = temp_str[i];
				i++; 
				j++;
			}
			segment[j + 1] = '\0';
			length[count] = stoi(segment);
			count++;
			j = 0;
			memset(segment, 0, 256);
			while (i < strlen(temp_str) && !isdigit(temp_str[i]))
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
	int flag = 1;
	if (a + b < c)
		flag = 0;
	if (a + c < b)
		flag = 0;
	if (b + c < a)
		flag = 0;
	return flag;
}