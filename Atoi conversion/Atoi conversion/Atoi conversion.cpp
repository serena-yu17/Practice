// Atoi conversion.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <cstdio>
#include <climits>
#include <ctype.h>
#include <string>
#include <iostream>
#include <cstring>
using namespace std;

long myAtoi(char*);

int main()
{
	while (1) {
		printf("Input your string:\n");
		char buffer[100];
		cin.getline(buffer, 100);
		long it = myAtoi(buffer);
		printf("%d\n", it);
	}
	return 0;
}

long myAtoi(char* str)
{
	int isMinus = 0;
	if (strlen(str) == 0)
		return 0;
	char* start = str;
	while (*str != 0 && (*str == ' ' || *str == '0' || *str == '+' || *str == '-')) {
		if (*str == '-') {
			if (isMinus == 1 || isMinus == -1)
				return 0;
			isMinus = -1;
			start = str;
		}
		if (*str == '+') {
			if (isMinus == 1 || isMinus == -1)
				return 0;
			isMinus = 1;
			start = str;
		}
		str++;
	}
	if (isMinus != 0)
		start++;
	else {
		while (*start != 0 && (*start == ' ' || *start == '0'))
			start++;
	}
	char* end = start;
	while (*end != 0 && isdigit(*end)) {
		end++;
	}
	int len = end - start;
	if (len == 0)
		return 0;
	if (pow(10, len - 1) > INT_MAX) {
		if (isMinus >= 0)
			return INT_MAX;
		else
			return INT_MIN;
	}
	int pow10[50];
	pow10[len - 1] = 1;
	for (int j = len - 2; j >= 0; --j) {
		pow10[j] = pow10[j + 1] * 10;
	}
	unsigned long res = 0;
	int i = 0;
	while (start + i < end)
	{
		res += (start[i] - '0') * pow10[i];
		i++;
	}
	if (res > INT_MAX) {
		if (isMinus >= 0)
			return INT_MAX;
		else
			return INT_MIN;
	}
	if (isMinus < 0)
		res = -res;
	return res;
}
