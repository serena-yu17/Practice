// multiplystrings.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

char* add(char* num1, char* num2)
{
	int carry = 0;
	int len1 = strlen(num1);
	int len2 = strlen(num2);
	if (len1 < len2)
	{
		//swap num1 and num2 to make sure that num1 is equal or longer than num2
		char* temp = num2;
		num2 = num1;
		num1 = temp;
		int tmpLen = len2;
		len2 = len1;
		len1 = tmpLen;
	}
	char* result = (char*)malloc(len1 + 2);
	if (!len2)
	{
		memcpy(result, num1, len1 + 1);
		return result;
	}
	result[len1 + 1] = '\0';
	int dig1 = len1 - 1;
	int dig2 = len2 - 1;
	int digres = len1;
	while (dig2 > -1)
	{
		int dig = carry + num1[dig1] - '0' + num2[dig2] - '0';
		carry = 0;
		if (dig > 9)
		{
			carry = dig / 10;
			dig %= 10;
		}
		result[digres] = dig + '0';
		dig1--;
		dig2--;
		digres--;
	}
	while (dig1 > -1)
	{
		int dig = carry + num1[dig1] - '0';
		carry = 0;
		if (dig > 9)
		{
			dig -= 10;
			carry = 1;
		}
		result[digres] = dig + '0';
		dig1--;
		digres--;
	}
	if (carry)
		result[digres] = carry + '0';
	else
		for (int i = 1; i < len1 + 2; i++)
			result[i - 1] = result[i];
	return result;
}

char* calcMult(char* num1, int len1, char* num2, int len2)
{
	if (!len1 || !len2 || (len1 == 1 && num1[0] == '0') || (len2 == 1 && num2[0] == '0'))
	{
		char* prod = (char*)malloc(2);
		prod[0] = '0';
		prod[1] = '\0';
		return prod;
	}
	if (len1 < len2)
	{
		//swap num1 and num2 to make sure that num1 is equal or longer than num2
		char* temp = num2;
		num2 = num1;
		num1 = temp;
		int tmpLen = len2;
		len2 = len1;
		len1 = tmpLen;
	}
	if (len2 == 1)
	{
		char* result = (char*)malloc(len1 + 2);
		result[len1 + 1] = '\0';
		int carry = 0;
		int dig1 = len1 - 1;
		int digRes = len1;
		while (dig1 > -1)
		{
			int dig = (num1[dig1] - '0') * (num2[0] - '0') + carry;
			carry = 0;
			if (dig > 9)
			{
				carry = dig / 10;
				dig %= 10;
			}
			result[digRes] = dig + '0';
			dig1--;
			digRes--;
		}
		if (carry)
			result[digRes] = carry + '0';
		else
			for (int i = 1; i < len1 + 2; i++)
				result[i - 1] = result[i];
		return result;
	}
	else
	{
		int rightLen = len2 >> 1;
		int leftLen1 = len1 - rightLen;
		int leftLen2 = len2 - rightLen;
		char* leftRes = calcMult(num1, leftLen1, num2, leftLen2);
		char* rightRes = calcMult(num1 + leftLen1, rightLen, num2 + leftLen2, rightLen);
		char* mid1 = calcMult(num1, leftLen1, num2 + leftLen2, rightLen);
		char* mid2 = calcMult(num1 + leftLen1, rightLen, num2, leftLen2);
		//shift the left part left by 2 * rightLen 
		int lenLeftRes = strlen(leftRes);
		int lenLeftPart = lenLeftRes + 2 * rightLen;
		leftRes = (char*)realloc((void*)leftRes, lenLeftPart + 1);
		if (!leftRes)
			return NULL;
		memset(leftRes + lenLeftRes, '0', 2 * rightLen);
		leftRes[lenLeftPart] = '\0';
		char* result = add(leftRes, rightRes);
		//shift the mid parts left by rightLen
		int lenMid1 = strlen(mid1);
		int lenMid1Part = lenMid1 + rightLen;
		mid1 = (char*)realloc((void*)mid1, lenMid1Part + 1);
		if (!mid1)
			return NULL;
		memset(mid1 + lenMid1, '0', rightLen);
		mid1[lenMid1Part] = '\0';
		result = add(result, mid1);
		//shift the second mid left by rightLen
		int lenMid2 = strlen(mid2);
		int lenMid2Part = lenMid2 + rightLen;
		mid2 = (char*)realloc((void*)mid2, lenMid2Part + 1);
		if (!mid2)
			return NULL;
		memset(mid2 + lenMid2, '0', rightLen);
		mid2[lenMid2Part] = '\0';
		result = add(result, mid2);
		free(leftRes);
		free(rightRes);
		return result;
	}
}

char* multiply(char* num1, char* num2)
{
	int len1 = strlen(num1);
	int len2 = strlen(num2);
	return calcMult(num1, len1, num2, len2);
}

int main()
{
	cout << "Input the first string: ";
	string n1;
	cin >> n1;
	cout << "Input the second string: ";
	string n2;
	cin >> n2;
	char* num1 = const_cast<char*>(n1.c_str());
	char* num2 = const_cast<char*>(n2.c_str());
	char* result = multiply(num1, num2);
	cout << result << endl;
	cin.ignore('\n', 10);
	cin.clear();
	free(result);
	getchar();
	return 0;
}

