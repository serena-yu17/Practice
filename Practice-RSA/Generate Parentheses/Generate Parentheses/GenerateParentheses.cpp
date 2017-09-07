// GenerateParentheses.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;


vector<string> generateParentheses(int n) {
	vector<string> result;
	string cur;
	int plen = 2 * n;
	int* pattern = new int[plen];
	for (int i = 0; i < n; i++) {
		pattern[i] = 0;
		pattern[n + i] = 1;
	}
	do {
		int paren = 0;
		for (int i = 0; i < plen; i++) {
			if (!pattern[i]) {
				cur.push_back('(');
				paren++;
			}
			else {
				if (paren == 0) {
					paren = -1;
					break;
				}
				else {
					cur.push_back(')');
					paren--;
				}
			}
		}
		if (paren == 0)
			result.push_back(cur);
		cur.clear();
	} while (next_permutation(pattern + 1, pattern + plen - 1));
	delete[] pattern;
	return result;
}


int main()
{
	cout << "Input number of pairs:" << endl;
	int n;
	cin >> n;
	vector<string> result = generateParentheses(n);
	for (auto a : result)
		cout << "\n" << a;
	cout << endl;
	cin.ignore(100, '\n');
	cin.clear();
	getchar();
}

