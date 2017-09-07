// RemoveNthNodeFromEndofList.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}

};

ListNode* removeNthFromEnd(ListNode* head, int n) {
	if (n == 1) {
		if (head->next == NULL)
			return NULL;
		ListNode* ite = head;
		while (ite->next->next != NULL)
			ite = ite->next;
		ite->next = NULL;
		return head;
	}
	vector<ListNode*> list;
	ListNode* ite = head;
	while (ite) {
		list.push_back(ite);
		ite = ite->next;
	}
	if (list.size() > n) {
		int pos = list.size() - n;
		ListNode* temp = list[pos];
		list[pos - 1]->next = list[pos + 1];
		delete temp;
	}
	else if (list.size() == n) {
		ListNode* temp = head;
		head = head->next;
		delete temp;
	}
	return head;
}

const int ARRAY_SIZE = 1000;

int main()
{
	while (1)
	{
		ListNode* l1 = new ListNode(0);
		ListNode* last = l1;
		int arr[ARRAY_SIZE];
		int count = 0;
		string input;
		cout << "Input list: " << endl;
		getline(cin, input);
		int n;
		cout << "Input target number:" << endl;
		cin >> n;
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
				arr[count++] = buffer;
		}
		l1->val = arr[0];
		for (int i = 1; i < count; i++)
		{
			ListNode* nextNode = new ListNode(arr[i]);
			last->next = nextNode;
			last = nextNode;
		}
		last->next = NULL;
		ListNode* res = removeNthFromEnd(l1, n);
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
	}
	return 0;
}

