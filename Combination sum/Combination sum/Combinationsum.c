// Combinationsum.cpp : Defines the entry point for the console application.
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

void search(int* candidates, int candidatesSize, int target, int** columnSizes, int* returnSize, int*** returnArray, int* addition, int numSize, int sum, int* capacity)
{
	sum += candidates[addition[numSize - 1]];
	if (sum == target)
	{
		if (*returnSize == *capacity)
		{
			*capacity <<= 1;
			int** temp = (int**)realloc((void*)(*returnArray), sizeof(*temp) * (*capacity));
			if (!temp)
			{
				if (!temp)
				{
					printf("returnArray reallocation error at size %d\n", *returnSize);
					return;
				}
			}
			*returnArray = temp;
			int* temp2 = (int*)realloc((void*)(*columnSizes), sizeof(*temp2) * (*capacity));
			if (!temp2)
			{
				printf("columnSizes reallocation error at size %d\n", *returnSize);
				return;
			}
			*columnSizes = temp2;
		}
		(*columnSizes)[*returnSize] = numSize;
		int* newArr = (int*)malloc(sizeof(int) * numSize);
		for (int i = 0; i < numSize; i++)
			newArr[i] = candidates[addition[i]];
		(*returnArray)[*returnSize] = newArr;
		(*returnSize)++;
	}
	else if (sum < target)
	{
		for (int i = addition[numSize - 1]; i < candidatesSize; i++)
		{
			int* newAddition = (int*)malloc(sizeof(int) * (numSize + 1));
			memcpy(newAddition, addition, sizeof(int) * numSize);
			newAddition[numSize] = i;
			search(candidates, candidatesSize, target, columnSizes, returnSize, returnArray, newAddition, numSize + 1, sum, capacity);
		}
	}
	free(addition);
}

int** combinationSum(int* candidates, int candidatesSize, int target, int** columnSizes, int* returnSize)
{
	*returnSize = 0;		
	int capacity = candidatesSize;
	int*** returnArray = (int***)malloc(sizeof(*returnArray));
	*returnArray = (int**)malloc(sizeof(*returnArray) * capacity);
	(*columnSizes) = (int*)malloc(sizeof(**columnSizes) * capacity);
	if (candidatesSize < 1 && (candidatesSize == 1 && candidates[0] != target))
		return	*returnArray;
	for (int i = 0; i < candidatesSize; i++)
	{
		int* addition = (int*)malloc(sizeof(*addition));
		addition[0] = i;
		search(candidates, candidatesSize, target, columnSizes, returnSize, returnArray, addition, 1, 0, &capacity);
	}
	return *returnArray;
}

int main()
{
	int size = 0;
	int* arr = getint(&size);
	/*for (int i = 0; i < size; i++)
		printf("%d ", arr[i]); */
	printf("Input target: ");
	int target;
	scanf("%d", &target);
	int** columnSizes = (int**)malloc(sizeof(int*));
	int returnSize = 0;
	int** returnArray = combinationSum(arr, size, target, columnSizes, &returnSize);
	for (int i = 0; i < returnSize; i++)
	{
		for (int j = 0; j < (*columnSizes)[i]; j++)
		{
			if (j)
				printf(" ");
			printf("%d", returnArray[i][j]);
		}
		free(returnArray[i]);
		printf("\n");
	}
	free(returnArray);
	free(*columnSizes);
	free(columnSizes);
	free(arr);
	getch();
}

