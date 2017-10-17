// Permutations.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* getint(int* size)
{
	unsigned int capacity = 16;
	int* nums = (int*)malloc(sizeof(int)*capacity);
	int i = 0, buffer = 0;
	char c = ' ';
	int neg = 0, found = 0;
	while (c != EOF && c != '\n' && c != '\r')
	{
		c = getchar();
		if (c == '-')
			neg = 1;
		else if (isdigit(c))
		{
			buffer *= 10;
			buffer += c - '0';
			found = 1;
		}
		else if (found)
		{
			if (neg)
			{
				buffer = -buffer;
				neg = 0;
			}
			if (i == capacity)
			{
				capacity *= 2;
				int* temp = (int*)realloc((void*)nums, sizeof(int)*capacity);
				if (temp)
					nums = temp;
				else
				{
					printf("Error: Reallocation failed at size %d.\n", i);
					return nums;
				}
			}
			nums[i++] = buffer;
			found = 0;
			buffer = 0;
		}
	}
	*size = i;
	return nums;
}

size_t factorial(int n)
{
	if (n == 0)
		return 1;
	if (n < 0)
	{
		puts("Factorial does not exist for negative numbers.");
		return 0;
	}
	size_t fac = 1;
	int local_n = n;
	while (local_n != 1)
	{
		fac *= local_n;
		local_n--;
	}
	return fac;
}

int* deepcopy(int* arr, int size)
{
	int* out = (int*)malloc(sizeof(*out) * size);
	memcpy(out, arr, sizeof(*out) * size);
	return out;
}

void swap(int* a, int* b)
{
	int temp = *b;
	*b = *a;
	*a = temp;
}

int** permute(int* nums, int numsSize, int* returnSize)
{
	if (!numsSize)
		return NULL;
	if (numsSize == 1)
	{
		int** result = (int**)malloc(sizeof(*result));
		*result = (int*)malloc(sizeof(**result));
		**result = nums[0];
		*returnSize = 1;
		return result;
	}
	int* numbers = deepcopy(nums, numsSize);
	*returnSize = factorial(numsSize);
	int** returnArr = (int**)malloc(sizeof(*returnArr) * *returnSize);
	size_t count = 0;
	returnArr[count++] = deepcopy(numbers, numsSize);
	int* p = (int*)malloc(sizeof(*p) * numsSize);
	memset(p, 0, sizeof(*p) * numsSize);
	int i = 1;
	while (i < numsSize && count != *returnSize)
	{
		if (p[i] < i)
		{
			int j = (i & 1) * p[i];
			if (numbers[i] != numbers[j])
			{
				swap(numbers + i, numbers + j);
				returnArr[count++] = deepcopy(numbers, numsSize);
			}
			p[i]++;
			i = 1;
		}
		else
			p[i++] = 0;
	}
	free(numbers);
	return returnArr;
}

int main()
{
	puts("Input the numbers:");
	int size = 0;
	int* arr = getint(&size);
	size_t returnSize = 0;
	int** permutations = permute(arr, size, &returnSize);
	for (size_t i = 0; i < returnSize; i++)
	{
		for (int j = 0; j < size; j++)
			printf("%d", permutations[i][j]);
		printf("\n");
	}
	getchar();
	return 0;
}

