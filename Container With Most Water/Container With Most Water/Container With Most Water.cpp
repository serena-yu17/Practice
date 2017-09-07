// Container With Most Water.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <random>
#include <time.h>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

int min(int a, int b) {
	return a < b ? a : b;
}


int maxArea(vector<int>& height) {
	int heightSize = height.size();
	int last = heightSize - 1;
	if (heightSize <= 1)
		return 0;
	if (heightSize == 2)
		return min(height[0], height[last]);
	int maxa = 0, start = 0;
	while (start < last) {
		int h = min(height[start], height[last]);
		int area = h*(last - start);
		if (area > maxa)
			maxa = area;
		while (start < last && height[start] <= h)
			start++;
		while (start < last && height[last] <= h)
			last--;
	}
	return maxa;
}


int main()
{
	while (1) {
		cout << "Input numbers." << endl;
		string s;
		getline(cin, s);
		std::stringstream myss;
		myss << s;
		string t;
		int x;
		vector<int> numbers;
		while (getline(myss, t, ','))
		{
			if (stringstream(t) >> x)
			{
				numbers.push_back(x);
			}
		}
		cout << "The generated numbers are: " << endl;
		int num = numbers.size();
		for (auto a : numbers)
			cout << '\t' << a;
		cout << endl;
		int area = maxArea(numbers);
		cout << "Max area = " << area << endl;
		getchar();
	}
}

