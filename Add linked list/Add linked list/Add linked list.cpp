// Add linked list.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x){
		val = x;
		next = NULL;
	}	
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	ListNode *front1 = l1, *front2 = l2;
	ListNode* sum=new ListNode(0);
	ListNode* fronts = sum;
	int ex = 0;
	while (front1 || front2 || ex) {
		int dig, val1, val2;
		if (front1) {
			val1 = front1->val;
			front1 = front1->next;
		}
		else 
			val1 = 0;
		if (front2) {
			val2 = front2->val;
			front2 = front2->next;
		}
		else 
			val2 = 0;
		dig = ex + val1 + val2;
		ex = 0;
		if (dig > 9) {
			dig -= 10;
			ex = 1;
		}
		fronts->next = new ListNode(dig);
		fronts = fronts->next;
	}
	sum = sum->next;
	return sum;
}

const int ARRAY_SIZE = 1000;

int main()
{
	while (1)
	{
		struct ListNode* l1 = new ListNode(0);
		struct ListNode* last = l1;
		int arr[2][ARRAY_SIZE];
		string input;
		char buffer[ARRAY_SIZE + 1];
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
			struct ListNode* nextNode = new ListNode(0);
			last->next = nextNode;
			last = nextNode;
			nextNode->val = arr[0][i];
		}
		last->next = NULL;
		struct ListNode* l2 = new ListNode(0);
		last = l2;
		l2->val = arr[1][0];
		for (int i = 1; i < posi[1]; i++)
		{
			struct ListNode* nextNode = new ListNode(0);
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

