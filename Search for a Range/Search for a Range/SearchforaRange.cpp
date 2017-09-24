// SearchforaRange.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
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

int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
	int left = 0;
	int right = numsSize - 1;
	int mid;
	int* out = (int*)malloc(sizeof(int) * 2);
	out[0] = -1;
	out[1] = -1;
	*returnSize = 2;
	while (left < right)
	{
		mid = (left + right) / 2;
		if (nums[mid] == target && (mid == 0 || nums[mid - 1] != target))
		{
			left = mid;
			right = mid;
			break;
		}
		else
		{
			if (nums[mid] > target || (mid != 0 && nums[mid] == target && nums[mid - 1] == target))
				right = mid - 1;
			else
				left = mid + 1;
		}
	}
	if (nums[left] == target)
		out[0] = left;
	right = numsSize - 1;
	while (left < right)
	{
		mid = (left + right) / 2;
		if (nums[mid] == target && (mid == numsSize - 1 || nums[mid + 1] != target))
		{
			left = mid;
			right = mid;
			break;
		}
		else
		{
			if (nums[mid] == target || (mid != numsSize - 1 && nums[mid] == target && nums[mid + 1] == target))
				left = mid + 1;
			else
				right = mid - 1;
		}
	}
	if (nums[right] == target)
		out[1] = right;
	return out;
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
	int returnsize = 0;
	int* position = searchRange(&input[0], input.size(), target, &returnsize);
	cout << position[0] << ", " << position[1] << endl;
	cin.ignore(100, '\n');
	cin.clear();
	getchar();
	return 0;
}

