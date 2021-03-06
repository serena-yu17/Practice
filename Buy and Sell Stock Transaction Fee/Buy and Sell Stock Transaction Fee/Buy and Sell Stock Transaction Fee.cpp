// Buy and Sell Stock Transaction Fee.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <climits>

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

int max(int a, int b)
{
	return a > b ? a : b;
}

int maxProfit(int* prices, int pricesSize, int fee)
{
	int doneTrade = 0, halfTrading = INT_MIN;
	for (int i = 0; i < pricesSize; i++)
	{
		halfTrading = max(halfTrading, doneTrade - prices[i]);		//	(doneTrade - prices[i]) : spend prices[i] to buy stock
		doneTrade = max(doneTrade, halfTrading + prices[i] - fee);	  //  (halfTrading + prices[i]): get money when selling stock
	}
	return doneTrade;
}

int main()
{
	while (1)
	{
		puts("Input your prices:");
		int size = 0;
		int* prices = getint(&size);
		puts("Input transaction fee:");
		char buffer[10];
		fgets(buffer, 10, stdin);
		int fee = atoi(buffer);
		int profit = maxProfit(prices, size, fee);
		printf("%d\n", profit);
	}
	return 0;
}

