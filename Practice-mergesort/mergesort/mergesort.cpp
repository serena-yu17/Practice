// mergesort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<chrono>
using namespace std;

void merge(int *left, int leftlength, int *right, int rightlength, int *merged, int*temp);
void mergesort(int inputarray[], int length, int* temp);

int main()
{
	while (1)
	{
		cout << "Input numbers." << endl;
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
		chrono::time_point<chrono::system_clock> start, end;
		start = chrono::system_clock::now();
		int *temp = new int[size];
		if (size == 1)
		{
			cout << v[0] << endl;
			continue;
		}
		else
		{
			mergesort(number, size, temp);
		}
		end = chrono::system_clock::now();
		chrono::duration<double> elapsed = end - start;
				for (int i = 0; i < size; ++i) //print array
		{
			cout << number[i] << ' ';
		}
		cout << '\n'<<elapsed.count()<<'s'<<endl;
		delete[] temp;
	}
}

void merge(int *left, int leftlength, int *right, int rightlength, int *merged, int* temp)
{
	int i = 0, j = 0, k = 0;
	while (i < leftlength && j < rightlength)
	{
		while (left[i] <= right[j] && i<leftlength && j < rightlength)
		{
			temp[k] = left[i];
			k++; 
			i++;
		}
		while (left[i] >= right[j] && i<leftlength && j<rightlength)
		{
			temp[k] = right[j];
			k++;
			j++;
		}
	}
	while (i < leftlength) //merge remaining elements
	{
		temp[k] = left[i];
		i++; 
		k++;
	}
	while (j < rightlength)
	{
		temp[k] = right[j];
		j++;
		k++;
	}
	for (i = 0; i < leftlength + rightlength; ++i)
	{
		merged[i] = temp[i];
	}
}
void mergesort(int inputarray[], int length, int* temp)
{
	if (length == 1) return;
	if (length == 2)
	{
		if (inputarray[0] > inputarray[1])
		{
			int swap = inputarray[0];
			inputarray[0] = inputarray[1];
			inputarray[1] = swap;
			return;
		}
		else return;
	}
	int mid, rightlength;
	rightlength = length / 2;
	mid = length - rightlength;
	int * left = inputarray;
	int * right = &inputarray[mid];
	mergesort(inputarray, mid, temp);
	mergesort(right, rightlength,temp);
	merge(left, mid, right, rightlength, inputarray,temp);
}

