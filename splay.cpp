// splay.cpp : Defines the entry point for the console application.
//
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
	searchtree left;
	searchtree right;
	searchtree parent;
};

int max(int key1, int key2)
{
	return key1 > key2 ? key1 : key2;
}

void preordertraverse(searchtree T)
{
	if (T)
	{
		printf("%d ", T->key);
		preordertraverse(T->left);
		preordertraverse(T->right);
	}
}

void inordertraverse(searchtree T)
{
	if (T)
	{
		inordertraverse(T->left);
		printf("%d ", T->key);
		if (T->parent)printf("(%d) ", T->parent->key);
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
	searchtree greatergrandfather = T->parent->parent->parent;
	searchtree grandfather = T->parent->parent;
	grandfather->left = T->parent->right;
	if (T->parent->right)T->parent->right->parent = grandfather;

	T->parent->right = grandfather;
	grandfather->parent = T->parent;

	T->parent->left = T->right;
	if(T->right)T->right->parent = T->parent;

	T->right = T->parent;
	T->parent->parent = T;
	//LLL
	if (greatergrandfather&&((T->key) < (greatergrandfather->key)))
	{
		greatergrandfather->left = T;
		T->parent = greatergrandfather;
	}
	else 
		//RLL
		if (greatergrandfather&&((T->key) > (greatergrandfather->key)))
		{
			greatergrandfather->right = T;
			T->parent = greatergrandfather;
		}
	
	//也可以把括号里的T->parent = greatergrandfather;搬出来放这
	if (!greatergrandfather)T->parent = NULL;
	return T;
}

searchtree RRSingleRotate(searchtree T)
{
	searchtree greatergrandfather = T->parent->parent->parent;
	searchtree grandfather = T->parent->parent;
	grandfather->right = T->parent->left;
	if(T->parent->left)T->parent->left->parent = grandfather;

	T->parent->left = grandfather;
	grandfather->parent = T->parent;

	T->parent->right = T->left;
	if(T->left)T->left->parent = T->parent;

	T->left = T->parent;
	T->parent->parent = T;
	//RRR
	if(greatergrandfather&&((T->key) > (greatergrandfather->key)))
	{
		greatergrandfather->right = T;
		T->parent = greatergrandfather;
	}
	else 
		//LRR
		if (greatergrandfather&&((T->key) < (greatergrandfather->key)))
		{
			greatergrandfather->left = T;
			T->parent = greatergrandfather;
		}
	//T = tmp;//可以去掉，因为没用，T是复制的
	if (!greatergrandfather)T->parent = NULL;
	return T;
}

searchtree LRDoubleRotate(searchtree T)
{
	searchtree greatergrandparent = T->parent->parent->parent;
	searchtree grandparent = T->parent->parent;
	T->parent->right = T->left;
	if(T->left) T->left->parent = T->parent;

	T->left = T->parent;
	T->parent->parent = T;

	grandparent->left = T->right;
	if(T->right) T->right->parent = grandparent;

	T->right = grandparent;
	grandparent->parent = T;
	//LLR
	if (greatergrandparent&&((T->key) < (greatergrandparent->key)))
	{
		greatergrandparent->left = T;
		T->parent = greatergrandparent;
	}
	else 
		//RLR
		if (greatergrandparent&&((T->key) > (greatergrandparent->key)))
		{
			greatergrandparent->right = T;
			T->parent = greatergrandparent;
		}
	if (!greatergrandparent)T->parent = NULL;
	return T;
}

searchtree RLDoubleRotate(searchtree T)
{
	searchtree greatergrandparent = T->parent->parent->parent;
	searchtree grandparent = T->parent->parent;
	T->parent->left = T->right;
	if(T->right) T->right->parent = T->parent;

	T->right = T->parent;
	T->parent->parent = T;

	grandparent->right = T->left;
	if(T->left) T->left->parent = grandparent;

	T->left = grandparent;
	grandparent->parent = T;
	//RRL
	if (greatergrandparent&&((T->key) > (greatergrandparent->key)))
	{
		greatergrandparent->right = T;
		T->parent = greatergrandparent;
	}
	//LRL
	else 
		if (greatergrandparent && ((T->key) < (greatergrandparent->key)))
		{
				greatergrandparent->left = T;
				T->parent = greatergrandparent;
		}
	if (!greatergrandparent)T->parent = NULL;
	return T;
}

searchtree SingleWithoutGrand(searchtree T)
{
	if (T->key > T->parent->key)
	{
		T->parent->right = T->left;
		if(T->left)	T->left->parent = T->parent;

		T->left = T->parent;
		T->parent->parent = T;
	}
	else
		if (T->key < T->parent->key)
		{
			T->parent->left = T->right;
			if(T->right) T->right->parent = T->parent;

			T->right = T->parent;
			T->parent->parent = T;
		}
	T->parent = NULL;
	return T;

}
searchtree insert(searchtree *p, searchtree parent,int key)
{
	if (*p == NULL)
	{
		*p = (searchtree)malloc(sizeof(struct treenode));
		(*p)->key = key;
		(*p)->left = NULL;
		(*p)->right = NULL;
		(*p)->parent = parent;
	}
	else
	{
		if (key > (*p)->key)
		{
			insert(&((*p)->right),*p, key);
			
		}
		else
			if (key < (*p)->key)
			{
				insert(&((*p)->left), *p,key);
			}
			else
			{
				printf("can't insert the same value\n");
				exit(1);
			}
		
	}
	return *p;
}

searchtree create(int a[],int len)
{
	int i = 0;
	searchtree T = NULL;
	for (i = 0; i < len; i++)
	{
		insert(&T,NULL,a[i]);
	}
	return T;
}

searchtree splayfind(searchtree T,int key)
{
	searchtree tmp = NULL;
	tmp=find(T, key);
	if (tmp)
	{
		while (tmp->parent)
		{
			if (tmp->parent->parent)
			{
				if ((key < tmp->parent->key) && (tmp->parent->key < tmp->parent->parent->key))tmp = LLSingleRotate(tmp);
				else
					if (key<tmp->parent->key&&tmp->parent->key > tmp->parent->parent->key)tmp = RLDoubleRotate(tmp);
					else
						if ((key > tmp->parent->key) && (tmp->parent->key < tmp->parent->parent->key))tmp = LRDoubleRotate(tmp);
						else
							if ((key > tmp->parent->key) && (tmp->parent->key > tmp->parent->parent->key))tmp = RRSingleRotate(tmp);
			}
			else
			{
				tmp = SingleWithoutGrand(tmp);
			}
		}
	}
	return tmp;
}

searchtree Delete(searchtree T, int key)
{
	searchtree tmp = splayfind(T, key);
	searchtree leftmax = findmax(tmp->left);
	leftmax = splayfind(tmp->left, leftmax->key);
	leftmax->right = tmp->right;
	free(tmp);
	return leftmax;
}
int main()
{
	int a[] = { 15,13,27,8,10,18,20,23,35,19,21 };
//	int a[] = { 1,2,3,4};
	searchtree T = NULL;
	int len = sizeof(a) / sizeof(a[0]);
	T=create(a, len);
	preordertraverse(T);
	printf("\n");
	inordertraverse(T);
	printf("\n");
	lastordertraverse(T);
	printf("\n");
	printf("=======\n");
	T=splayfind(T, 15);
//	searchtree tmp = find(T, 2);
//	tmp = RRSingleRotate(tmp);
//	preordertraverse(tmp->parent);
//	tmp = SingleWithoutGrand(tmp);
	preordertraverse(T);
	printf("\n");
	T=Delete(T, 15);
	preordertraverse(T);


	return 0;
}

