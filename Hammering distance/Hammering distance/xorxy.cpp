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

int hammingDistance(int x, int y)
{
	int xorxy = x ^ y;
	int count = 0;
	while (xorxy)
	{
		if (xorxy & 1)
			count++;
		xorxy >>= 1;
	}
	return count;
}