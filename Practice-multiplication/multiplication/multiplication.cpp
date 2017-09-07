// multiplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<math.h>
#include<string>

using namespace std;

char* addition(const char*, const char*);
char* subtract(const char*, const char*);
char* multiply(const char*, const char*);
char* power_s(const char*, unsigned long long);
void filterstr(const string&, char*);
void trimstr(char*);

int main()
{
	while (1)
	{
		std::cout << "Input positive integers x and y, separated by a space:" << endl;
		string temp1, temp2;
		cin >> temp1 >> temp2;
		if (temp1 == "\0" || temp2 == "\0")
			continue;
		char* multi1 = new char[temp1.size() + 1];
		filterstr(temp1, multi1);
		char* multi2 = new char[temp2.size() + 1];
		filterstr(temp2, multi2);
		if (multi1 == "\0" || multi2 == "\0")
			continue;
		cout << "Your inputs are: \nx = " << multi1 << ", y = " << multi2 << endl;
		char* sum = addition(multi1, multi2);
		cout << "x + y = " << sum << endl;
		char* subtr = subtract(multi1, multi2);
		cout << "x - y = " << subtr << endl;
		char* multip = multiply(multi1, multi2);
		cout << "x * y = " << multip << endl;
		if (strlen(multi2) < 20)
		{
			unsigned long long power_nth = atoll(multi2);
			char* power_output = power_s(multi1, power_nth);
			cout << "x to the " << power_nth << "th power = " << power_output << endl;
			delete[] power_output;
		}

		delete[] multi1;
		delete[] multi2;
		delete[] sum;
		delete[] subtr;
		delete[] multip;
	}
}

void filterstr(const string& s, char* output)
{
	int count = 0, size = s.size();
	for (int i = 0; i < size; i++)
	{
		if (isdigit(s[i]))
		{
			output[count] = s[i];
			count++;
		}
	}
	output[count] = 0;
	trimstr(output);
}


void fillstr(char* input, int size)
{
	for (int i = 0; i < size; i++)
		input[i] = '0';
}

void trimstr(char* input)
{
	int len = strlen(input);
	int i = 0;
	while (input[i] == '0')
		i++;
	char* output = new char[len - i + 1];
	memcpy(output, input + i, len - i);
	output[len - i] = '\0';
	for (int j = 0; j < len; j++)
		input[j] = 0;
	memcpy(input, output, len - i);
	input[len - i] = '\0';
	delete[] output;
}

void split(int left, int right, const char* input, char* output1, char* output2)
{
	memcpy(output1, input, left);
	output1[left] = 0;
	trimstr(output1);
	if (strlen(output1) == 0)
	{
		output1[0] = '0';
		output1[1] = 0;
	}
	memcpy(output2, (input + left), right);
	output2[right] = 0;
	trimstr(output2);
	if (strlen(output2) == 0)
	{
		output2[0] = '0';
		output2[1] = 0;
	}
}

char* addition(const char* add1, const char* add2)
{
	int i;
	int length1 = strlen(add1);
	int length2 = strlen(add2);
	if (length1 < length2)
	{
		return addition(add2, add1);
	}
	int flag = 0, diff = length1 - length2;
	char* output = new char[length1 + 2];
	fillstr(output, length1 + 2);
	for (i = length1 - 1; i >= diff; i--)
	{
		int tempdigi, tail1, tail2;
		tail1 = add1[i] - '0';
		tail2 = add2[i - diff] - '0';
		tempdigi = tail1 + tail2 + flag;
		flag = 0;
		if (tempdigi >= 10)
		{
			tempdigi %= 10;
			flag = 1;
		}
		output[i + 1] = tempdigi + '0';
	}
	//copy the remaining digits
	if (diff > 0)
	{
		i = diff - 1;
		while (i >= 0)
		{
			int tempdigi = add1[i] - '0' + flag;
			flag = 0;
			if (tempdigi >= 10)
			{
				tempdigi %= 10;
				flag = 1;
			}
			output[i + 1] = tempdigi + '0';
			i--;
		}
	}
	if (flag == 1)
		output[0] = '1';
	output[length1 + 1] = '\0';
	trimstr(output);
	return output;
}

char* minus_str(const char* input)
{
	int len = strlen(input);
	char* outputminus = new char[len + 2];
	memcpy(outputminus + 1, input, len);
	outputminus[0] = '-';
	outputminus[len + 1] = 0;
	return outputminus;
}

char* subtract(const char* sub1, const char* sub2)
{
	int i, minus;
	int length1 = strlen(sub1);
	int length2 = strlen(sub2);
	if (!strcmp(sub1, sub2))
	{
		char* output = new char[2];
		output[0] = '0';
		output[1] = 0;
		return output;
	}
	if (length1 < length2)
	{
		char* outputpos = subtract(sub2, sub1);
		char* outputminus = minus_str(outputpos);
		delete[] outputpos;
		return outputminus;
	}
	if (length1 == length2)
	{
		int flag = 0;
		for (i = 0; i <= length1 - 1; i++)
		{
			if (sub1[i] > sub2[i])
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			char* outputpos = subtract(sub2, sub1);
			char* outputminus = minus_str(outputpos);
			delete[] outputpos;
			return outputminus;
		}
	}
	int flag = 0, diff = length1 - length2;
	char* output = new char[length1 + 1];
	fillstr(output, length1 + 1);
	for (i = length1 - 1; i >= diff; i--)
	{
		int tempdigi, tail1, tail2;
		tail1 = sub1[i] - '0';
		tail2 = sub2[i - diff] - '0';
		tempdigi = tail1 - tail2 - flag;
		flag = 0;
		if (tempdigi < 0)
		{
			flag = 1;
			tempdigi += 10;
		}
		output[i] = tempdigi + '0';
	}
	//copy the remaining digits
	if (diff > 0)
	{
		for (i = diff - 1; i >= 0; i--)
		{
			int tempdigi = sub1[i] - '0' - flag;
			flag = 0;
			if (tempdigi < 0)
			{
				flag = 1;
				tempdigi += 10;
			}
			output[i] = tempdigi + '0';
		}
	}
	output[length1] = '\0';
	trimstr(output);
	return output;
}

