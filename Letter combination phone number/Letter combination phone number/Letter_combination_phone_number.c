// Lettercombinationphonenumber.cpp : Defines the entry point for the console application.
//Given a digit string, return all possible letter combinations that the number could represent.


#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

inline char getletter(char const n, int const ite) {
	int num = n - '0' - 2;
	int ch = 0;
	if (num >= 0 && num < 5)
		ch = num * 3 + ite + 'a';
	else if (num == 5)
		ch = 'a' + 15 + ite;
	else if (num == 6)
		ch = 'a' + 19 + ite;
	else if (num == 7)
		ch = 'a' + 22 + ite;
	return (char)ch;
}

inline void incre(char const* dig, int *pattern, int const len) {
	int limit[] = { 3,3,3,3,3,4,3,4 };
	int ex = 1;
	int i = len - 1;
	while (i >= 0 && ex != 0) {
		while (dig[i] < '2')
			i--;
		pattern[i] += ex;
		ex = 0;
		if (pattern[i] > limit[dig[i] - '2'] - 1) {
			pattern[i] = 0;
			ex = 1;
			i--;
		}
	}
}

inline int notend(int const *pattern, int len) {
	for (int i = 0; i < len; i++)
		if (pattern[i])
			return 1;
	return 0;
}

char *assign(char const* num, int const* pattern, int const len) {
	char *text = (char *)malloc(len + 1);
	int count = 0;
	int i;
	for (i = 0; i < len; i++) {
		if (num[i] == '0')
			text[count++] = ' ';
		else if (num[i] > '1' && num[i] <= '9') {
			text[count++] = getletter(num[i], pattern[i]);
		}
	}
	text[count] = 0;
	return text;
}

char **letterCombinations(char *digits, int *returnSize) {
	int len = strlen(digits);
	if (len == 0) {
		*returnSize = 0;
		return NULL;
	}
	int size = (int)pow(4, len);
	char **comb = (char **)malloc(sizeof(char *) * size);
	int *pattern = (int *)malloc(len * sizeof(int));
	memset(pattern, 0, len * sizeof(int));
	size = 0;
	do {
		char *letters = assign(digits, pattern, len);
		if (letters[0] != 0)
			comb[size++] = letters;
		incre(digits, pattern, len);
	} while (notend(pattern, len));
	free(pattern);
	*returnSize = size;
	return comb;
}

int main() {
	while (1) {
		printf("Input your array: ");
		char raw[100];
		scanf("%s", raw);
		int size;
		char **result = letterCombinations(raw, &size);
		for (int i = 0; i < size; i++) {
			printf("%s", result[i]);
			if (i != size - 1)
				printf(",");
		}
		printf("\n\n");
		for (int i = 0; i < size; i++)
			free(result[i]);
		free(result);
	}
	return 0;
}

