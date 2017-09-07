// 4Sum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
using namespace std;

int compare_int(void const* a, void const* b) {
	return (*(int*)a - *(int*)b);
}

vector<vector<int>> fourSum(vector<int>& nums, int target) {
	int size = nums.size();
	vector<vector<int>> result = vector<vector<int>>();
	if (size < 4)
		return result;
	if (size == 4) {
		if (nums[0] + nums[1] + nums[2] + nums[3] == target)
			result.push_back(nums);
		return result;
	}
	qsort(&nums[0], size, sizeof(int), compare_int);
	for (int i = 0; i < size - 3; i++) {
		for (int j = i + 1; j < size - 2; j++) {
			int tar2 = target - nums[i] - nums[j];
			int start = j + 1, end = size - 1;
			while (start < end) {
				if (nums[start] + nums[end] == tar2) {
					vector<int> vec = vector<int>(4);
					vec[0] = nums[i];
					vec[1] = nums[j];
					vec[2] = nums[start];
					vec[3] = nums[end];
					result.push_back(vec);
					while (start < end && nums[start + 1] == nums[start])start++;
					while (start < end && nums[end - 1] == nums[end]) end--;
					start++;
					end--;
				}
				else if (start < end) {
					if (nums[start] + nums[end] < tar2)
						start++;
					else
						end--;
				}
			}
			while (j < size - 3 && nums[j + 1] == nums[j]) j++;
		}
		while (i < size - 4 && nums[i + 1] == nums[i]) i++;
	}
	return result;
}

vector<int> getint(string s) {
	if (s.size() == 0)
		return vector<int>();
	int buffer = 0;
	vector<int> nums;
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
		cout << "Input your array:" << endl;
		string raw;
		getline(cin, raw);
		vector<int> numbers = getint(raw);
		cout << "Input your target:" << endl;
		int tg;
		cin >> tg;
		cin.ignore(1000, '\n');
		cin.clear();
		vector<vector<int>> result = fourSum(numbers, tg);
		for (auto a : result) {
			for (auto elem : a)
				cout << elem << " ";
			cout << endl;
		}
	}
	return 0;
}

