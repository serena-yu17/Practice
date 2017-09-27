// nqueens.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <sstream>
using namespace std;

int n;

struct point
{
	int y;
	int x;
	int** grid = NULL;
	point* last = NULL;
	int children = 0;
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
		{
			for (int i = 0; i < n; i++)
				if (grid[i])
					delete[] grid[i];
			delete grid;
		}
	}
};

vector<point*>* bfs(vector<point*>* level, int y)
{
	vector<point*>* newLevel = new vector<point*>();
	for (point* pt : *level)
	{
		int found = 0;
		for (int x = 0; x < n; x++)
		{
			if (!pt->grid[y][x])
			{
				found = 1;
				int** grid = new int*[n]();
				for (int i = y; i < n; i++)
				{
					grid[i] = new int[n];
					memcpy(grid[i], pt->grid[i], n * sizeof(int));
				}
				int j = 1;
				while (y + j < n)
				{
					if (x + j < n)
						grid[y + j][x + j] = 1;
					if (x - j > -1)
						grid[y + j][x - j] = 1;
					grid[y + j][x] = 1;
					j++;
				}
				point *nxtPt = new point(x, y);
				nxtPt->grid = grid;
				nxtPt->last = pt;
				pt->children++;
				newLevel->push_back(nxtPt);
			}
		}
		if (!found)
		{
			while (pt && pt->children < 2)
			{
				point* temp = pt->last;
				delete pt;
				pt = temp;
			}
			if (pt)
				pt->children--;
		}
	}
	delete level;
	return newLevel;
}


vector<int*>* queens()
{
	vector<int*>* result = new vector<int*>();
	vector<point*>* level = new  vector<point*>();
	for (int x = 0; x < n; x++)
	{
		int** grid = new int*[n]();
		for (int i = 0; i < n; i++)
			grid[i] = new int[n]();
		int j = 1;
		while (j < n)
		{
			if (x + j < n)
				grid[j][x + j] = 1;
			if (x - j > -1)
				grid[j][x - j] = 1;
			grid[j][x] = 1;
			j++;
		}
		point *nxtPt = new point(x, 0);
		nxtPt->grid = grid;
		level->push_back(nxtPt);
	}
	for (int y = 1; y < n; y++)
		level = bfs(level, y);
	for (point* pt : *level)
	{
		int* res = new int[n];
		while (pt)
		{
			res[pt->y] = pt->x;
			point* temp = pt->last;
			if (!pt->children)
				delete pt;
			pt = temp;
		}
		result->push_back(res);
	}
	return result;
}


int main()
{
	ios::sync_with_stdio(false);
	while (1)
	{
		cout << "Enter number of queens:" << endl;
		cin >> n;
		auto start = chrono::steady_clock::now();
		vector<int*>* result = queens();
		auto duration = chrono::duration_cast<std::chrono::milliseconds>(chrono::steady_clock::now() - start);
		cout << "Time elapsed: " << duration.count() << "ms" << endl;
		cout << "Number of solutions: " << result->size() << endl;
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

