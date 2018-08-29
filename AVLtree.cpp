// AVLtree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct treenode * position;
typedef struct treenode * searchtree;
struct treenode {
	int key;
	int height;
	searchtree left;
	searchtree right;
};

int height(searchtree T)
{
	if (T == NULL)
		return -1;
	else
		return T->height;
}

int max(int key1, int key2)
{
	return key1 > key2 ? key1 : key2;
}

void preodertraverse(searchtree T)
{
	if (T)
	{
		printf("%d ", T->key);
		preodertraverse(T->left);
		preodertraverse(T->right);
	}
}

void inordertraverse(searchtree T)
{
	if (T)
	{
		inordertraverse(T->left);
		printf("%d ", T->key);
		inordertraverse(T->right);
	}
}

void lastordertraverse(searchtree T)
{
	if (T)
	{
		lastordertraverse(T->left);
		lastordertraverse(T->right);
		printf("%d ", T->key);
	}
}

position find(searchtree T, int key)
{
	if (T != NULL)
	{
		if (T->key < key)return find(T->right, key);
		else
			if (T->key > key)return find(T->left, key);
			else return T;
	}
	else return NULL;
}

position findmin(searchtree T)
{
	searchtree tmp = T;
	if (T != NULL)
		while (tmp->left)
			tmp = tmp->left;
	return tmp;
}

position findmax(searchtree T)
{
	if (T)
		while (T->right)
			T = T->right;
	//改变T，没关系，因为T是复制的
	return T;
}

//先画图，子树以三角形代替
//以轴为中心，右节点向下旋转（以不平衡节点的儿子为轴）
//左子树比右子树高太多
//Left-Left情形
searchtree LLSingleRotate(searchtree T)
{
	searchtree tmp = T->left;
	T->left = tmp->right;
	tmp -> right = T;
	//T = tmp;//可以去掉，因为没用，T是复制的
	T->height = max(height(T->left), height(T->right))+1;
	tmp->height = max(height(tmp->left), T->height)+1;
	return tmp;
}

searchtree RRSingleRotate(searchtree T)
{
	searchtree tmp = T->right;
	T->right = tmp->left;
	tmp->left = T;
	T->height = max(height(T->left), height(T->right)) + 1;
	tmp->height = max(T->height, height(tmp->right)) + 1;

	return tmp;
}

searchtree LRDoubleRotate(searchtree T)
{
	T->left = RRSingleRotate(T->left);
	T = LLSingleRotate(T);
	return T;
}

searchtree RLDoubleRotate(searchtree T)
{
	T->right = LLSingleRotate(T->right);
	T = RRSingleRotate(T);
	return T;
}

searchtree insert(searchtree *p, int key)
{
	if (*p == NULL)
	{
		*p = (searchtree)malloc(sizeof(struct treenode));
		(*p)->key = key;
		(*p)->left = NULL;
		(*p)->right = NULL;
		(*p)->height = 0;
	}
	else
	{
		if (key > (*p)->key)
		{
			insert(&((*p)->right), key);
			if (height((*p)->right) - height((*p)->left) > 1)
			{
				if (key > ((*p)->right->key))*p=RRSingleRotate(*p);
				else *p=RLDoubleRotate(*p);
			}
		}
		else
			if (key < (*p)->key)
			{
				insert(&((*p)->left), key);
				if (height((*p)->left) - height((*p)->right) > 1)
				{
					if (key < (*p)->left->key)*p=LLSingleRotate(*p);
					else *p=LRDoubleRotate(*p);
				}
			}
			else
			{
				printf("can't insert the same value\n");
				exit(1);
			}
		(*p)->height = max(height((*p)->left), height((*p)->right)) + 1;
	}
	return *p;
}

searchtree create(int a[], int len)
{
	int i = 0;
	searchtree T = NULL;
	for (i = 0; i < len; i++)
	{
		insert(&T, a[i]);
	}
	return T;
}

searchtree Delete(searchtree T, int key)
{
	position tmp;
	if (T)
	{
		if (key > T->key)
		{
			T->right = Delete(T->right, key);
			if (height(T->left) - height(T->right)> 1)
			{
				if (height(T->left->left) >= height(T->left->right))T = LLSingleRotate(T);
				else T = LRDoubleRotate(T);
			}
		}
		//Delete()的返回值一定要赋给T->right，不然T->right删除节点后可能变成指向非法地址
		else
			if (key < T->key)
			{
				T->left = Delete(T->left, key);
				if (height(T->right) - height(T->left) > 1)
				{
					if (height(T->right->right) >=height(T->right->left))T = RRSingleRotate(T);
					else T = RLDoubleRotate(T);
				}
			}
			else
				if (T->left&&T->right)
				{
					tmp = findmax(T->left);
					T->key = tmp->key;
					T->left = Delete(T->left, T->key);
					//此时T->key为右子树最小值
				}
				else
					if (T->right == NULL)
						//如果是if(T->left)与if(T->right)不能处理无孩子的情况
						//或者再加一个if(!T->left&&!T->right)
					{
						tmp = T;
						T = T->left;
						free(tmp);
					}
					else
						if (T->left == NULL)
						{
							tmp = T;
							T = T->right;
							free(tmp);
						}
		if(T) T->height = max(height(T->left), height(T->right)) + 1;
		//尽管在if(T){}里，但T为空判断不能少，因为T在{}中间被改变了可能为空
	}
	else printf("not found\n");
	return T;
}

int main()
{
	int a[] = { 3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9 };
	searchtree T=NULL;
	int len = sizeof(a) / sizeof(a[0]);
	int i = 0;
	for (; i < len; i++)
		insert(&T, a[i]);
	preodertraverse(T);
	printf("\n");
	inordertraverse(T);
	printf("\n");
	lastordertraverse(T);
	printf("\n");
	Delete(T, 10);
	inordertraverse(T);
	printf("\n");
	printf("height:%d\n", height(T));
	printf("min:%d\n", findmin(T)->key);
	printf("max:%d\n", findmax(T)->key);

    return 0;
}

