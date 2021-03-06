// generate random array.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


//Generates <SIZE> number of non-repeated random numbers at O(n). Repeat for <N_TESTS> times.

#define SIZE 20
#define N_TESTS 20

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <climits>

static inline void swap(unsigned* a, unsigned* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

static inline int digs(unsigned n)
{
	int base = 10;
	for (int i = 1; i < 6; i++, base *= 10)
	{
		if (n < base)
			return i;
	}
}

int main()
{
	srand(time(NULL));
	int len = digs(SIZE);
	unsigned arr[SIZE];
	for (int test = 0; test < N_TESTS; test++)
	{		
		for (int i = 0; i < SIZE; i++)
			arr[i] = i;
		int target = SIZE;
		while (target)
		{
			int p = rand() * target / RAND_MAX;
			swap(arr + p, arr + target - 1);
			target--;
		}
		for (int i = 0; i < SIZE; i++)
		{
			if (i)
				printf(", ");
			for (int j = 0; j < len - digs(arr[i]); j++)
				printf(" ");
			printf("%d", arr[i]);
		}
		printf("\n");
	}
	puts("Press any key to exit...");
	getchar();
	return 0;
}

