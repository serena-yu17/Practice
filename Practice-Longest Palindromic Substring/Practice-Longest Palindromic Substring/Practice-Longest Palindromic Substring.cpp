// Practice-Longest Palindromic Substring.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char* longestPalindrome(char*);
char* fillstr(char*);

int main()
{
	while (1)
	{
		printf("Input your string:\n");
		char str[32767];
		scanf("%s", str);
		char* out = longestPalindrome(str);
		printf("%s\n", out);
		free(out);
	}
}

char* fillstr(char* s)
{
	int len = strlen(s);
	int filledlen = len * 2 + 4;
	char* str = (char*)malloc(filledlen);
	str[0] = 29;	//any ASCII code can do except for letters, symbols and numbers.
	int i = 0;
	for (i = 1; i < len * 2; i += 2)
	{
		str[i] = 30;	//any ASCII code can do except for letters, symbols and numbers.
		str[i + 1] = s[(i - 1) / 2];
	}
	str[i] = 30;	//any ASCII code can do except for letters, symbols and numbers.
	str[filledlen - 2] = 31;	//any ASCII code can do except for letters, symbols and numbers.
	str[filledlen - 1] = 0;	//end of string
	return str;
}

char* longestPalindrome(char* s)
{
	char* str = fillstr(s);
	int len = strlen(str);
	int* palinCount = (int*)malloc(sizeof(int)*(len + 1));
	memset(palinCount, 0, (len + 1) * sizeof(int));
	int i = 0, range = 0, pivot = 0, maxpos = 0, maxlen = 0;
	int leftimage = 0;
	for (i = 0; i < len; i++)
	{
		if (pivot * 2 >= i)
		{
			leftimage = pivot * 2 - i;
			if (palinCount[leftimage] + i < range)
			{
				palinCount[i] = palinCount[leftimage];
				continue;
			}
		}
		while (str[i - palinCount[i] - 1] == str[i + palinCount[i] + 1])
			palinCount[i]++;
		range = i + palinCount[i];
		pivot = i;
		if (palinCount[i] > maxlen)
		{
			maxlen = palinCount[i];
			maxpos = i;
		}
	}
	char* out = (char*)malloc(maxlen * 2 + 1);
	int fill = 0;
	for (int j = maxpos - maxlen; j <= maxpos + maxlen; j++)
	{
		if (str[j] > 31)
		{
			out[fill++] = str[j];
		}
	}
	out[fill] = 0;	//end of string
	free(str);
	free(palinCount);
	return out;
}

