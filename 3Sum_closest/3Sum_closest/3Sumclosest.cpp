// 3Sumclosest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <stdio.h>
using namespace std;

///////////////////

void quicksort(int*, int);
void swap_int(int*, int*);
int *mid(int*, int*, int*);
void insertsort(int*, int);
int ab(int);

int threeSumClosest(int* nums, int numsSize, int target) {
	if (numsSize <= 3) {
		int sum = 0;
		for (int i = 0; i < numsSize; i++)
			sum += nums[i];
		return sum;
	}
	quicksort(nums, numsSize);
	int closest = nums[0] + nums[1] + nums[2];
	int close = closest;
	for (int i = 0; i < numsSize - 2; i++) {
		int first = nums[i] + nums[i + 1] + nums[i + 2];
		if (first == target)
			return target;
		if (first > close && close >= target)	// i is getting too large
			break;
		close = first;
		if (nums[i] + nums[numsSize - 2] + nums[numsSize - 1] < target) {
			close = nums[i] + nums[numsSize - 2] + nums[numsSize - 1];	//if the largest possible combination containing nums[i] is smallest
		}
		else {
			int tar = target - nums[i];
			int bg = i + 1, end = numsSize - 1;
			int sum = nums[bg] + nums[end];
			if (sum == tar)
				return target;
			int bgs[2], ends[2];	//keep records
			bgs[0] = sum;
			bgs[1] = tar;
			ends[0] = sum;
			ends[1] = tar;
			while (bg < end) {
				if (nums[bg] + nums[end] == tar)
					return target;
				if (ab(tar - nums[bg] - nums[end]) < ab(tar - close + nums[i]))
					close = nums[bg] + nums[end] + nums[i];
				if (ends[0] < tar && ends[1] < tar)	// Consistently going too small
					break;
				if (bgs[0] > tar && bgs[1] > tar)	//Consistently going too big
					break;
				if (nums[bg] + nums[end] > tar) {
					ends[0] = ends[1];
					ends[1] = nums[bg] + nums[end];
					end--;
				}
				else {
					bgs[0] = bgs[1];
					bgs[1] = nums[bg] + nums[end];
					bg++;
				}
			}
		}
		if (ab(target - close) < ab(target - closest))
			closest = close;
	}
	return closest;
}


int ab(int a) {
	return a < 0 ? -a : a;
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


///////////////////////////////////////////////////////////

vector<int> getint(string s) {
	if (s.size() == 0)
		return vector<int>();
	string buffer;
	vector<int> nums;
	int i = 0;
	while (i < s.size()) {
		int isPos = 1;
		while (i < s.size() && (isdigit(s[i]) || s[i] == '-')) {
			if (s[i] == '-') {
				isPos = -1;
				i++;
			}
			else {
				buffer.push_back(s[i]);
				i++;
			}
		}
		if (buffer.size() != 0) {
			nums.push_back(stoi(buffer) * isPos);
			buffer.clear();
		}
		i++;
	}
	return nums;
}

int main()
{
	while (1) {
		cout << "Input your list of numbers:" << endl;
		string s;
		getline(cin, s);
		vector<int> numbers = getint(s);
		cout << "Input your target:" << endl;
		int tg;
		cin >> tg;
		cin.ignore(1000, '\n');
		cin.clear();
		int sum = threeSumClosest(&numbers[0], numbers.size(), tg);
		cout << sum << endl;
	}
}
