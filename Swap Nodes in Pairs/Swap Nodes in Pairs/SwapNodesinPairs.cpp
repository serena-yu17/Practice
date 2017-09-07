// SwapNodesinPairs.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<vector>

using namespace std;

struct ListNode {
	int val;
	struct ListNode *next;
};

struct ListNode* swapPairs(struct ListNode* head) {
	struct ListNode* front = head;
	struct ListNode* last = NULL;
	while (front != NULL && front->next != NULL) {
		struct ListNode* second = front->next;
		struct ListNode* further = second->next;
		if (front == head)
			head = second;
		else
			last->next = second;
		second->next = front;
		front->next = further;
		last = front;
		front = front->next;
	}
	return head;
}


int main()
{
	ListNode* l1 = new ListNode();
	ListNode* last = l1;
	vector<int> arr;
	string input;
	cout << "Input list: " << endl;
	getline(cin, input);
	for (int i = 0; i < input.size(); i++)
	{
		int buffer = 0;
		int read = 0;
		while (i < input.size() && !isdigit(input[i]))
			i++;
		while (i < input.size() && isdigit(input[i]))
		{
			buffer *= 10;
			buffer += input[i] - '0';
			read = 1;
			i++;
		}
		if (read == 1)
			arr.push_back(buffer);
	}
	l1->val = arr[0];
	for (int i = 1; i < arr.size(); i++)
	{
		ListNode* nextNode = new ListNode();
		nextNode->val = arr[i];
		last->next = nextNode;
		last = nextNode;
	}
	last->next = NULL;
	ListNode* res = swapPairs(l1);
	ListNode* iterator = res;
	cout << "New list is: " << endl;
	while (iterator) {
		cout << iterator->val << ' ';
		ListNode* temp = iterator->next;
		delete iterator;
		iterator = temp;
	}
	cout << endl;
	cin.ignore(100, '\n');
	cin.clear();
	return 0;
}

