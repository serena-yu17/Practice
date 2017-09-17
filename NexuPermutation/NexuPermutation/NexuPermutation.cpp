// NexuPermutation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void reverse(int* left, int* right) {
	while (left < right) {
		swap(left, right);
		left++;
		right--;
	}
}

void nextPermutation(int* nums, int numsSize) {
	if (numsSize < 2)
		return;
	int i = numsSize - 1;
	while (i > 0 && nums[i - 1] >= nums[i])
		i--;
	if (i == 0) {
		reverse(nums, nums + numsSize - 1);
		return;
	}
	int j = numsSize;
	while (nums[j - 1] <= nums[i - 1])
		j--;
	j--;
	swap(nums + j, nums + i-1);
	reverse(nums + i, nums + numsSize - 1);
}


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

int main()
{
	while (1) {
		std::cout << "Input your array:" << std::endl;
		std::string raw;
		std::getline(std::cin, raw);
		std::vector<int> numbers = getint(raw);
		nextPermutation(&numbers[0], numbers.size());
		for (auto a : numbers) {
			std::cout << a << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}
