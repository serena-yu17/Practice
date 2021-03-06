// House Robber III.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <climits>
#include <sstream>
#include <string>

using namespace std;

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

inline bool isNull(string& const s, int i)
{
	if (i < s.size() - 4 && (s[i] == 'n' || s[i] == 'N') && (s[i + 1] == 'u' || s[i + 1] == 'U')
		&& (s[i + 2] == 'l' || s[i + 2] == 'L') && (s[i + 3] == 'l' || s[i + 3] == 'L'))
		return 1;
	return 0;
}

std::vector<int> getint(std::string& const s)
{
	if (s.size() == 0)
		return std::vector<int>();
	std::vector<int> nums;
	int i = 0;
	while (i < s.size())
	{
		int buffer = 0;
		int found = 0;
		int neg = 0;
		if (s[i] == '-')
			neg = 1;
		while (i < s.size() && isdigit(s[i]))
		{
			buffer *= 10;
			buffer += s[i] - '0';
			i++;
			found = 1;
		}
		if (found)
		{
			if (neg)
				buffer = -buffer;
			nums.push_back(buffer);
		}
		if (isNull(s, i))
		{
			nums.push_back(INT_MIN);
			i += 4;
		}
		i++;
	}
	return nums;
}


vector<TreeNode*>* buildLevel(vector<TreeNode*>* level, const vector<int>& num, int& p)
{
	vector<TreeNode*>* nextLv = new vector<TreeNode*>;
	for (int i = 0; i < level->size() && p < num.size(); i++)
	{
		if ((*level)[i])
		{
			if (num[p] != INT_MIN)
				(*level)[i]->left = new TreeNode(num[p]);
			else
				(*level)[i]->left = NULL;
			nextLv->push_back((*level)[i]->left);
			p++;
			if (p < num.size())
			{
				if (num[p] != INT_MIN)
					(*level)[i]->right = new TreeNode(num[p]);
				else
					(*level)[i]->right = NULL;
				nextLv->push_back((*level)[i]->right);
				p++;
			}
		}
		else
		{
			p++;
			if (p < num.size())
				p++;
		}
	}
	delete level;
	return nextLv;
}

TreeNode* buildTree(const vector<int>& num)
{
	if (num[0] == INT_MIN)
		return NULL;
	TreeNode* root = new TreeNode(num[0]);
	if (num.size() == 1)
		return 	root;
	vector<TreeNode*>* level = new vector<TreeNode*>;
	level->push_back(root);
	int p = 1;
	while (p < num.size())
		level = buildLevel(level, num, p);
	delete level;
	return root;
}

inline void clearTree(TreeNode* root)
{
	if (!root)
		return;
	if (root->left)
		clearTree(root->left);
	if (root->right)
		clearTree(root->right);
	delete root;
}

// C {
typedef struct TreeNode TreeNode;
int seek(TreeNode* node, int* currentSum)
{
	if (!node)
		return 0;
	int sumL = 0, sumR = 0;
	if (node->left)
		*currentSum += seek(node->left, &sumL);
	if (node->right)
		*currentSum += seek(node->right, &sumR);
	int inclusiveSum = node->val + sumL + sumR;
	if (inclusiveSum > *currentSum)
		return inclusiveSum;
	else
		return 	*currentSum;
}


int rob(TreeNode* const root)
{
	if (!root)
		return 0;
	int currentSum = 0;
	int maxSum = seek(root, &currentSum);
	return maxSum;
}
//} C


int main()
{
	while (1)
	{
		cout << "Input your tree:\n";
		string raw;
		getline(cin, raw);
		vector<int> nums = getint(raw);
		TreeNode* root = buildTree(nums);
		cout << rob(root) << endl;
		clearTree(root);
	}
	return 0;
}

