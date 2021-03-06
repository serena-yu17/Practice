// Subarray Product Less Than K.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <sstream>
#include <ctype.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void getint(string& const s, vector<int>* nums)
{
	if (s.size() == 0)
		return;
	size_t i = 0;
	while (i < s.size())
	{
		long long buffer = 0;
		int found = 0;
		int neg = 0;
		if (s[i] == '-')
			neg = 1;
		while (i < s.size() && isdigit(s[i]))
		{
			buffer *= 10;
			buffer += s[i] - '0';
			i++;
			found = 1;
		}
		if (found)
		{
			if (neg)
				buffer = -buffer;
			(*nums).push_back(buffer);
		}
		i++;
	}
}

void extend(size_t* prod, long* end, int* nums, size_t numsSize, int k)
{

	while (*end < numsSize)
	{
		size_t newprod = (*prod) * nums[*end];
		if (newprod < k && *end < numsSize)
		{
			(*end)++;
			*prod = newprod;
		}
		else
			break;
	}
}

size_t numSubarrayProductLessThanK(int* nums, size_t numsSize, int k)
{
	size_t count = 0;
	size_t prod = 1;
	long end = 0;
	long begin = 0;
	while (begin < numsSize)
	{
		extend(&prod, &end, nums, numsSize, k);
		count += end - begin;
		begin++;
		if (begin <= end)
			prod /= nums[begin - 1];
		else
			end = begin;
	}
	return count;
}

int main()
{
	while (1)
	{
		vector<int> nums;
		int k = 5;
		/*cout << "Input your numbers:\n";
		string raw;
		getline(cin, raw);
		getint(raw, &nums);
		cout << "Input target:\n";
		cin >> k;*/
		for (size_t i = 0; i < 47220; i++)
		{
			if (i == 867)
				nums.push_back(8);
			else
				nums.push_back(1);
		}

		int numsubarray = numSubarrayProductLessThanK(&nums[0], nums.size(), k);
		cout << numsubarray << endl;
		cin.ignore(100, '\n');
		cin.clear();
	}
	return 0;
}

