// searchtree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

typedef struct treenode * position;
typedef struct treenode * searchtree;

struct treenode {
	int key;
	searchtree left;
	searchtree right;
};

searchtree insert(searchtree *p, int key)
{
	if (*p == NULL)
	{
		*p = (searchtree)malloc(sizeof(struct treenode));
		(*p)->key = key;
		(*p)->left = NULL;
		(*p)->right = NULL;
	}
	else 
		if (key > (*p)->key) insert(&((*p)->right), key);
		else 
			if (key < (*p)->key) insert(&((*p)->left), key);
			else
			{
				printf("can't insert the same value\n");
				exit(1);
			}
	return *p;
}

searchtree create(int a[],int len)
{
	int i = 0;
	searchtree T=NULL;
	for (i = 0; i < len; i++)
	{
		insert(&T, a[i]);
	}
	return T;
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

void printlevel(searchtree T, int level)
{
	if (T == NULL) return;
	if (level == 1) printf("%d ", T->key);
	else
	{
		printlevel(T->left, level - 1);
		printlevel(T->right, level - 1);
	}
}

void LevelTraverseR(searchtree T, int level)
{
	int i = 1;
	if (T == NULL)return ;
	for (; i <= level; i++)
	{
		printlevel(T, i);
		printf("\n");
	}
}

struct queue
{
	searchtree T;
	struct queue *next;
};

static struct queue *front, *rear;

int is_empty()
{
	return front== NULL;
}
void enqueue(searchtree T)
{
	struct queue *tmp = (struct queue *)malloc(sizeof(struct queue));
	tmp->T = T;
	tmp->next = NULL;
	rear->next = tmp;
	rear = tmp;
}

struct queue *dequeue()
{
	struct queue *tmp = front;
	front = front->next;
	free(tmp);
	return front;
}

void LevelTraverseQ(searchtree T)
{
	struct queue *head = (struct queue *)malloc(sizeof(struct queue));
	head->T = T;
	head->next = NULL;
	front = rear = head;
	//����Ϊ��������ͷhead
	struct queue *tmp=front;

	do
	{
			printf("%d\n", tmp->T->key);
			if (tmp->T->left)
				enqueue(tmp->T->left);
			if (tmp->T->right)
				enqueue(tmp->T->right);
			//ȡ������Ԫ��,�����������󣬷�ֹ����ȡ��Ԫ��Ϊ��
			tmp = dequeue();
 	}while (!is_empty());
//	printf("%d ======\n", tmp->T->key);
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
	searchtree tmp=T;
	if(T!=NULL)
		while (tmp->left)
			tmp = tmp->left;
	return tmp;
}

position findmax(searchtree T)
{
	if (T)
		while (T->right)
			T = T->right;
	//�ı�T��û��ϵ����ΪT�Ǹ��Ƶ�
	return T;
}

searchtree Delete(searchtree T, int key)
{
	position tmp;
	if (T)
	{
		if (key > T->key)T->right= Delete(T->right, key);
		//Delete()�ķ���ֵһ��Ҫ����T->right����ȻT->rightɾ���ڵ����ܱ��ָ��Ƿ���ַ
		else
			if (key < T->key) T->left=Delete(T->left, key);
			else
				if (T->left&&T->right)
				{
					tmp = findmax(T->left);
					T->key = tmp->key;
					T->left = Delete(T->left, T->key);
					//��ʱT->keyΪ��������Сֵ
				}
				else
					if (T->right == NULL)
						//�����if(T->left)��if(T->right)���ܴ����޺��ӵ����
						//�����ټ�һ��if(!T->left&&!T->right)
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
	}
	else printf("not found\n");
	return T;
}

void nodecount(searchtree T, int *pleafnum, int *pnodenum, int *pfullnum)
{
	if (T == NULL)return;
	else
	{
		(*pnodenum)++;
		if (T->left&&T->right) (*pfullnum)++;
		else
			if (T->left == NULL&&T->right == NULL) (*pleafnum)++;
		nodecount(T->left,pleafnum,pnodenum,pfullnum);
		nodecount(T->right,pleafnum,pnodenum,pfullnum);
	}
}

int main()
{
	int a[] = {12,10,13,8,6,15,24,9,14};
	int len = sizeof(a) / sizeof(a[0]);
	searchtree T=create(a, len);
	int nodenum = 0, leafnum = 0, fullnum = 0;
/*
	preodertraverse(T);
	printf("\n");
	inordertraverse(T);
	printf("\n");
	lastordertraverse(T);
	printf("\n");
*/	//Delete(T, 3);
	//inordertraverse(T);
	printf("\n");
	LevelTraverseQ(T);

	nodecount(T, &leafnum, &nodenum, &fullnum);
	printf("==========\n");
	printf("%d\n", leafnum);
	printf("%d\n", nodenum);
	printf("%d\n", fullnum);




		
    return 0;
}

