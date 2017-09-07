// coins.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <functional>
#include <string>

using namespace std;

long count(long, int*, int);

int main()
{
	while (1)
	{
		vector<int> input;
		int buffer;
		long total;
		cout << "Input the total amount of money to change:" << endl;
		cin >> total;
		cin.ignore(10000, '\n');
		cout << "Input the denominations used:" << endl;
		string cache1, cache2;
		getline(cin, cache1);
		stringstream temp;
		temp << cache1;
		while (getline(temp, cache2, ' '))
		{
			if (stringstream(cache2) >> buffer && buffer != 0)
				input.push_back(buffer);
		}
		sort(input.begin(), input.end(), greater<int>());
		int* inp = &input[0];
		int size = input.size();
		long count_n = count(total, inp, size);
		cout << "Total combinations are:  " << count_n << endl;
	}
}

long count(long total, int* norminal, int types)
{
	long count_n = 0;
	if (total < 0)
		return 0;
	if (total == 0)
		return 1;
	if (types == 1)
	{
		if (total % *norminal == 0)
			return 1;
		else
			return 0;
	}
	int i = 0;
	while (i <= int(total / *norminal))
	{
		count_n += count(total-(i * (*norminal)), norminal + 1, types - 1);
		i++;
	}
	return count_n;
}
