// KthNumInBinTree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
using namespace std;

struct TreeNode {
	int key;
	struct TreeNode *Left;
	struct TreeNode *Right;
	TreeNode(int x) :
		key(x), Left(NULL), Right(NULL) {
	}
};

TreeNode* KthNode(TreeNode* pRoot, int k)
{
	if (!pRoot || k <= 0)
		return nullptr;

	static int cnt = 0;
	TreeNode *result = nullptr;

	if (pRoot->Left)
		result = KthNode(pRoot->Left, k);

	if (!result)
	{
		++cnt;
		if (k == cnt)
		{
			result = pRoot;
			return result;
		}
	}

	if (!result && pRoot->Right)
		result = KthNode(pRoot->Right, k);

	return result;
}

TreeNode *insert(TreeNode *pRoot, int key)
{
	if (!pRoot)
	{
		TreeNode *newroot = new TreeNode(key);
		return newroot;
	}

	if (key > pRoot->key)
		pRoot->Right=insert(pRoot->Right, key);

	else
		if (key < pRoot->key)
			pRoot->Left=insert(pRoot->Left, key);

	return pRoot;
}

int main()
{
	//int a[] = { 8,6,10,5,7,9,11 };
	int a[] = { 5,3,7,2,4,6,8 };
	int len = sizeof(a) / sizeof(a[0]);

	TreeNode *pRoot=nullptr;
	for (int i = 0; i < len; ++i)
	{
		pRoot = insert(pRoot, a[i]);
	}
	
	TreeNode *result = KthNode(pRoot, 2);
	cout<<result->key << endl;
    return 0;
}

