// ZigZag conversion.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>
char* convert(char*, int);

int main()
{
	while (1) {
		printf("Input your string:\n");
		char buffer[1024];
		int rows = 0;
		scanf("%s%d", buffer, &rows);
		char* cov = convert(buffer, rows);
		printf("%s\n", cov);
		free(cov);
	}
}

char* convert(char* s, int rows) {
	int len = strlen(s);
	if (len < rows + 1) {
		char* str = (char*)malloc(len + 1);
		strcpy(str, s);
		str[len] = 0;
		return str;
	}
	char** all = (char**)malloc(rows*sizeof(char*));
	int* pos = (int*)malloc(rows*sizeof(int));
	//initialize array and counter
	for (int i = 0; i < rows; ++i) {
		all[i] = (char*)malloc(len + 1);
		pos[i] = 0;
	}
	int i = 0;
	while (i < len)
	{
		int first = 0;
		int last = rows;
		while (last > first && i < len) {
			for (int j = first; j < last && i < len; ++j) {
				all[j][pos[j]++] = s[i];
				i++;
			}
			first++;
			last--;
		}
	}
	char* str = (char*)malloc(len + 1);
	char* copy = str;
	for (int j = 0; j < rows; ++j) {
		memcpy(copy, all[j], pos[j]);
		copy += pos[j];
	}
	str[len] = 0;
	//cleanup
	for (int j = 0; j < rows; ++j)
		free(all[j]);
	free(all);
	free(pos);	
	//cleanup
	return str;
}
