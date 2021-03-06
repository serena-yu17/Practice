// Partition to K Equal Sum Subsets.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>

#include <sstream>
#include <ctype.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

/*bool dfs(int* nums, int numsSize, int k, int div)
{
int* partSum = (int*)malloc(k * sizeof(*partSum));
memset(partSum, 0, k * sizeof(*partSum));
int* allocation = (int*)malloc(numsSize * sizeof(*allocation));
memset(allocation, 0, numsSize * sizeof(*allocation));
int incomplete = (1 << k) - 1;
int p = 0;
while (p != -1)
{
if (p < numsSize && allocation[p] < k)
{
int add = partSum[allocation[p]] + nums[p];
allocation[p]++;
if (add <= div)
{
partSum[allocation[p] - 1] = add;
if (add == div)
incomplete &= ~(1 << (allocation[p] - 1));
p++;
}
}
else
{
if (!incomplete)
{
free(partSum);
free(allocation);
return 1;
}
partSum[allocation[p - 1] - 1] -= nums[p - 1];
allocation[p] = 0;
p--;
}
}
free(partSum);
free(allocation);
return 0;
} */

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

void printBin(int x, int size)
{
	char* stack = (char*)malloc(size);
	memset(stack, '0', size);
	int p = 0;
	while (x)
	{
		stack[p++] = (x & 1) + '0';
		x >>= 1;
	}
	for (int i = size - 1; i > -1; i--)
		printf("%c", stack[i]);
	printf("\n");
}

int sumArr(int* nums, int numsSize)
{
	int sumArray = 0;
	for (int i = 0; i < numsSize; i++)
		sumArray += nums[i];
	return sumArray;
}

int arrToInt(int size, int* arr, int len)
{
	int result = (1 << size) - 1;
	for (int i = 1; i < len; i++)
		result &= ~(1 << arr[i]);
	return result;
}

int* findSum(int* nums, int size, int div, int* count)
{
	int capacity = size;
	int* combinations = (int*)malloc(capacity * sizeof(*combinations));
	*count = 0;
	int* stack = (int*)malloc((size + 1) * sizeof(*stack));
	int* choices = (int*)malloc((size + 1) * sizeof(*choices));
	for (int i = 0; i < size + 1; i++)
		choices[i] = i;
	int p = 0;
	stack[p++] = -1;
	int sum = 0;
	while (p)
	{
		if (sum < div && choices[stack[p - 1] + 1] < size)
		{
			stack[p] = choices[stack[p - 1] + 1];
			sum += nums[stack[p]];
			choices[stack[p - 1] + 1]++;
			p++;
		}
		else
		{
			if (sum == div)
			{
				if (*count == capacity)
				{
					capacity <<= 1;
					int* tmp = (int*)realloc((void*)combinations, capacity * sizeof(*combinations));
					if (!tmp)
					{
						printf("Realloc error in findSum at capacity = %d\n", capacity);
						return NULL;
					}
					combinations = tmp;
				}
				combinations[(*count)++] = arrToInt(size, stack, p);
			}
			if (p == 0)
				break;
			sum -= nums[stack[p - 1]];
			choices[stack[p - 1] + 1] = stack[p - 1] + 1;
			p--;
		}
	}
	free(stack);
	free(choices);
	return combinations;
}

bool findChain(int* combinations, int count, int size, int k)
{
	int full = (1 << size) - 1;
	int* stack = (int*)malloc((k + 1) * sizeof(*stack));
	int* choices = (int*)malloc((count + 1) * sizeof(*choices));
	int* accumulate = (int*)malloc((k + 1) * sizeof(*accumulate));
	accumulate[0] = -1;
	for (int i = 0; i < count + 1; i++)
		choices[i] = i;
	int p = 0;
	stack[p++] = -1;
	while (p)
	{
		if (p < k + 1 && choices[stack[p - 1] + 1] < count)
		{
			if (accumulate[p - 1] | combinations[choices[stack[p - 1] + 1]] == full)
			{
				stack[p] = choices[stack[p - 1] + 1];
				accumulate[p] = accumulate[p - 1] & combinations[stack[p]];
				choices[stack[p - 1] + 1]++;
				p++;
			}
			else
				choices[stack[p - 1] + 1]++;
		}
		else
		{
			if (p == k + 1 && accumulate[p - 1] == 0)
				return 1;
			choices[stack[p - 1] + 1] = stack[p - 1] + 1;
			p--;
		}
	}
	free(stack);
	free(choices);
	free(accumulate);
	return 0;
}

bool canPartitionKSubsets(int* nums, int numsSize, int k)
{
	if (k == 1 && k == numsSize)
		return 1;
	int sum = sumArr(nums, numsSize);
	if (sum % k)
		return 0;
	int div = sum / k;
	int* smallNum = (int*)malloc(numsSize * sizeof(*smallNum));
	int p = 0;
	int size = numsSize;
	for (int i = 0; i < numsSize; i++)
	{
		if (nums[i] > div)
			return 0;
		if (nums[i] == div)
		{
			k--;
			size--;
		}
		else
			smallNum[p++] = nums[i];
	}
	int count = 0;
	int* combinations = findSum(smallNum, size, div, &count);
	if (count < k)
		return 0;
	/*for (int i = 0; i < size; i++)
		printf("%d ", smallNum[i]);
	printf("\n");
	for (int i = 0; i < count; i++)
		printBin(combinations[i], size);*/
	bool found = findChain(combinations, count, size, k);
	free(combinations);
	return found;
}

int main()
{
	while (1)
	{
		vector<int> nums;
		int k;
		cout << "Input your numbers:\n";
		string raw;
		getline(cin, raw);
		getint(raw, &nums);
		cout << "Input target:\n";
		cin >> k;
		bool can = canPartitionKSubsets(&nums[0], nums.size(), k);
		if (can)
			cout << "True\n";
		else
			cout << "False\n";
		cin.ignore(100, '\n');
		cin.clear();
	}
}