char* multiply(const char* multi1, const char* multi2)
{
	int len1 = strlen(multi1), len2 = strlen(multi2);
	if (len1 == 0 || len2 == 0 || multi1 == "0" || multi2 == "0")
	{
		char* output = new char[1];
		output[0] = '0';
		return output;
	}
	if (len1 < 10 && len2 < 10)
	{
		unsigned long long output;
		output = atoll(multi1) * atoll(multi2);
		char * outputs = new char[len1 + len2 + 2];
		snprintf(outputs, len1 + len2 + 1, "%llu", output);
		outputs[len1 + len2 + 1] = '\0';
		trimstr(outputs);
		return outputs;
	}
	else if (len1 < 10)
	{
		int right = len2 >> 2;
		right <<= 1;
		int left = len2 - right;
		char* multi2_1 = new char[left + 1];
		char* multi2_2 = new char[right + 1];
		split(left, right, multi2, multi2_1, multi2_2);
		char* z1;
		z1 = multiply(multi1, multi2_1);
		char* z2;
		z2 = multiply(multi1, multi2_2);
		int lenz1 = strlen(z1);
		char* z1s = new char[lenz1 + right + 1];
		memcpy(z1s, z1, lenz1);
		int i;
		for (i = 0; i < right; i++)
		{
			z1s[i + lenz1] = '0';
		}
		z1s[lenz1 + right] = '\0';
		char* outputs;
		outputs = addition(z1s, z2);
		delete[] multi2_1; multi2_1 = NULL;
		delete[] multi2_2; multi2_2 = NULL;
		delete[] z1; z1 = NULL;
		delete[] z2; z2 = NULL;
		delete[] z1s; z1s = NULL;
		return outputs;
	}
	else if (len2 < 10)
	{
		return multiply(multi2, multi1);
	}
	else if (len1 < len2)
	{
		return multiply(multi2, multi1);
	}
	else
	{
		int right = len2 >> 2;
		right <<= 1;
		int left = len2 - right, diff = len1 - len2;
		char* multi1_1 = new char[left + diff + 1];
		char* multi1_2 = new char[right + 1];
		char* multi2_1 = new char[left + 1];
		char* multi2_2 = new char[right + 1];
		split((left + diff), right, multi1, multi1_1, multi1_2);
		split(left, right, multi2, multi2_1, multi2_2);
		char* z1, *z2, *z3;
		z1 = multiply(multi1_1, multi2_1);
		z2 = multiply(multi1_2, multi2_2);
		z3 = multiply(addition(multi1_1, multi1_2), addition(multi2_1, multi2_2));
		z3 = subtract(z3, z1);
		z3 = subtract(z3, z2);
		int i;
		int lenz1 = strlen(z1);
		char* z1s = new char[lenz1 + (right << 1) + 1];
		fillstr(z1s, lenz1 + (right << 1) + 1);
		memcpy(z1s, z1, lenz1);
		for (i = 0; i < (right << 1); i++)
		{
			z1s[i + lenz1] = '0';
		}
		z1s[lenz1 + (right << 1)] = '\0';
		int lenz3 = strlen(z3);
		char* z3s = new char[lenz3 + right + 1];
		fillstr(z3s, lenz3 + right + 1);
		memcpy(z3s, z3, lenz3);
		for (i = 0; i < right; i++)
		{
			z3s[i + lenz3] = '0';
		}
		z3s[lenz3 + right] = '\0';
		z3s = addition(z3s, z1s);
		z3s = addition(z3s, z2);
		trimstr(z3s);
		delete[] multi1_1;
		delete[] multi1_2;
		delete[] multi2_1;
		delete[] multi2_2;
		delete[] z1;
		delete[] z2;
		delete[] z3;
		return z3s;
	}
}

char* power_s(const char* input, unsigned long long nth)
{
	int len = strlen(input);
	char* output = new char[len * nth + 1];
	if (nth == 0)
	{
		output[0] = '1';
		output[1] = 0;
		return output;
	}
	if (nth == 1)
	{
		memcpy(output, input, len);
		output[strlen(input)] = 0;
		return output;
	}
	long long temp = nth;
	int count = log2(temp);
	char* record = new char[count];
	int i;
	temp = nth;
	i = 0;
	for (i = 0; i < count; i++)
	{
		record[i] = temp % 2;
		temp >>= 1;
	}
	memcpy(output, input, len);
	output[len] = 0;
	for (i = count - 1; i >= 0; i--)
	{
		output = multiply(output, output);
		if (!record[i])
			continue;
		else
			output = multiply(output, input);
	}
	delete[] record;
	trimstr(output);
	return output;
}
