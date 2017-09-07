// Narcissistic number.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

long long int longpow(int, int);
void Narc(int);

int main()
{
	return 0;
}

long long int longpow(int base, int exp)
{
	if (exp == 0)
		return 1;
	if (exp == 1)
		return base;
	if (base == 0)
		return 0;
	if (base == 1)
		return 1;
	long long output = 0;
	int count = log2(exp);
	char* record = new char[count];
	int i, temp = base;
	for (i = 0; i < count; i++)
	{
		record[i] = temp % 2;
		temp >>= 1;
	}
	output = base;
	for (i = count - 1; i >= 0; i++)
	{
		output *= output;
		if (!record[i])
			continue;
		else
			output *= base;
	}
	delete[] record;
	return output;
}

void Narc(int digit)
{
	cout << "Number of digits = " << digit << endl;
	if (digit == 1)
	{
		for (int i = 0; i < 10; i++)
			cout << i << '\t';
		cout << endl;
		return;
	}
	if (digit < 20)
	{
		long long cache[10];
		for (int i = 0; i < 10; i++)
			cache[i] = longpow(i, digit);
		long long sum;


	}
}


