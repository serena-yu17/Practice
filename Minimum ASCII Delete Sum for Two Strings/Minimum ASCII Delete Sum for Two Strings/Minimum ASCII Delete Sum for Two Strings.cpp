// Minimum ASCII Delete Sum for Two Strings.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <string>
#include <sstream>
using namespace std;

// Helper function to calculate min of 3 int
inline int min3(int a, int b, int c)
{
	int minab = a < b ? a : b;
	return minab < c ? minab : c;
} 

int minimumDeleteSum(const char* first, const char* second)
{
	int len1 = strlen(first);
	int len2 = strlen(second);
	int* marksRow1 = (int*)malloc(sizeof(*marksRow1) * (len2 + 1));
	int* marksRow2 = (int*)malloc(sizeof(*marksRow2) * (len2 + 1));
	marksRow1[0] = 0;
	for (int x = 1; x < len2 + 1; x++)
		marksRow1[x] = marksRow1[x - 1] + second[x - 1];
	for (int y = 0; y < len1; y++)
	{
		marksRow2[0] = marksRow1[0] + first[y];			// Aggeregate the first position
		for (int x = 0; x < len2; x++)
		{
			int replace = 0;
			if (first[y] != second[x])
				replace = first[y] + second[x];			// Replacement cost: when the two char are not the same
			int indelFirst = first[y];					// Indel cost on first
			int indelSecond = second[x];				//Indel cost on second
			marksRow2[x + 1] = min3(marksRow2[x] + indelSecond, marksRow1[x + 1] + indelFirst, marksRow1[x] + replace);
		}
		//swap the two rows
		int* tmp = marksRow2;
		marksRow2 = marksRow1;
		marksRow1 = tmp;
	}
	int distance = marksRow1[len2];
	free(marksRow1);
	free(marksRow2);
	return distance;
}

int main()
{
	while (1)
	{
		string s1, s2;
		cout << "Input the strings:\n";
		cin >> s1 >> s2;
		cout << minimumDeleteSum(s1.c_str(), s2.c_str()) << endl;
	}
	return 0;
}

