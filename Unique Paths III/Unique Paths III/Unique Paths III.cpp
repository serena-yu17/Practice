// Unique Paths III.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*
On a 2-dimensional grid, there are 4 types of squares:

1 represents the starting square.  There is exactly one starting square.
2 represents the ending square.  There is exactly one ending square.
0 represents empty squares we can walk over.
-1 represents obstacles that we cannot walk over.
Return the number of 4-directional walks from the starting square to the ending square, that walk over every non-obstacle square exactly once.



Example 1:

Input: [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
Output: 2
Explanation: We have the following two paths:
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)
Example 2:

Input: [[1,0,0,0],[0,0,0,0],[0,0,0,2]]
Output: 4
Explanation: We have the following four paths:
1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)
Example 3:

Input: [[0,1],[2,0]]
Output: 0
Explanation:
There is no path that walks over every empty square exactly once.
Note that the starting and ending square can be anywhere in the grid.


Note:

1 <= grid.length * grid[0].length <= 20
*/

#include "pch.h"
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

struct Point {
	int32_t x = 0;
	int32_t y = 0;
};

struct PointHash {
	size_t operator()(Point p) const noexcept {
		return size_t(p.x) << 32 | p.y;
	}
};

int exploreStartingCondition(vector<vector<int>>& const grid, Point& startPoint) {
	int count = 0;
	for (int row = 0; row < grid.size(); row++)
		for (int col = 0; col < grid[row].size(); col++) {
			if (grid[row][col] == 0)
				count++;
			if (grid[row][col] == 1) {
				startPoint.x = row;
				startPoint.y = row;
			}
		}
	return count;
}

Point findNext(vector<vector<int>>& const grid, Point& const currentPoint) {

}

int dfs(vector<vector<int>>& const grid, Point& const startPoint, const int emptyCount) {
	int pathCount = 0;
	int passedEmptyCount = 0;
	unordered_set <Point, PointHash> usedPoints;
	vector<Point> stack;

}

int uniquePathsIII(vector<vector<int>>& const grid) {
	Point startPt;
	int emptyCount = exploreStartingCondition(grid, startPt);
	if (emptyCount == 0)
		return 0;
	if (startPt.x == -1 || startPt.y == -1)
		return 0;
	return dfs(grid, startPt, emptyCount);
}

int main()
{

}
