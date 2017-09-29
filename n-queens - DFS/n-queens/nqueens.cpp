// nqueens.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <thread>
using namespace std;

int n;


struct point
{
	int y;
	int x;
	point(int x0, int y0)
	{
		x = x0;
		y = y0;
	}
	point()
	{	}
	bool operator==(point& other)
	{
		return x == other.x && y == other.y;
	}
	bool operator!=(point& other)
	{
		return !(*this == other);
	}
};


void dfs(vector<int*>* result, int x0, int y0, unordered_map<int64_t, int>& pow2)
{
	vector<point> stack;
	int64_t ** grid = new int64_t*[n];
	for (int i = 0; i < n; i++)
		grid[i] = new int64_t[n];
	point root = point(x0, y0);
	int j = 1;
	memset(grid[root.y], -1, n * sizeof(int64_t));
	while (y0 + j < n)
	{
		if (x0 + j < n)
			grid[root.y][y0 + j] &= ~(1 << (x0 + j));
		if (x0 - j > -1)
			grid[root.y][y0 + j] &= ~(1 << (x0 - j));
		grid[root.y][y0 + j] &= ~(1 << x0);
		j++;
	}
	stack.push_back(root);
	while (stack.size())
	{
		point* top = &stack[stack.size() - 1];
		int y = top->y + 1;
		if (grid[top->y][y] & ((1 << n) - 1) && stack.size() != n)
		{
			point nxt = point();
			int64_t firstPosition = grid[top->y][y] & (-grid[top->y][y]);
			const int x = pow2[firstPosition];
			nxt.x = x;
			nxt.y = y;
			memcpy(grid[nxt.y] + y, grid[top->y] + y, (n - y) * sizeof(int64_t));
			grid[nxt.y][y] &= ~firstPosition;
			j = 1;
			while (y + j < n)
			{
				if (x + j < n)
					grid[nxt.y][y + j] &= ~(1 << (x + j));
				if (x - j > -1)
					grid[nxt.y][y + j] &= ~(1 << (x - j));
				grid[nxt.y][y + j] &= ~(1 << x);
				j++;
			}
			stack.push_back(nxt);
		}
		else {
			if (stack.size() == n)
			{
				int* res = new int[n];
				for (int i = 0; i < n; i++)
					res[i] = stack[i].x;
				result->push_back(res);
			}
			memset(grid[top->y] + top->y, -1, (n - top->y) * sizeof(int64_t));
			if (stack.size() > 1)
				grid[stack[stack.size() - 2].y][top->y] &= ~(1 << top->x);
			stack.pop_back();
		}
	}
	for (int i = 0; i < n; i++)
		delete[] grid[i];
	delete[] grid;
}

const char* int2char(const int64_t& in)
{
	int size = CHAR_BIT * sizeof(int64_t);
	char* result = new char[size + 1];
	result[size] = 0;
	int i = size - 1;
	int64_t n = in;
	while (i > -1)
	{
		result[i--] = (n & 1) + '0';
		n >>= 1;
	}
	return result;
}

int64_t power(int base, int n)
{
	if (!base && n)
		return 0;
	int64_t pow = 1;
	while (n) {
		if (n & 1)
			pow *= base;
		base *= base;
		n >>= 1;
	}
	return pow;
}


vector<int*>* queens()
{
	unordered_map<int64_t, int> pow2;
	for (int i = 0; i < 63; i++)
		pow2[power(2, i)] = i;
	vector<int*>** searchResult = new vector<int*>*[n]();
	vector<int*>* result = new vector<int*>();
	vector<thread> th;
	for (int x = 0; x < n; x++)
	{
		searchResult[x] = new vector<int*>();
		th.push_back(thread(dfs, searchResult[x], x, 0, pow2));
	}
	for (int x = 0; x < n; x++)
	{
		th[x].join();
		for (int* comb : *searchResult[x])
			result->push_back(comb);
		delete searchResult[x];
	}
	delete searchResult;
	return result;
}


int main()
{
	ios::sync_with_stdio(false);
	while (1)
	{
		cout << "Enter number of queens:" << endl;
		cin >> n;
		if (n > 62)
		{
			cout << "Input too large too handle.\n" << endl;
			continue;
		}
		auto start = chrono::steady_clock::now();
		vector<int*>* result = queens();
		auto duration = chrono::duration_cast<std::chrono::milliseconds>(chrono::steady_clock::now() - start);
		cout << "Time elapsed: " << duration.count() << "ms" << endl;
		cout << "Number of solutions: " << result->size() << "\n" << endl;
		for (int* comb : *result)
			delete comb;
		delete result;
		/*cout << "Print number of solution:" << endl;
		int nSolution;
		cin >> nSolution;
		int* line = (*result)[nSolution];
		for (int i = 0; i < n; i++)
		cout << line[i];
		cout << endl;*/
	}
	return 0;
}

