// ceaser encode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void encrypt(char*, const char[]);
void decrypt(char*, const char[]);
char* filterstr(const string&);

int main()
{
	while (1)
	{
		string rawinput, rawkey;
		cout << "Input your text:" << endl;
		getline(cin, rawinput);
		while (rawkey.size() < 10)
		{
			cout << "Input your 10-character key:" << endl;
			getline(cin, rawkey);
		}
		char* input = new char[rawinput.size()];
		char key[10];
		int i = 0;
		for (i = 0; i < rawinput.size(); i++)
			input[i] = rawinput[i];
		input[i] = 0;
		for (i = 0; i < 10; i++)
			key[i] = rawkey[i];
		encrypt(input, key);
		cout << "Encrypted text is:\n" << input << endl;
		decrypt(input, key);
		cout << "Decrypted text is:\n" << input << '\n' << endl;
		delete[] input; 
	}
}

void encrypt(char* input, const char key[])
{
	int size = strlen(input), i = 0, j = 0;
	while (i < size)
	{
		if (j = 10)
			j = 0;
		input[i] = input[i] + key[j];
		i++; j++;
	}
}

void decrypt(char* input, const char key[])
{
	int size = strlen(input), i = 0, j = 0;
	while (i < size)
	{
		if (j = 10)
			j = 0;
		input[i] = input[i] - key[j];
		i++; j++;
	}
}
