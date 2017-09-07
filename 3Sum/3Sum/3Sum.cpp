// 3Sum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> threeSum(vector<int>& nums) {
	int size = nums.size();
	if (size < 3)
		return vector<vector<int>>();
	if (size == 3) {
		if (nums[0] + nums[1] + nums[2] == 0) {
			vector<vector<int>> vec;
			vec.push_back(nums);
			return vec;
		}
		else
			return vector<vector<int>>();
	}
	sort(nums.begin(), nums.end());
	for (auto v : nums)
		cout << v << ' ';
	cout << endl;
	vector<vector<int>>v_sum;
	for (int i = 0; i < size - 2; ++i) {
		int sum = -nums[i];
		int start = i + 1, end = size - 1;
		while (start < end) {
			if (nums[start] + nums[end] == sum) {
				vector<int> vec;
				vec.push_back(nums[i]);
				vec.push_back(nums[start]);
				vec.push_back(nums[end]);
				v_sum.push_back(vec);
				while (start < end && nums[start + 1] == nums[start])
					start++;
				while (start < end && nums[end - 1] == nums[end])
					end--;
				start++;
				end--;
			}
			if (start < end && nums[start] + nums[end] < sum)
				start++;
			if (start < end && nums[start] + nums[end] > sum)
				end--;
		}
		while (i < size - 2 && nums[i + 1] == nums[i])
			i++;
	}
	return v_sum;
}


int main()
{
	while (1) {
		cout << "Input your list of numbers:" << endl;
		string s;
		getline(cin, s);
		std::stringstream myss;
		myss << s;
		string t;
		int x;
		vector<int> numbers;
		while (getline(myss, t, ',')) {
			if (stringstream(t) >> x) {
				numbers.push_back(x);
			}
		}
		int size;
		vector<vector<int>> solution = threeSum(numbers);
		for (auto v : solution) {
			cout << v[0];
			for (int i = 1; i < 3; ++i) {
				cout << ',';
				cout << v[i];
			}
			cout << endl;
		}
	}
}

