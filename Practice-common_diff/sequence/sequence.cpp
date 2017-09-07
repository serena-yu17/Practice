// sequence.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<string>
#include<iostream>
#include<vector>
#include<sstream>
#include<math.h>
using namespace std;

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

char analyse(vector<int> input)
{
	int size = input.size();
	if (size == 1)
		return 1;
	int max_n = max_num(input), min_n = min_num(input);
	int diff = max_n - min_n;
	if (diff == 0)
		return 1;
	if (diff % (size - 1) != 0)
		return 0;
	int comd = diff / (size - 1);
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

char comdiff(vector<int> input)
{
	int size = input.size();
	if (size == 1)
		return 1;
	int max_n = max_num(input), min_n = min_num(input);
	int diff = max_n - min_n;
	if (diff == 0)
		return 1;
	if (diff % (size - 1) != 0)
		return 0;
	return 1;
}

int main()
{
	int flag=0, count=0;
	vector<int> v(10);
	while (1)
	{
		count++;
		for (int i=0; i<10;i++)
			v[i] = 1 + rand() % 1000;
		if (analyse(v) == 0 && comdiff(v) == 1)
			flag = 1;
		if (flag == 1)
		{
			for (int member : v)
				cout << member << ',';
			cout << "\tIn " << count << " trials." << endl;
		}
	}
	///////
	return 0;
}

