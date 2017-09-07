// quick sort and insert sort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

void quicksort(int*, int);
void swap_int(int*, int*);
int *mid(int*, int*, int*);
void insertsort(int*, int);


vector<int> getint(string s) {
	if (s.size() == 0)
		return vector<int>();
	string buffer;
	vector<int> nums;
	int i = 0;
	while (i < s.size()) {
		while (i < s.size() && (isdigit(s[i]) || s[i] == '-')) {
			buffer.push_back(s[i]);
			i++;
		}
		if (buffer.size() != 0) {
			nums.push_back(stoi(buffer));
			buffer.clear();
		}
		i++;
	}
	return nums;
}

int main()
{
	while (1)
	{
		cout << "Input your sequence:" << endl;
		string raw;
		getline(cin, raw);
		vector<int> numbers = getint(raw);
		int size = numbers.size();
		int* arr = new int[size];
		for (int i = 0; i < size; i++)
			arr[i] = numbers[i];
		quicksort(arr, size);
		cout << "Quick sort:" << endl;
		for (int i = 0; i < size; i++)
			cout << arr[i] << " ";
		cout << endl;
		delete[] arr;
	}
}

int *mid(int *num1, int *num2, int *num3)
{
	if (*num1 > *num2)
		swap_int(num1, num2);
	if (*num1 > *num3)
		swap_int(num1, num3);
	if (*num2 > *num3)
		swap_int(num2, num3);
	return num2;
}

void swap_int(int *swap1, int *swap2)
{
	int temp;
	temp = *swap1;
	*swap1 = *swap2;
	*swap2 = temp;
}

void quicksort(int* iarray, int size)
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
	if (size < 10)
	{
		insertsort(iarray, size);
		return;
	}
	int* pivot = mid(iarray, iarray + (int)((size + 1) / 2), iarray + size - 1);
	swap_int(pivot, iarray + size - 1);
	int i = 0, j = size - 1;
	while (i < j)
	{
		while (iarray[++i] < iarray[size - 1])
			;
		while (iarray[--j] > iarray[size - 1])
			;
		if (i < j)
			swap_int(iarray + i, iarray + j);
	}
	swap_int(iarray + i, iarray + size - 1);
	quicksort(iarray, i);
	quicksort(iarray + i + 1, size - i - 1);
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

