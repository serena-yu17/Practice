// Integer to Roman.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

char *roman(int num) {
	int digits[10];
	memset(digits, 0, 10 * sizeof(int));
	int i = 0;
	int digcount = 0;
	while (num > 0) {
		digits[9 - i] = num % 10;
		num /= 10;
		digcount++;
		i++;
	}
	int *dig = digits;
	while (*dig == 0)
		dig++;
	int d = digcount - 1;
	char roman[10][5];
	for (i = 0; i < 10; i++)
		roman[i][0] = 0;
	char symbol[] = { 'I', 'V', 'X', 'L', 'C', 'D', 'M' };
	int count = 0;
	while (d >= 0) {
		int pos = (digcount - 1 - d) * 2;
		int digit = dig[d];
		char *p = &roman[d][0];
		if (digit == 9) {
			*p = symbol[pos];
			*(p + 1) = symbol[pos + 2];
			*(p + 2) = 0;
			count += 2;
		}
		else {
			if (digit > 5) {
				digit -= 5;
				*p = symbol[pos + 1];
				p++;
				count++;
			}
			if (digit == 5) {
				*p = symbol[pos + 1];
				*(p + 1) = 0;
				count++;
			}
			else if (digit % 5 != 0 && digit % 5 < 4) {
				for (i = 0; i < digit; i++) {
					*(p + i) = symbol[pos];
					count++;
				}
				*(p + i) = 0;
			}
			else if (digit % 5 == 4) {
				*p = symbol[pos];
				*(p + 1) = symbol[pos + 1];
				*(p + 2) = 0;
				count += 2;
			}
		}
		--d;
	}

	char *romanStr = (char *)malloc(count + 1);
	int pos = 0;
	for (
		i = 0;
		i < digcount;
		i++) {
		char *p = &roman[i][0];
		while (*p != 0) {
			romanStr[pos] = *
				p;
			pos++;
			p++;
		}
	}
	romanStr[pos] = 0;
	return romanStr;
}


int main() {
	while (1) {
		cout << "Input the number:" << endl;
		int input;
		cin >> input;
		char *rm = roman(input);
		cout << rm << endl;
		delete[] rm;
	}
}


