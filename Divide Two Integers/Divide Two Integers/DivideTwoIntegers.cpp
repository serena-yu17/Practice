// DivideTwoIntegers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <climits>

int divide(int dividend, int divisor) {
	if (divisor == 0)
		return INT_MAX;
	if (dividend == INT_MIN && divisor == -1)
		return INT_MAX;
	long long div1 = dividend, div2 = divisor;
	int pos = 1;
	if (div1 < 0) {
		pos = -pos;
		div1 = -div1;
	}
	if (div2 < 0) {
		pos = -pos;
		div2 = -div2;
	}
	if (div1 == 0 || div1 < div2)
		return 0;
	long long count = 1;
	unsigned long long div12 = div1, tar = div2 << 1;
	while (div12 >= tar) {
		div12 >>= 1;
		count <<= 1;
	}
	tar = div2;
	while (div12 > tar) {
		div12 -= div2;
		count++;
	}
	if (pos == -1)
		count = -count;
	if (count > INT_MAX || count < INT_MIN)
		count = INT_MAX;
	return count;
}


int main()
{
	while (1) {
		printf("Input the dividend and divisor: ");
		int dividend, divisor;
		scanf("%d%d", &dividend, &divisor);
		int div = divide(dividend, divisor);
		printf("%d\n", div);
	}
	return 0;
}

