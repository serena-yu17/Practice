// Remove Comments.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> removeComments(const vector<string>& source)
{
	vector<string> out;
	bool valid = 1;
	bool continuousLine = 0;
	string newLine;
	for (string line : source)
	{		
		int i;
		for (i = 0; i < line.size(); i++)
		{
			if (line[i] == '/' && line[i + 1] == '/' && valid)
				break;
			else if (line[i] == '/' && line[i + 1] == '*' && valid)
			{
				valid = 0;
				i++;
				continuousLine = 1;
				continue;
			}
			if (line[i] == '*' && line[i + 1] == '/' && !valid)
			{
				valid = 1;
				i++;
				continuousLine = 0;
				continue;
			}
			if (valid)
				newLine.push_back(line[i]);
		}
		if (newLine.size() && !continuousLine)
		{
			out.push_back(newLine);
			newLine.clear();
		}
	}
	return out;
}


int main()
{
	vector<string> source = { "/*Test program */", "int main()", "{ ", "  // variable declaration ", "int a, b, c;", "/* This is a test", "   multiline  ", "   comment for ", "   testing */", "a = b + c;", "}" };
	for (auto line : source)
		cout << line << '\n';
	cout << "------------------\n";
	source = removeComments(source);
	for (auto line : source)
		cout << line << '\n';
	source = { "a/*comment", "line", "more_comment*/b" };
	for (auto line : source)
		cout << line << '\n';
	cout << "------------------\n";
	source = removeComments(source);
	for (auto line : source)
		cout << line << '\n';
	getchar();
	return 0;
}

