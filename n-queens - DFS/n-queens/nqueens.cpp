// nqueens.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <sstream>
#include <unordered_map>
using namespace std;

int n;


struct point
{
	int y;
	int x;
	int64_t* grid = NULL;
	point* last = NULL;
	point(int x0, int y0)
	{
		x = x0;
		y = y0;
	}
	bool operator==(point& other)
	{
		return x == other.x && y == other.y;
	}
	bool operator!=(point& other)
	{
		return !(*this == other);
	}
	~point()
	{
		if (grid)
			delete grid;
	}
};


vector<point*>* bfs(vector<point*>* level, int y, vector<point*>& allPoints, unordered_map<int64_t, int>& pow2)
{
	vector<point*>* newLevel = new vector<point*>();
	for (point* pt : *level)
	{
		while (pt->grid[y] & ((1 << n) - 1))
		{
			int64_t firstPosition = pt->grid[y] & (-pt->grid[y]);
			const int x = pow2[firstPosition];
			pt->grid[y] &= ~firstPosition;
			int64_t* grid = new int64_t[n];
			memcpy(grid + y, pt->grid + y, sizeof(int64_t)*(n - y));
			int j = 1;
			while (y + j < n)
			{
				if (x + j < n)
					grid[y + j] &= ~(1 << (x + j));
				if (x - j > -1)
					grid[y + j] &= ~(1 << (x - j));
				grid[y + j] &= ~(1 << x);
				j++;
			}
			point *nxtPt = new point(x, y);
			nxtPt->grid = grid;
			nxtPt->last = pt;
			newLevel->push_back(nxtPt);
			allPoints.push_back(nxtPt);
		}
	}
	delete level;
	return newLevel;
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
	vector<point*> allPoints;
	vector<int*>* result = new vector<int*>();
	vector<point*>* level = new  vector<point*>();
	for (int x = 0; x < n; x++)
	{
		int64_t* grid = new int64_t[n];
		memset(grid, -1, n * sizeof(int64_t));
		int j = 1;
		while (j < n)
		{
			if (x + j < n)
				grid[j] &= ~(1 << (x + j));
			if (x - j > -1)
				grid[j] &= ~(1 << (x - j));
			grid[j] &= ~(1 << x);
			j++;
		}
		point *nxtPt = new point(x, 0);
		nxtPt->grid = grid;
		level->push_back(nxtPt);
		allPoints.push_back(nxtPt);
	}
	for (int y = 1; y < n; y++)
		level = bfs(level, y, allPoints, pow2);
	for (point* pt : *level)
	{
		int* res = new int[n];
		while (pt)
		{
			res[pt->y] = pt->x;
			pt = pt->last;
		}
		result->push_back(res);
	}
	for (point* pt : allPoints)
		delete pt;
	allPoints.clear();
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

