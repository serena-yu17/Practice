// Twosum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> twoSum(vector<int>& nums, int target) {
	int size = nums.size();
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (nums[i] + nums[j] == target) {
				vector<int> result = vector<int>(2);
				result[0] = i;
				result[1] = j;
				return result;
			}
		}
	}
	return vector<int>();
}

vector<int> twoSum_hash(vector<int>& nums, int target) {
	unordered_map<int, int> nums_map;
	for (int i = 0; i < nums.size(); i++) {
		if (nums_map.find(target - nums[i]) != nums_map.end()) {
			vector<int> result = vector<int>(2);
			result[0] = nums_map[target - nums[i]];
			result[1] = i;
			return result;
		}
		nums_map[nums[i]] = i;
	}
	return vector<int>();
}


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
		vector<int> solution = twoSum_hash(numbers, tg);
		for (auto v : solution)
			cout << v << ' ';
		cout << endl;
	}
}

