// LeftHeap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>

typedef  struct treenode * leftheap;
struct treenode
{
	int key;
	leftheap leftchild;
	leftheap rightchild;
	int npl;
	
};
int nplmin(leftheap L)
{
	return L->leftchild->npl > L->rightchild->npl ? L->rightchild->npl : L->leftchild->npl;
}
leftheap merge(leftheap L1, leftheap L2)
{
	leftheap tmp = NULL;
	if (!L1)return L2;
	if (!L2)return L1;
	if (L1->key > L2->key)
	{
		tmp = L1;
		L1 = L2;
		L2 = tmp;
	}
	if (!L1->leftchild)
	{
		L1->leftchild = L2;
		return L1;
	}
/*	else
	{
		L1->rightchild = merge(L1->rightchild, L2);
		if (L1->leftchild->npl < L1->rightchild->npl)
		{
			tmp = L1->leftchild;
			L1->leftchild = L1->rightchild;
			L1->rightchild = tmp;
		}
		L1->npl = L1->rightchild->npl + 1;
		return L1;
	}
*/
	
/*		//可以把下面统一起来，通过交换操作，让L1绐终指向小左堆，让L2指向大左堆，如上。
	{
		if (L1->leftchild)
		{
			L1->rightchild = merge(L1->rightchild, L2);

			if (L1->leftchild->npl < L1->rightchild->npl)
			{
				tmp = L1->rightchild;
				L1->rightchild = L1->leftchild;
				L1->leftchild = tmp;
			}
			L1->npl = L1->rightchild->npl + 1;
		}
		else L1->leftchild = L2;
		return L1;
	}
	else
	{
		if (L2->leftchild)
		{
			L2->rightchild = merge(L2->rightchild, L1);
			if (L2->leftchild->npl < L2->rightchild->npl)
			{
				tmp = L2->rightchild;
				L2->rightchild = L2->leftchild;
				L2->leftchild = tmp;
			}
			L2->npl = L2->rightchild->npl + 1;
		}
		else L2->leftchild = L1;

		return L2;
	}
*/
//斜堆几乎无条件交换左右儿子
	else
	{
		L1->rightchild = merge(L1->rightchild, L2);
	//	if (L1->leftchild&&L1->rightchild)//这个可以不用，因为之前代码保证了这个条件
		{
			tmp = L1->leftchild;
			L1->leftchild = L1->rightchild;
			L1->rightchild = tmp;
		}
	//	L1->npl = nplmin(L1) + 1;
		return L1;
	}
}

leftheap insert(leftheap L, int key)
{
	leftheap newnode = (leftheap)malloc(sizeof(struct treenode));
	if (!newnode)
	{
		perror("newnode allocate fail");
		exit(1);
	}
	newnode->key = key;
	newnode->leftchild = newnode->rightchild = NULL;
	newnode->npl = 0;
	L = merge(L, newnode);
	return L;
}
void printlevel(leftheap L, int i)
{
	if (!L || i < 1)return;
	if (i==1)
	{
		printf("%d ", L->key);
		return;
	}
	printlevel(L->leftchild, i - 1);
	printlevel(L->rightchild, i - 1);
}
void leveltraverse(leftheap L,int level)
{
	if (!L||level<1)return;
	int i = 1;
	for (; i <= level; i++)
	{
		printlevel(L, i);
	}
	printf("\n=====\n");
}
leftheap Deletemin(leftheap L)
{
	leftheap left=NULL,right=NULL;
	if (!L)
	{
		perror("L is empty");
		exit(1);
	}
	left = L->leftchild;
	right = L->rightchild;
	free(L);
	return merge(left, right);
}
int main()
{
	int a[] = { 3,10,8,21,14,17,23,26 };
	int b[] = { 43,22,44,33,12,5 };
	int lena = sizeof(a) / sizeof(a[0]);
	int lenb = sizeof(b) / sizeof(b[0]);
	leftheap La=NULL,Lb=NULL;
	int i = 0;
	for (i=0; i < lena; i++)
	{
		La=insert(La,a[i]);
	}

	for (i=0; i < lenb; i++)
	{
		Lb = insert(Lb, b[i]);
	}

	leveltraverse(La, 4);
//	La=Deletemin(L);
	leveltraverse(Lb, 8);
	La=merge(La, Lb);
	leveltraverse(La,10);
	La = Deletemin(La);
	leveltraverse(La,10);

	return 0;
}

