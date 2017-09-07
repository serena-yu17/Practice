// multiplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <thread>
#include <cstring>

#include "multiplication.h"
using namespace std;

void iterate(ul, ul, vector<Numset>*);
void calc(ul, ul, vector<Numset>*);
//
const int n_threads = 7;
//


int main()
{
	while (1)
	{
		cout << "Input the largest number looking for:" << endl;
		ul ub;
		cin >> ub;
		vector<Numset> numset[n_threads];
		if (ub < 11)
			continue;
		if (ub < 1001)
		{
			iterate(10, ub, &numset[0]);
			for (auto a : numset[0])
				cout << a.num1 << " * " << a.num2 << " = " << a.res << ", Columns = " << a.col << endl;
		}
		else
		{
			thread* trd[n_threads];
			ul unit = (ub - 10) / n_threads;
			for (int i = 0; i < n_threads; i++)
			{
				ul low = i * unit + 10;
				ul high = low + unit + 10;
				trd[i] = new thread(iterate, low, high, &numset[i]);
			}
			for (int i = 0; i < n_threads; i++)
				trd[i]->join();
			for (int i = 0; i < n_threads; i++)
			{
				for (auto a : numset[i])
					cout << a.num1 << " * " << a.num2 << " = " << a.res << ", Columns = " << a.col << endl;
				delete trd[i]; trd[i] = nullptr;
			}
		}
	}
	//the end
	return 0;
}

void iterate(ul low, ul high, vector<Numset>* numset)
{
	for (ul i = 10; i < high; i++)
	{
		for (ul j = low; j <= i; j++)
			calc(i, j, numset);
	}
}

void calc(ul num1, ul num2, vector<Numset>* numset)
{
	char* sn1 = new char[11];
	snprintf(sn1, 11, "%llu", num1);
	char* sn2 = new char[11];
	snprintf(sn2, 11, "%llu", num2);
	int len_num2 = strlen(sn2);
	char** res = new char*[len_num2 + 1];
	res[len_num2] = new char[strlen(sn1) + strlen(sn2) + 1];
	ul res3 = num1 * num2;
	snprintf(res[len_num2], strlen(sn1) + strlen(sn2) + 1, "%llu", res3);
	int maxlen = strlen(res[len_num2]);
	//if (num1 == 65536 && num2 == 65536)
	//	__debugbreak();
	for (int i = 0; i < len_num2; i++)
	{
		res[i] = new char[maxlen + 1];
		int cur_dig = (sn2[len_num2 - 1 - i] - '0');
		ul cur_res = num1 * cur_dig;
		snprintf(res[i], maxlen + 1, "%llu", cur_res);
		align(&res[i], i, maxlen);
	}
	align(&sn1, 0, maxlen);
	align(&sn2, 0, maxlen);
	int* column = new int[maxlen];
	memset(column, 0, maxlen * sizeof(int));
	int equal = 1;
	for (int i = 0; i < maxlen; i++)
	{
		column[i] += sn1[i] - '0';
		column[i] += sn2[i] - '0';
		for (int j = 0; j < len_num2 + 1; j++)
			column[i] += res[j][i] - '0';
		if (i > 0 && column[i] != column[i - 1])
		{
			equal = 0;
			break;
		}
	}
	if (equal == 1)
	{
		Numset goodset(num1, num2, res3, column[0]);
		(*numset).push_back(goodset);
	}
	//cleanup:
	delete[] sn1; sn1 = nullptr;
	delete[] sn2; sn2 = nullptr;
	//clean res members
	for (int i = 0; i < len_num2 + 1; i++)
	{
		delete[] res[i]; res[i] = nullptr;
	}
	delete[] res; res = nullptr;
	delete[] column; column = nullptr;
}

//align to maxlen with n of 0 at the end (equavalent to multiply 10^n)
void align(char** s, int n, int maxlen)
{
	char* source = *s;
	int len = strlen(source);
	if (len == maxlen)
	{
		if (n == 0)
			return;
		for (int i = 0; i < len - n; i++)
			source[i] = source[i + n];
		memset(&source[len - n], '0', n);
		return;
	}
	char* target = new char[maxlen + 1];
	memset(target, '0', maxlen);
	int i;
	for (i = 0; i < len && i < maxlen - n; i++)
		target[maxlen - 1 - i - n] = source[len - 1 - i];
	target[maxlen] = 0;
	delete[] * s;
	*s = target;
}

Numset::Numset(ul n1, ul n2, ul r, int c)
{
	num1 = n1;
	num2 = n2;
	res = r;
	col = c;
}