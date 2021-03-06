// Maximum Length of Repeated Subarray.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

int findLength(const vector<int>& A, const vector<int>& B)
{
	int len1 = A.size(), len2 = B.size();
	if (!len1 || !len2)
		return 0;
	int** grid = new int*[len1 + 1];
	for (int i = 0; i < len1 + 1; i++)
		grid[i] = new int[len2 + 1]();
	int maxLen = 0;
	for (int y = 0; y < len2 + 1; y++)
		for (int x = 0; x < len1 + 1; x++)
		{
			if (!y || !x)
				grid[y][x] = 0;
			else if (A[x - 1] == B[y - 1])
			{
				grid[y][x] = grid[y - 1][x - 1] + 1;
				if (grid[y][x] > maxLen)
					maxLen = grid[y][x];
			}
		}
	for (int i = 0; i < len1 + 1; i++)
		delete[] grid[i];
	delete[] grid;
	return maxLen;
}

int main()
{
	vector<int> A = { 1,2,3,2,1 };
	vector<int> B = { 3,2,1,4,7 };
	cout << findLength(A, B);
	getchar();
	return 0;
}

