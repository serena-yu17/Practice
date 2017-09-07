// Letterpermutationphonenumber.cpp : Defines the entry point for the console application.
//	Given a digit string, return all possible letter combinations of all possible permutations of the digits.
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

inline void swap(char *a, char *b) {
	char temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int factorial(int a) {
	int prod = 1;
	for (int i = 2; i < a + 1; i++) {
		prod *= i;
	}
	return prod;
}

char **permutation(char *arr, int *ct) {
	int len = strlen(arr);
	if (len == 0) {
		*ct = 0;
		return NULL;
	}
	if (len == 1) {
		*ct = 1;
		char **permutations = (char **)malloc(sizeof(char *));
		permutations[0] = (char *)malloc(2);
		permutations[0][0] = arr[0];
		permutations[0][1] = 0;
		return permutations;
	}
	int count = factorial(len) + 1;
	char **permutations = (char **)malloc(count * sizeof(char *));
	memset(permutations, 0, count * sizeof(char *));
	char *str = (char *)malloc(len + 1);
	strncpy(str, arr, len + 1);
	permutations[0] = str;
	count = 1;
	char *perm = (char *)malloc(len + 1);
	strncpy(perm, arr, len + 1);
	int *p = (int *)malloc(sizeof(int) * len);
	memset(p, 0, sizeof(int) * len);
	int i = len - 2;
	while (i >= 0) {
		if (p[i] < len - 1 - i) {
			int j = len - 1 - (i & 1) * p[i];
			if (perm[i] != perm[j]) {
				swap(perm + i, perm + j);
				permutations[count] = (char *)malloc(len + 1);
				strncpy(permutations[count], perm, len + 1);
				count++;
			}
			p[i]++;
			i = len - 2;
		}
		else
			p[i--] = 0;
	}
	free(perm);
	*ct = count;
	return permutations;
}

inline char getletter(char n, int ite) {
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

inline void incre(char* dig, int *pattern, int len) {
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

char *assign(char *num, int *pattern, int len) {
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
	int permCount;
	char **perm = permutation(digits, &permCount);
	int size = (int)pow(4, len) * permCount;
	char **comb = (char **)malloc(sizeof(char *) * size);
	int *pattern = (int *)malloc(len * sizeof(int));
	size = 0;
	for (int i = 0; i < permCount; i++) {
		memset(pattern, 0, len * sizeof(int));
		do {
			char *letters = assign(perm[i], pattern, len);
			if (letters[0] != 0)
				comb[size++] = letters;
			incre(perm[i], pattern, len);
		} while (notend(pattern, len));
	}
	free(pattern);
	for (int i = 0; i < permCount; i++)
		if (perm[i] != 0) {
			free(perm[i]);
			perm[i] = 0;
		}
	free(perm);
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

