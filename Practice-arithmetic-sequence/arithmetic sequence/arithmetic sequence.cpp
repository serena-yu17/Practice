// arithmetic sequence.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<string>
#include<iostream>
#include<vector>
#include<sstream>
#include<math.h>
using namespace std;

int analyse(vector<int>);

int main()
{
	while (1)
	{
		cout << "Input array:" << endl;
		string s;
		getline(cin, s);
		std::stringstream myss;
		myss << s;
		string t;
		int x;
		vector<int> v;
		while (getline(myss, t, ' '))
		{
			if (stringstream(t) >> x)
			{
				v.push_back(x);
			}
		}
		int *number = &v[0];
		int size = v.size();
		if (!size)
			continue;
		int flag = 0;
		flag = analyse(v);
		string insert = "NOT ";
		if (flag)
			insert = "\0";
		cout << "This array is " << insert << "an arithmetic sequence.\n" << endl;
	}
	//////////////
	return 0;
}

int max_num(vector<int> number)
{
	int size = number.size();
	if (size == 1)
		return number[0];
	int max_num = number[0];
	for (int i = 1; i < size; i++)
	{
		if (number[i] > max_num)
			max_num = number[i];
	}
	return max_num;
}

int min_num(vector<int> number)
{
	int size = number.size();
	if (size == 1)
		return number[0];
	int min_num = number[0];
	for (int i = 1; i < size; i++)
	{
		if (number[i] < min_num)
			min_num = number[i];
	}
	return min_num;
}

int analyse(vector<int> input)
{
	int size = input.size();
	if ( size == 1)
		return 1;
	int max_n = max_num(input), min_n = min_num(input);
	int diff = max_n - min_n;
	if (diff == 0)
			return 1;
	if (diff % (size - 1) != 0)
		return 0;
	int comd = diff / (size-1);
	vector<char> test(size);
	for (int i = 0; i < size; i++)
	{
		int j = (input[i] - min_n) / comd;
		test[j] = 1;
	}
	int sum = 0;
	for (int i : test)
		sum += i;
	if (sum != size)
		return 0;
	return 1;
}
