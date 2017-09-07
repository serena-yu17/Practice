// RSA.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include<iostream>
#include<cmath>
#include <string>
using namespace std;

long RSA(long baseN, long key, long Msg);

int main()
{
	const long p = 13, q = 19;
	long baseM, keym, Msgm, r;
	long i;
	baseM = p*q;
	r = (p - 1)*(q - 1);
	//cout << r;
	long e=1, d=1, s;
	s = long(sqrt(r + 1));
	for (i = s-1; i >1; --i)
	{
		if ((r+1) % i ==0 && r % i > 0)
		{
			d = i;
			e = (r + 1) / d;
			break;
		}
	}
	cout << "p=" << p << "\tq=" << q << "\tr=" << r << "\te=" << e <<"\td="<< d <<"\td*e="<<d*e<<endl;
	cout << "Input your number: ";
	cin >> Msgm;
	long Encrypted = RSA(baseM, e, Msgm);
	cout << "Encrypted=" << Encrypted<<endl;
	long Unencrpyt = RSA(baseM, d, Encrypted);
	cout << "Unencrypted=" << Unencrpyt << endl;
	cin >> e;
}

long powmod(long n, long b, long a)
{
	long mod=1;
	while (b)
	{
		if (b % 2)
		{
			mod = (mod*a) % n;
		}
		a = (a*a) % n;
		b = b / 2;
	}
	return mod;
}

long RSA(long baseN, long key, long Msg)
{
	if (baseN > 0 && key > 0 && Msg > 0)
	{
		return powmod(baseN, key, Msg);
	}
	else
	{
		cout << "The key cannot be equal or smaller than 0."<<endl;
	}
}