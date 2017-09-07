// Hammering distance.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int hammingDistance(int, int);

int main()
{
	while (1)
	{
		cout << "Input 2 numbers, separated by space:" << endl;
		int num1 = 0, num2 = 0;
		cin >> num1;
		cin >> num2;
		//cout << num1 <<'\t' << num2 << endl;
		int hdist = hammingDistance(num1, num2);
		cout << "Their hammer distance is:\n" << hdist << endl;
	}
}

int hammingDistance(int num1, int num2) 
{
	int count = 0;
	while (num1 != 0 || num2 != 0)
	{
		if ((num1 & 1) != (num2 & 1))
			count++;
		num1 >>= 1;
		num2 >>= 1;
	}
	return count;
}