// iterate list.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

void quicksort(int*, int);
//void enumerate(int*, int);
void swap_int(int*, int*);
int *mid(int*, int*, int*);
void insertsort(int*, int);

struct iterate
{
	int* iarray;
	iterate* next;
};

int main()
{
	while (1)
	{
		cout << "Input your sequence:" << endl;
		string raw, process;
		getline(cin, raw);
		int temp;
		stringstream parse_str(raw);
		vector<int> numbers;
		while (getline(parse_str, process, ' '))
		{
			if (stringstream(process) >> temp)
				numbers.push_back(temp);
		}
		int size = numbers.size();
		quicksort(&numbers[0], size);
		cout << "Quick sort:" << endl;
		for (int a : numbers)
			cout << a << ", ";
		cout << endl;
	}
}

int *mid(int *num1, int *num2, int *num3)
{
	if (*num1 >= *num2)
	{
		if (*num1 <= *num3)
			return num1;
		else
			return *num2 >= *num3 ? num2 : num3;
	}
	else
	{
		if (*num1 >= *num3)
			return num1;
		else
			return *num2 <= *num3 ? num2 : num3;
	}
}

void swap_int(int *swap1, int *swap2)
{
	int temp;
	temp = *swap1;
	*swap1 = *swap2;
	*swap2 = temp;
}

void quicksort(int * iarray, int size)
{
	if (!(size > 1))
		return;
	if (size == 2)
	{
		if (iarray[0] <= iarray[1])
			return;
		else
		{
			swap_int(iarray, iarray + 1);
			return;
		}
	}
	if (size < 8)
	{
		insertsort(iarray, size);
		return;
	}
	int* pivot = mid(iarray, iarray + size - 1, iarray + (int)((size + 1) / 2));
	swap_int(pivot, iarray + size - 1);
	int i = 0, j = size - 1;
	while (i < j)
	{
		while (iarray[++i] < iarray[size-1])
			;
		while (iarray[--j] > iarray[size - 1])
			;
		if (i < j)
		{
			swap_int(iarray + i, iarray + j);
		}
	}
	swap_int(iarray + i, iarray + size - 1);
	quicksort(iarray, i);
	quicksort(iarray + i, size - i);
}

void insertsort(int* iarray, int size)
{
	if (!(size > 1))
		return;
	int *front = iarray + 1;
	int *iter;
	while (front < iarray + size)
	{
		if (*front < *(front - 1))
		{
			iter = front - 2;
			while (iter >= iarray && *iter > *front)
				iter--;
			iter++;
			int *move = front;
			int temp = *front;
			while (move > iter)
			{
				*move = *(move - 1);
				move--;
			}
			*iter = temp;
		}
		front++;
	}
}