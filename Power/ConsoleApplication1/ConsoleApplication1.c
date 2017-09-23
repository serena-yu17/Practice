// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>

//Language: C
typedef unsigned long long ull;
ull  power(unsigned int base, unsigned int n) {
	if (!base && n)
		return 0;
	ull pow = 1;
	while (n) {
		if (n & 1)
			pow *= base;
		base *= base;
		n >>= 1;
	}
	return pow;
}

int main()
{
	while (1) {
		unsigned int base, n;
		scanf("%d %d", &base, &n);
		printf("%llu\n", power(base, n));
	}
	return 0;
}

