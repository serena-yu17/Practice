// DistinctString.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct hashItem
{
	struct hashItem* next;
	int strStart;
} hashItem;

unsigned int hashStr(char* begin, char* end)
{
	unsigned int value = 5381;
	char* p = begin;
	char c;
	while (p < end)
	{
		c = *p;
		if (*p >= 'A' && *p <= 'Z')
			c += 32;
		value = (value << 5) + value + c;
		p++;
	}
	return value;
}

int strCaseCompare(char* a, char* b, int len)
{
	for (int i = 0; i < len; i++)
		if (a[i] != b[i] || a[i] - b[i] == 32 || b[i] - a[i] == 32)
			return 0;
	return 1;
}

void printWords(char* strArray, int targetLength)
{
	if (!targetLength)
		return;
	unsigned slen = strlen(strArray);
	unsigned *words = (unsigned*)malloc(slen * sizeof(*words));			   // Stores all the starting letter of words
	unsigned* wordLength = (unsigned*)malloc(slen * sizeof(*wordLength));		   // Stores length of words
	char* hashValue = (char*)malloc(slen * sizeof(*hashValue));		   // Stores hash value of words
	memset(hashValue, 0, slen * sizeof(*hashValue));
	hashItem** hashNum = (hashItem**)malloc(slen * sizeof(*hashNum));
	memset(hashNum, 0, slen * sizeof(*hashNum));
	unsigned usedItem = 0;
	unsigned count = 0;
	unsigned i = 0;
	unsigned collision = 0;
	while (i < slen)
	{
		int len = 0;
		while (i < slen && ((strArray[i] >= 'a' && strArray[i] <= 'z') || (strArray[i] >= 'A' && strArray[i] <= 'Z')))
		{
			i++;
			len++;
		}
		if (len == targetLength)
		{
			//build hash
			//This part can be omitted, but it will dramatically reduce the string comparison needed 
			unsigned int hashCode = hashStr(&strArray[i - len], &strArray[i]);
			int hashPos = hashCode % slen;
			int repeated = 0;
			int start = i - len;
			if (hashValue[hashPos])
			{
				hashItem* front = hashNum[hashPos];
				while (front)
				{
					if (strCaseCompare(&strArray[start], &strArray[front->strStart], len))
					{
						repeated = 1;
						break;
					}
					front = front->next;
				}
			}
			if (!repeated)
			{
				words[count] = start;
				wordLength[count] = len;
				hashValue[hashPos] = 1;
				hashItem* newNode = (hashItem*)malloc(sizeof(*newNode));
				newNode->next = NULL;
				newNode->strStart = start;
				usedItem++;
				if (!hashNum[hashPos])
					hashNum[hashPos] = newNode;
				else
				{
					hashItem* front = hashNum[hashPos];
					while (front->next)
						front = front->next;
					front->next = newNode;
					collision++;
				}
				count++;
			}
		}
		i++;
	}
	//print
	printf("{");
	for (unsigned i = 0; i < count; i++)
	{
		if (i)
			printf(" ");
		for (unsigned j = words[i]; j < words[i] + wordLength[i]; j++)
		{
			char c = strArray[j];
			if (strArray[j] >= 'A' && strArray[j] <= 'Z')
				c += 32;
			printf("%c", c);
		}
	}
	printf("}");
	free(words);
	free(wordLength);
	free(hashValue);
	for (int i = 0; i < slen; i++)
	{
		hashItem* front = hashNum[i];
		while (front)
		{
			hashItem* temp = front->next;
			free(front);
			front = temp;
		}
	}
	free(hashNum);
}

int main()
{
	int capacity = 256;
	char* strArray = (char*)malloc(capacity);
	int p = 0;
	puts("Input words:");
	char c;
	while (EOF != (c = getchar()) && c != '\n' && c != '\r')
	{
		strArray[p++] = c;
		if (p == capacity)
		{
			capacity *= 2;
			char* temp = (char*)realloc((void*)strArray, capacity);
			if (!temp)
			{
				puts("Memory allocation failed.");
				return 1;
			}
			strArray = temp;
		}
	}
	strArray[p++] = '\0';
	puts("Input your desired length:");
	int targetLength;
	char buffer[10];
	fgets(buffer, 10, stdin);
	targetLength = atoi(buffer);
	puts("The generated array is:");
	printWords(strArray, targetLength);
	getchar();
	free(strArray);
	return 0;
}

