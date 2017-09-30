// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>

//Language: C
size_t  power(unsigned int b, unsigned int n) {
	if (!b && n)
		return 0;
	size_t base = b;
	size_t pow = 1;
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
		printf("%zu\n", power(base, n));
	}
	return 0;
}

