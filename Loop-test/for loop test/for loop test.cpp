
// for loop test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<chrono>
#include <iostream>
#include <cstdlib>
#include <vector>
#include<algorithm>

using namespace std;
using namespace chrono;

duration<double> integrated_for(int times)
{
	chrono::time_point<chrono::system_clock> start, end;
	chrono::duration<double> elapsed;
	int i = 0;
	long addition = 0;
	start = chrono::system_clock::now();
	while (i < times)
	{
		addition++; addition++; addition++;
		i++;
	}
	end = chrono::system_clock::now();
	elapsed = end - start;
	return elapsed;
}

duration<double> separate_for(int times)
{
	chrono::time_point<chrono::system_clock> start, end;
	chrono::duration<double> elapsed;
	int i = 0;
	long addition = 0;
	start = chrono::system_clock::now();
	while (i < times)
	{
		addition++;
		i++;
	}
	i = 0;
	while (i < times)
	{
		addition++;
		i++;
	}
	i = 0;
	while (i < times)
	{
		addition++;
		i++;
	}
	end = chrono::system_clock::now();
	elapsed = end - start;
	return elapsed;
}

long one_plus(long input)
{
	return ++input;
}

duration<double> integrated_function(int times)
{
	chrono::time_point<chrono::system_clock> start, end;
	chrono::duration<double> elapsed;
	int i = 0;
	long addition = 0;
	start = chrono::system_clock::now();
	while (i < times)
	{
		addition = one_plus(addition); addition = one_plus(addition); addition = one_plus(addition);
		i++;
	}
	end = chrono::system_clock::now();
	elapsed = end - start;
	return elapsed;
}

duration<double> separate_function(int times)
{
	chrono::time_point<chrono::system_clock> start, end;
	chrono::duration<double> elapsed;
	int i = 0;
	long addition = 0;
	start = chrono::system_clock::now();
	while (i < times)
	{
		addition = one_plus(addition);
		i++;
	}
	i = 0;
	while (i < times)
	{
		addition = one_plus(addition);
		i++;
	}
	i = 0;
	while (i < times)
	{
		addition = one_plus(addition);
		i++;
	}
	end = chrono::system_clock::now();
	elapsed = end - start;
	return elapsed;
}

vector<int> randomlist(int size)
{
	int random_num = rand() % 1000;
	vector<int> output;
	for (int i = 0; i < size; i++)
		output.push_back(random_num);
	return output;
}

void operation_expensive(int size)
{
	vector<int>random_vector = randomlist(size);
	sort(random_vector.begin(), random_vector.end());
}

duration<double> integrated_expensive(int times)
{
	chrono::time_point<chrono::system_clock> start, end;
	chrono::duration<double> elapsed;
	int i = 0;
	long addition = 0;
	start = chrono::system_clock::now();
	while (i < times)
	{
		operation_expensive(1000); operation_expensive(1000); operation_expensive(1000);
		i++;
	}
	end = chrono::system_clock::now();
	elapsed = end - start;
	return elapsed;
}

duration<double> separate_expensive(int times)
{
	chrono::time_point<chrono::system_clock> start, end;
	chrono::duration<double> elapsed;
	int i = 0;
	long addition = 0;
	start = chrono::system_clock::now();
	while (i < times)
	{
		operation_expensive(1000);
		i++;
	}
	i = 0;
	while (i < times)
	{
		operation_expensive(1000);
		i++;
	}
	i = 0;
	while (i < times)
	{
		operation_expensive(1000);
		i++;
	}
	end = chrono::system_clock::now();
	elapsed = end - start;
	return elapsed;
}


int main()
{
	while (1)
	{
		duration<double> result[6];
		int i, loops;
		cout << "Input loops to run:" << endl;
		cin >> loops;
		for (i = 0; i < loops; i++)
		{
			result[0] += integrated_for(10000);
			result[1] += separate_for(10000);
			result[2] += integrated_function(10000);
			result[3] += separate_function(10000);
			/*result[4] += integrated_expensive(10000);
			result[5] += separate_expensive(10000);*/
		}
		cout << "integrated_for:\t\t\t" << result[0].count() << endl;
		cout << "separate_for:\t\t\t" << result[1].count() << endl;
		cout << "integrated_function:\t\t\t" << result[2].count() << endl;
		cout << "separate_function:\t\t\t" << result[3].count() << endl;
		//cout << "integrated_expensive:\t\t\t" << result[4].count() << endl;
		//cout << "separate_expensive:\t\t\t" << result[5].count() << endl;
	}
}

