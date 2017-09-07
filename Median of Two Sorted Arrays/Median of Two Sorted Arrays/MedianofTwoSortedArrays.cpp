// MedianofTwoSortedArrays.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <limits>
using namespace std;

void swap_p(int** a, int** b) {
	int* temp = *a;
	*a = *b;
	*b = temp;
}

void swap_v(int*a, int*b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
	int med1_1 = (nums1Size - 1) >> 1;
	int med2_2 = (nums2Size - 1) >> 1;
	double med1f, med2f;
	if (nums1Size & 1)
		med1f = (double)nums1[med1_1];
	else
		med1f = ((double)nums1[med1_1 + 1] + nums1[med1_1]) / 2;
	if (nums2Size & 1)
		med2f = (double)nums2[med2_2];
	else
		med2f = ((double)nums2[med2_2 + 1] + nums2[med2_2]) / 2;
	if (nums1Size == 0 && nums2Size != 0)
		return med2f;
	if (nums2Size == 0 && nums1Size != 0)
		return med1f;
	if (nums1Size == 1 && nums2Size == 1)
		return ((double)nums1[0] + nums2[0]) / 2;
	if (med1f == med2f)
		return med1f;
	// keep median 1 < median 2 for convenience.
	if (nums1[med1_1] > nums2[med2_2]) {
		swap_p(&nums1, &nums2);
		swap_v(&nums1Size, &nums2Size);
		swap_v(&med1_1, &med2_2);
	}
	if (nums2[0] >= nums1[nums1Size - 1]) {
		int target = (nums1Size + nums2Size - 1) >> 1;
		if (target > nums1Size - 1)
			if ((nums1Size + nums2Size) & 1)
				return nums2[target - nums1Size];
			else
				return ((double)nums2[target - nums1Size] + nums2[target - nums1Size + 1]) / 2;
		else if (target == nums1Size - 1)
			if ((nums1Size + nums2Size) & 1)
				return nums1[target];
			else
				return ((double)nums1[target] + nums2[0]) / 2;
		else if ((nums1Size + nums2Size) & 1)
			return nums1[target];
		else
			return ((double)nums1[target] + nums1[target + 1]) / 2;
	}
	else {
		int med1_2 = 0;	//find the corresponding median value in the other array
		while (nums2[med1_2] < nums1[med1_1])
			++med1_2;
		int target = (nums1Size + nums2Size - 1) >> 1;
		int p1 = med1_1, p2 = med1_2;
		int* last = NULL;
		while (p1 < nums1Size  && p2 < nums2Size  && p1 + p2 < target + 1) {
			if (nums1[p1] <= nums2[p2]) {
				last = &nums1[p1];
				p1++;
			}
			else {
				last = &nums2[p2];
				p2++;
			}
		}
		while (p1 < nums1Size  && p1 + p2 < target + 1) {
			last = &nums1[p1];
			p1++;
		}
		while (p2 < nums2Size  && p1 + p2 < target + 1) {
			last = &nums2[p2];
			p2++;
		}
		int med = 0;
		if (last == NULL)
			med = nums1[med1_1];
		else {
			med = *last;
		}
		if ((nums1Size + nums2Size) & 1) {
			return (double)med;
		}
		else {
			int next;
			if (p1 > nums1Size - 1) {
				p1 = nums1Size - 1;
				if (nums1[p1] <= med)
					nums1[p1] = INT_MAX;
			}
			else if (p2 > nums2Size - 1) {
				p2 = nums2Size - 1;
				if (nums2[p2] <= med)
					nums2[p2] = INT_MAX;
			}
			next = nums1[p1] < nums2[p2] ? nums1[p1] : nums2[p2];
			return ((double)med + next) / 2;
		}
	}
}


vector<int> getint(string s) {
	if (s.size() == 0)
		return vector<int>();
	int buffer = 0;
	vector<int> nums;
	int i = 0;
	while (i < s.size()) {
		int isPos = 1;
		int filled = 0;
		while (i < s.size() && (isdigit(s[i]) || s[i] == '-')) {
			if (s[i] == '-' && buffer == 0) {
				isPos = -1;
				i++;
			}
			else {
				buffer *= 10;
				buffer += s[i] - '0';
				i++;
				filled = 1;
			}
		}
		if (filled == 1)
			nums.push_back(buffer * isPos);
		i++;
		buffer = 0;
		filled = 0;
	}
	return nums;
}

int main()
{
	while (1) {
		cout << "Input your arrays in two lines:" << endl;
		string raw;
		int i = 0;
		vector<int> vec[2];
		while (i < 2 && getline(cin, raw)) {
			vec[i] = getint(raw);
			sort(vec[i].begin(), vec[i].end());
			i++;
			raw.clear();
		}
		int* arr1 = new int[vec[0].size()];
		int* arr2 = new int[vec[1].size()];
		int len1 = 0, len2 = 0;
		while (len1 < vec[0].size())
			arr1[len1++] = vec[0][len1];
		while (len2 < vec[1].size())
			arr2[len2++] = vec[1][len2];
		double med = findMedianSortedArrays(arr1, len1, arr2, len2);
		cout << med << endl;
		delete[] arr1;
		delete[] arr2;
	}
	return 0;
}

