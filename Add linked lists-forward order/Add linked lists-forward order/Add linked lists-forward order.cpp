// Add linked lists-forward order.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct ListNode
{
	int val;
	struct ListNode *next;
};

char* addition(const char* add1, int length1, const char* add2, int length2)
{
	int i, flag = 0, diff = length1 - length2;;
	char* output = new char[length1 + 1];
	for (i = length1 - 1; i >= diff; i--)
	{
		int tempdigi, tail1, tail2;
		tail1 = add1[i];
		tail2 = add2[i - diff];
		tempdigi = tail1 + tail2 + flag;
		flag = 0;
		if (tempdigi >= 10)
		{
			tempdigi %= 10;
			flag = 1;
		}
		output[i + 1] = tempdigi;
	}
	//copy the remaining digits
	if (diff > 0)
	{
		i = diff - 1;
		while (i >= 0)
		{
			int tempdigi = add1[i] + flag;
			flag = 0;
			if (tempdigi >= 10)
			{
				tempdigi %= 10;
				flag = 1;
			}
			output[i + 1] = tempdigi;
			i--;
		}
	}
	if (flag == 1)
		output[0] = 1;
	else output[0] = 'x';
	return output;
}

int countlinklist(struct ListNode* list)
{
	int count = 0;
	while (list != NULL)
	{
		count++;
		list = list->next;
	}
	return count;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
{
	struct ListNode *output = new ListNode();
	char* arr1 = new char[countlinklist(l1)];
	char* arr2 = new char[countlinklist(l2)];
	int count1 = 0, count2 = 0;
	while (l1 != NULL)
	{
		arr1[count1] = l1->val;
		count1++;
		l1 = l1->next;
	}
	while (l2 != NULL)
	{
		arr2[count2] = l2->val;
		count2++;
		l2 = l2->next;
	}
	char* sum;
	if (count1 >= count2)
		sum = addition(arr1, count1, arr2, count2);
	else
		sum = addition(arr2, count2, arr1, count1);
	int len = 1 + (count1 > count2 ? count1 : count2);
	int i = 0;
	while ((sum[i] == 0 || sum[i] == 'x') && i < len)
		i++;
	if (i == len)
	{
		output->val = 0;
		output->next = NULL;
		return output;
	}
	output->val = sum[i];
	i++;
	struct ListNode *last = output;
	while (i < len)
	{
		struct ListNode* nextNode = new ListNode();
		last->next = nextNode;
		last = nextNode;
		nextNode->val = sum[i];
		i++;
	}
	delete[] sum;
	delete[] arr1;
	delete[] arr2;
	last->next = NULL;
	return output;
}

const int ARRAY_SIZE = 1000;

int main()
{
	while (1)
	{
		struct ListNode* l1 = new ListNode();
		struct ListNode* last = l1;
		int arr[2][ARRAY_SIZE];
		string input;
		char buffer[ARRAY_SIZE+1];
		int pos = 0;
		int posi[2] = { 0,0 };
		for (int s = 0; s < 2; s++)
		{
			cout << "Input list #" << s + 1 << " : " << endl;
			getline(cin, input);
			cin.clear();
			for (int i = 0; i < input.size(); i++)
			{
				while (!isdigit(input[i]) && i < input.size())
					i++;
				memset(buffer, '0', ARRAY_SIZE);
				while (isdigit(input[i]) && i < input.size())
				{
					buffer[ARRAY_SIZE - 1 - pos] = input[i];
					pos++;
					i++;
				}
				buffer[ARRAY_SIZE] = 0;
				if (pos != 0)
				{
					arr[s][posi[s]++] = atoi(buffer);
					pos = 0;
				}
			}
			input.clear();
		}
		l1->val = arr[0][0];
		for (int i = 1; i < posi[0]; i++)
		{
			struct ListNode* nextNode = new ListNode();
			last->next = nextNode;
			last = nextNode;
			nextNode->val = arr[0][i];
		}
		last->next = NULL;
		struct ListNode* l2 = new ListNode();
		last = l2;
		l2->val = arr[1][0];
		for (int i = 1; i < posi[1]; i++)
		{
			struct ListNode* nextNode = new ListNode();
			last->next = nextNode;
			last = nextNode;
			nextNode->val = arr[1][i];
		}
		last->next = NULL;
		struct ListNode* sum = addTwoNumbers(l1, l2);
		struct ListNode* iterator = sum;
		cout << "Sum is: " << endl;
		while (iterator != NULL)
		{
			cout << iterator->val << ' ';
			iterator = iterator->next;
		}
		cout << endl;
		struct ListNode* ite = l1;
		while (ite->next != NULL)
		{
			struct ListNode* temp = ite->next;
			delete ite;
			ite = temp;
		}
		ite = l2;
		while (ite->next != NULL)
		{
			struct ListNode* temp = ite->next;
			delete[] ite;
			ite = temp;
		}
		getchar();
	}
}



