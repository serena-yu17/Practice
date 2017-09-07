// Practice-Longest Palindromic Substring.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
using namespace std;

char* longestPalindrome(char*);


int main()
{
	while (1)
	{
		char str[256];
		scanf("%s", str);
		char* out = longestPalindrome(str);
		printf("%s\n", out);
		free(out);
	}
}

char* longestPalindrome(char* s)
{
	int i = 0, maxlen = 0, begin = 0;
	if (strlen(s) != 0 && strlen(s) != 1)
	{
		while (i < strlen(s) - 1)
		{
			int count = 1;
			while (s[i + count] == s[i])
				count++;
			if (count > 0 && (count & 1) == 0)
			{
				i += (count >> 1) - 1;
				int j = count >> 1;
				while (i + 1 + j < strlen(s) && i - j >= 0 && s[i - j] == s[i + 1 + j])
					j++;
				int len = j * 2;
				if (len > maxlen)
				{
					maxlen = len;
					begin = i - j + 1;
				}
				i += (count >> 1) - 1;
			}
			else if ((count & 1) == 1)
			{
				i += count >> 1;
				if (i > 0 && s[i - 1] == s[i + 1])
				{
					int j = (count >> 1) + 1;
					while (i + j < strlen(s) && i - j >= 0 && s[i - j] == s[i + j])
						j++;
					int len = j * 2 - 1;
					if (len > maxlen)
					{
						maxlen = len;
						begin = i - j + 1;
					}
					i += count >> 1;
				}
			}
			i++;
		}
	}
	if (maxlen != 0)
	{
		char* output = (char*)malloc(maxlen + 1);
		memcpy(output, s + begin, maxlen);
		output[maxlen] = 0;
		return output;
	}
	else
	{
		char* output = (char*)malloc(1);
		output[0] = s[0];
		return output;
	}
}
