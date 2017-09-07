// Narc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

long* narcis(int, int &);
void insertsort(long *, int);

int main()
{
	while (1)
	{
		cout << "Enter the digits of Narcissistic numbers:" << endl;
		int n;
		cin >> n;
		if (n < 20)
		{
			int length = 0;
			long* output = narcis(n, length);
			for (int i = 0; i < length; i++)
				cout << output[i];
			cout << endl;
			delete[] output;
		}
	}
}

long* narcis(int n, int & count)
{
	long* narc_num;
	if (n >= 20)
	{
		narc_num = new long[1];
		narc_num[0] = 0;
		return narc_num;
	}
	narc_num = new long[200];
	count = 0;
	if (n == 1)
	{
		for (int i = 1; i <= 10; i++)
		{
			narc_num[count] = i;
			count++;
		}
		return narc_num;
	}
	long power[10];
	for (int i = 0; i < 10; i++)
		power[i] = pow(i, n);
	int *num = new int[n];
	for (int i = 0; i < n; i++)
		num[i] = 0;
	num[0] = 1;
	long sum = 0;
	int index = n;
	while (index > 0 || num[index] < 10)
	{
		if (index == n && int(log10(sum)) + 1 == n)
		{
			int flag = 1;
			long temp = sum;
			for (int i = n - 1; i >= 0; i--)
				if (temp % 10 != num[i])
					flag = 0;
			if (flag == 1)
			{
				narc_num[count] = sum;
				count++;
			}
		}
		if (index == 0 || index < n && num[index] <= num[index - 1])
		{
			sum += power[num[index]];
			index++;
			if (index < n)
				num[index] = 0;
		}
		else
		{
			index -= 1;
			sum -= power[num[index]];
			num[index]++;
		}
	}
	delete[] num;
	insertsort(narc_num, count);
	return narc_num;
}

void insertsort(long *input, int length)
{
	long *pfront;
	pfront = input + 1;
	int i = 0;
	while (pfront < input + length - 1)
	{
		if (*pfront < *(pfront - 1))
		{
			long *piterate = pfront - 1;
			while (piterate > input && *pfront < *piterate)
				piterate--;
			long *poperate = pfront;
			long temp = *pfront;
			while (poperate > piterate)
			{
				*poperate = *(poperate - 1);
				poperate--;
			}
			*piterate = temp;
		}
	}
	pfront++;
}
