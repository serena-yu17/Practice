// Longest Substring Without Repeating Characters.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lengthOfLongestSubstring(char*);

int main()
{
	while (1)
	{
		printf("Input your string:\n");
		char inputbuffer[32767];
		scanf("%s", inputbuffer);
		printf("%d\n", lengthOfLongestSubstring(inputbuffer));
	}
	return 0;
}

int lengthOfLongestSubstring(char* s)
{
	int maxLength = 0, i = 0, begin = 0;
	int len = strlen(s);
	int charmap[256];
	memset(charmap, -1, 256 * sizeof(int));
	while (i < len)
	{
		if (charmap[s[i]] != -1)
		{
			int rep_pos = charmap[s[i]];
			if (i - begin > maxLength)
				maxLength = i - begin;
			for (int j = begin; j < rep_pos; j++)
				charmap[s[j]] = -1;
			begin = rep_pos + 1;
		}
		charmap[s[i]] = i;
		i++;
	}
	if (i - begin > maxLength)
		maxLength = i - begin;
	return maxLength;
}