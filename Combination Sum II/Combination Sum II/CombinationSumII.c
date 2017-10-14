// CombinationSumII.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 

int* getint(int* size)
{
	puts("Input the numbers:");
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

void expandArray(int*** arr, int** arr2, int* capacity)
{
	(*capacity) *= 2;
	int** temp = (int**)realloc((void*)(*arr), sizeof(*temp) * (*capacity));
	if (!temp)
	{
		printf("Memory reallocation failed.");
		return;
	}
	*arr = temp;
	int* temp2 = (int*)realloc((void*)(*arr2), sizeof(*temp2) * (*capacity));
	if (!temp2)
	{
		printf("Memory reallocation failed.");
		return;
	}
	*arr2 = temp2;
}

int compInt(void* a, void* b)
{
	return *((int*)a) >= *((int*)b);
}

int** combinationSum2(int* candidates, int candidatesSize, int target, int** columnSizes, int* returnSize)
{
	qsort(candidates, candidatesSize, sizeof(int), compInt);
	*returnSize = 0;
	int capacity = candidatesSize;
	int*** returnArr = (int***)malloc(sizeof(*returnArr));
	*returnArr = (int**)malloc(sizeof(**returnArr) * capacity);
	*columnSizes = (int*)malloc(sizeof(**columnSizes) * capacity);
	if (candidatesSize == 1 && candidates[0] == target)
	{
		**returnArr = (int*)malloc(sizeof(int));
		***returnArr = target;
		**columnSizes = 1;
		*returnSize = 1;
	}
	else
	{
		if (candidatesSize > 0 && !(candidatesSize == 1 && candidates[0] != target))
		{
			int* stack = (int*)malloc(sizeof(*stack) * (candidatesSize + 1));
			int* used = (int*)malloc(sizeof(*used) * (candidatesSize + 1));
			for (int i = 0; i < candidatesSize + 1; i++)
				used[i] = i;
			int size = 0;
			stack[size++] = -1;
			int sum = 0;
			while (size)
			{
				while (used[size - 1] && candidates[used[size - 1]] == candidates[used[size - 1] - 1] && used[size - 1] > stack[size - 1] + 1)
					used[size - 1]++;
				if (sum < target && used[size - 1] < candidatesSize)
				{
					stack[size] = used[size - 1];
					sum += candidates[stack[size]];
					used[size - 1]++;
					used[size] = stack[size] + 1;
					size++;
				}
				else
				{
					if (sum == target)
					{
						if (*returnSize == capacity)
							expandArray(returnArr, columnSizes, &capacity);
						int* combination = (int*)malloc(sizeof(*combination) * (size - 1));
						for (int i = 1; i < size; i++)
							combination[i - 1] = candidates[stack[i]];
						(*returnArr)[*returnSize] = combination;
						(*columnSizes)[*returnSize] = size - 1;
						(*returnSize)++;
					}
					sum -= candidates[stack[size - 1]];
					size--;
				}
			}
		}
	}
	int** out = *returnArr;
	free(returnArr);
	return out;
}

int main()
{
	int size = 0;
	int* arr = getint(&size);
	printf("Input target: ");
	int target;
	char buffer[10];
	fgets(buffer, 10, stdin);
	target = atoi(buffer);
	int** columnSizes = (int**)malloc(sizeof(int*));
	int returnSize = 0;
	int** returnArr = combinationSum2(arr, size, target, columnSizes, &returnSize);
	for (int i = 0; i < returnSize; i++)
	{
		for (int j = 0; j < (*columnSizes)[i]; j++)
		{
			if (j)
				printf(" ");
			printf("%d", returnArr[i][j]);
		}
		free(returnArr[i]);
		printf("\n");
	}
	free(returnArr);
	free(*columnSizes);
	free(columnSizes);
	free(arr);
	getchar();
	return 0;
}

