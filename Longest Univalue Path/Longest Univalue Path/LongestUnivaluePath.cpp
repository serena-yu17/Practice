// LongestUnivaluePath.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
using namespace std;

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int longestUnivaluePath(TreeNode* root)
{
	if (!root)
		return 0;
	vector<TreeNode*> stack;
	unordered_set<TreeNode*> usedPath;
	unordered_map<TreeNode*, unsigned> count;
	unordered_map<TreeNode*, TreeNode*> branch;
	unordered_map<TreeNode*, unsigned> maxBranchCount;
	stack.push_back(root);
	usedPath.insert(root);
	count[root] = 0;
	branch[root] = root;
	while (stack.size())
	{
		TreeNode* pt = stack[stack.size() - 1];				   // pointer to top of stack
		TreeNode* nxt = NULL;
		if (pt->left && usedPath.find(pt->left) == usedPath.end())
			nxt = pt->left;
		else if (pt->right && usedPath.find(pt->right) == usedPath.end())
			nxt = pt->right;
		if (nxt)
		{
			stack.push_back(nxt);
			usedPath.insert(nxt);
			if (nxt->val != pt->val)
			{
				count[nxt] = 0;
				branch[nxt] = nxt;
				if (maxBranchCount[branch[pt]] < count[pt])
					maxBranchCount[branch[pt]] = count[pt];
			}
			else
			{
				if (count[pt] == 0)
					branch[nxt] = nxt;
				else
					branch[nxt] = branch[pt];
				count[nxt] = count[pt] + 1;
			}
		}
		else
		{
			if (maxBranchCount[branch[pt]] < count[pt])
				maxBranchCount[branch[pt]] = count[pt];
			stack.pop_back();
		}
	}
	int longestLength = 0;
	for (auto node : maxBranchCount)
	{
		int len = 0;
		if (node.first->left && node.first->left->val == node.first->val)
			len += maxBranchCount[node.first->left];
		if (node.first->right && node.first->right->val == node.first->val)
			len += maxBranchCount[node.first->right];
		if (len > longestLength)
			longestLength = len;
	}
	return longestLength;
}

//The functions below are used to build the test cases

std::vector<int> getint(std::string s) {
	if (s.size() == 0)
		return std::vector<int>();
	std::vector<int> nums;
	int i = 0;
	while (i < s.size())
	{
		int buffer = 0;
		int found = 0;
		while (i < s.size() && (isdigit(s[i]) || s[i] == '-'))
		{
			buffer *= 10;
			buffer += s[i] - '0';
			i++;
			found = 1;
		}
		if (found)
			nums.push_back(buffer);
		if (i < s.size() - 4 && s[i] == 'n' && s[i + 1] == 'u' && s[i + 2] == 'l' && s[i + 3] == 'l')
		{
			nums.push_back(-1);
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
			if (num[p] != -1)
				(*level)[i]->left = new TreeNode(num[p]);
			else
				(*level)[i]->left = NULL;
			nextLv->push_back((*level)[i]->left);
			p++;
			if (p < num.size())
			{
				if (num[p] != -1)
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
	if (num[0] == -1)
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

void recPrintNode(FILE* fs, TreeNode* node, int* nullCount)
{
	if (node->left)
	{
		fprintf(fs, "    %d -> %d;\n", node->val, node->left->val);
		if (!node->right)
		{
			fprintf(fs, "    null%d [shape=point, ];\n", nullCount);
			fprintf(fs, "    %d -> null%d;\n", node->val, nullCount);
			*nullCount++;
		}
		recPrintNode(fs, node->left, nullCount);
	}
	if (node->right)
	{
		fprintf(fs, "    %d -> %d;\n", node->val, node->right->val);
		if (!node->left)
		{
			fprintf(fs, "    null%d [shape=point, ];\n", nullCount);
			fprintf(fs, "    %d -> null%d;\n", node->val, nullCount);
			*nullCount++;
		}
		recPrintNode(fs, node->right, nullCount);
	}
}

void print_dot(TreeNode* root)
{
	FILE* fs = fopen("./tree.gv", "w");
	fprintf(fs, "digraph BST {\n");
	fprintf(fs, "    node [fontname=\"Arial\"];\n");
	if (!root)
		fprintf(fs, "\n");
	else if (!root->left && root->right)
		fprintf(fs, "    %d;\n", root->val);
	else
	{
		int* nullCount = new int();
		recPrintNode(fs, root, nullCount);
		delete nullCount;
	}
	fprintf(fs, "}\n");
	fclose(fs);
}

int main()
{
	ios::sync_with_stdio(false);
	while (1)
	{
		cout << "Input the tree in rows:" << endl;
		string raw;
		getline(cin, raw);
		vector<int> num = getint(raw);
		TreeNode* root = NULL;
		if (num.size())
			root = buildTree(num);
		print_dot(root);
		system("dot -Tsvg ./tree.gv -o graph1.svg ");
		system("graph1.svg");
		cout << longestUnivaluePath(root) << endl;
	}
	return 0;
}

