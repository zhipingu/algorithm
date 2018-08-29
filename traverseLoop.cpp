// traverseLoop.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<iostream>
#include<string>
#include<vector>
#include<stack>

using namespace std;

struct treeNode
{
	int key;
	treeNode *leftChild;
	treeNode *rightChild;
};

void pre_traverseLoop(treeNode *T)
{
	if (!T) cerr << "treeNode is invalid" << endl;

	stack<treeNode *> nodes;
	treeNode *cur = T;
	do
	{
		cout << cur->key << " ";
		nodes.push(cur);
		cur = cur->leftChild;


		while (!cur && !nodes.empty())
		{
			cur = nodes.top();
			nodes.pop();
			cur = cur->rightChild;
		}

	} while (cur);
	cout << endl;
}

void in_traverseLoop(treeNode *T)
{
	if (!T)
	{
		cerr << "T is nullptr" << endl;
		return;
	}

	stack<treeNode *>nodes;

	treeNode *cur = T;

	while (cur)
	{
		nodes.push(cur);
		cur = cur->leftChild;
		while (!cur && !nodes.empty())
		{
			cur = nodes.top();
			nodes.pop();
			cout << cur->key << " ";
			cur = cur->rightChild;
		}
	}
	cout << endl;

}

void last_traverseLoop(treeNode *T)
{
	if (!T)
	{
		cerr << "T is nullptr" << endl;
		return;
	}

	stack<treeNode *> nodes;
	treeNode *cur = T, *pre = nullptr;
	
	while (cur || !nodes.empty())
	{
		while (cur)
		{
			nodes.push(cur);
			cur = cur->leftChild;
		}

		cur = nodes.top();

		if (cur->rightChild == nullptr || pre == cur->rightChild)
		{
			cout << cur->key << " ";
			pre = cur;
			nodes.pop();
			cur = nullptr;
		}
		else
		{
			cur = cur->rightChild;
		}

	}
	cout << endl;
}

void post_traverseLoop(treeNode *T)
{

	if (!T)
	{
		cerr << "T is nullptr" << endl;
		return;
	}

	enum Times {One,Two};
	stack<pair<treeNode *, Times>> nodes;
	treeNode *cur = T;

	while (cur || !nodes.empty())
	{
		while (cur)
		{
			nodes.push(make_pair(cur, One));
			cur = cur->leftChild;
		}
		
		if (!nodes.empty())
		{
			cur = nodes.top().first;
			Times t = nodes.top().second;
			nodes.pop();

			if (t == One)
			{
				nodes.push(make_pair(cur, Two));
				cur = cur->rightChild;
			}
			else if(t==Two)
			{
				cout << cur->key << " ";
				cur = nullptr;
			}
		}

	}
	cout << endl;
}

treeNode *insert(treeNode *root, int key)
{

	if (!root)
	{
		treeNode *newnode = new treeNode;
		newnode->key = key;
		newnode->leftChild = nullptr;
		newnode->rightChild = nullptr;

		root = newnode;
		return root;
	}

	if (key>root->key) root->rightChild = insert(root->rightChild, key);
	else if (key<root->key) root->leftChild = insert(root->leftChild, key);

	return root;
}

void PrintLevel(treeNode *root, int level)
{
	if (!root) return;
	if (level<1) return;

	if (level == 1) cout << root->key << " ";
	else if (level>1)
	{
		PrintLevel(root->leftChild, level - 1);
		PrintLevel(root->rightChild, level - 1);
	}
}

void print(treeNode *root, int levels)
{
	if (!root) return;

	for (int i = 1; i <= levels; ++i)
	{
		PrintLevel(root, i);
		cout << endl;
	}
}

int main()
{
	treeNode *root1 = nullptr, *root2 = nullptr;
	int a[] = { 12,10,17,7,11,14,18,13,16 };
	int b[] = { 17,14,18 };

	int len = sizeof(a) / sizeof(a[0]);
	int len2 = sizeof(b) / sizeof(b[0]);

	for (int i = 0; i<len; ++i)
	{
		root1 = insert(root1, a[i]);
	}

	for (int i = 0; i<len2; ++i)
	{
		root2 = insert(root2, b[i]);
	}

	cout << "level----------------->" << endl;
	print(root1, 4);
	cout << "===========" << endl;
	print(root2, 2);

	cout << "pre------------------>" << endl;
	pre_traverseLoop(root1);
	cout << "==========" << endl;
	pre_traverseLoop(root2);
	cout << "last==========" << endl;
	last_traverseLoop(root1);

	cout << "post==========" << endl;
	last_traverseLoop(root1);

	return 0;
}

