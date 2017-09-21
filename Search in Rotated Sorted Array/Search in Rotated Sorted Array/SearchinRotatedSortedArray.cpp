// SearchinRotatedSortedArray.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

std::vector<int> getint(std::string s) {
	if (s.size() == 0)
		return std::vector<int>();
	int buffer = 0;
	std::vector<int> nums;
	int i = 0;
	while (i < s.size()) {
		int isPos = 1;
		int filled = 0;
		while (i < s.size() && (isdigit(s[i]) || s[i] == '-')) {
			if (s[i] == '-' && buffer == 0) {
				isPos = -1;
				i++;
			}
			else {
				buffer *= 10;
				buffer += s[i] - '0';
				i++;
				filled = 1;
			}
		}
		if (filled == 1)
			nums.push_back(buffer * isPos);
		i++;
		buffer = 0;
		filled = 0;
	}
	return nums;
}

int* binarysearch(int* left, int* right, int target)
{
	while (left < right)
	{
		int* mid = left + (right - left) / 2;
		if (*mid == target)
			return mid;
		else
		{
			if (*mid > target)
				right = mid - 1;
			else
				left = mid + 1;
		}
	}
	if (*left == target)
		return left;
	else
		return NULL;
}

int search(int* nums, int numsSize, int target)
{
	if (target == nums[0])
		return 0;
	if (target == nums[numsSize - 1])
		return numsSize - 1;
	int left = 0, right = numsSize - 1;
	while (left < right)
	{
		int mid = (left + right) / 2;
		if (nums[mid] > nums[right])		//rotated posision at right half
			left = mid + 1;
		else
			right = mid;
	}
	int small = left;
	int large;
	int* pos;
	if (nums[small] == target)
		return small;
	if (small == 0)
		pos = binarysearch(nums, nums + numsSize - 1, target);
	else {
		large = small - 1;
		if (target > nums[0])
			pos = binarysearch(nums, nums + large, target);
		else
			pos = binarysearch(nums + small, nums + numsSize - 1, target);
	}
	if (!pos)
		return -1;
	else return pos - nums;
}



int main()
{
	ios::sync_with_stdio(false);
	cout << "Input array:" << endl;
	string raw;
	getline(cin, raw);
	cout << "Input target:" << endl;
	int target;
	cin >> target;
	vector<int> input = getint(raw);
	int position = search(&input[0], input.size(), target);
	cout << position << endl;
	cin.ignore(100, '\n');
	cin.clear();
	getchar();
	return 0;
}

