// Subarray Sums Divisible by K.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

int subarraysDivByK(vector<int>& A, int K) {
	vector<int> remainders(K, 0);
	remainders[0] = 1;
	int count = 0;
	int sum = 0;
	for (int i = 0; i < A.size(); i++) {
		sum += A[i];
		auto rem = (sum % K + K) % K;		
			count += remainders[rem];
			remainders[rem]++;
	}
	return count;
}

int main()
{
	vector<int> array{ -2 };
	int count = subarraysDivByK(array, 6);
	cout << count;
}