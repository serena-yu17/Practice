// prime numbers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main()
{
	while (1)
	{
		cout << "Input your limit:" << endl;
		size_t ub;
		cin >> ub;
		cin.ignore(1000, '\n');
		cin.clear();
		char* num = new char[ub];
		memset(num, 1, ub);
		num[1] = 0;
		num[0] = 0;
		size_t i = 2;
		size_t limit = 1 + sqrt(ub);
		while (i < limit)
		{
			if (num[i] == 0)
			{
				i++;
				continue;
			}
			size_t j = i;
			while (j < ub)
			{
				size_t mul = 0;
				size_t k = i;
				while (j < limit && mul < ub)
				{
					mul = j*k;
					num[mul] = 0;
					do
						k++;
					while (num[k] == 0 && k < limit);
				}
				j += i;
				num[j] = 0;
			}
			i++;
		}
		vector<int> prime;
		for (size_t i = 2; i < ub; i++)
		{
			if (num[i] == 1)
				prime.push_back(i);
		}
		for (int a : prime)
			cout << a << '\t';
		cout << endl;
		delete[] num;
	}
	return 0;
}

