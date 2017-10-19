// InsertDeleteGetRandom.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <random>
using namespace std;

class RandomizedSet
{
private:
	unordered_map<int, int> location;
	vector<int> arr;
public:
	bool insert(int num)
	{
		if (location.find(num) == location.end())
		{
			arr.push_back(num);
			location[num] = arr.size() - 1;
			return 1;
		}
		return 0;
	}
	bool remove(int num)
	{
		if (location.find(num) != location.end())
		{
			if (arr.size() == 1)
			{
				location.clear();
				arr.clear();
			}
			else
			{
				int loc = location[num];
				location[arr.back()] = loc;
				location.erase(num);
				arr[loc] = arr.back();
				arr.pop_back();
			}
			return 1;
		}
		return 0;
	}

	int getRandom()
	{
		if (arr.size())
		{
			int id = rand() % (arr.size());
			return arr[id];
		}
		return 0;
	}
};


int main()
{
	ios::sync_with_stdio(false);
	RandomizedSet rd = RandomizedSet();
	cout << rd.insert(0) << ' ';
	cout << rd.remove(0) << ' ';
	cout << rd.insert(-1) << ' ';
	cout << rd.remove(0) << ' ';
	for (int i = 0; i < 10; i++)
		cout << rd.getRandom() << ' ';
	return 0;
}

