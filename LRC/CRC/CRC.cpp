// CRC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
using namespace std;
char LRC(char*);
int main()
{
	while (1)
	{
		cout << "Input your sequence: " << endl;
		char seq[1024];
		cin.getline(seq, 1024);
		printf("%s%c%c", "Your LRC is: ", LRC(seq), '\n');
		memset(seq, 0, 1024);
		cin.clear();
	}
}
char LRC(char* input)
{
	char lrc = 0;
	int i = 0;
	while (input[i] != 0)
	{
		lrc ^= input[i];
		i++;
	}
	return lrc;
}