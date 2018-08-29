// binomial queue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>

typedef struct treenode *ptreenode;
typedef struct binomialqueue *pbinqueue;
struct treenode
{
	int key;
	struct treenode *firstchild;
	struct treenode *nextsibling;
};

struct binomialqueue
{
	int currentsize;
	int capacity;
	ptreenode *thequeue;
};

pbinqueue initbinqueue(int capacity)
{
	pbinqueue B;
	int i = 0;
	B = (pbinqueue)malloc(sizeof(struct binomialqueue));
	if (!B)
	{
		perror("B allocate fail");
		exit(1);
	}
	B->currentsize = 0;
	B->capacity = capacity;
	B->thequeue = (ptreenode *)malloc(sizeof(ptreenode)*capacity);
	if (!B->thequeue)
	{
		perror("B->thequeue allocate fail");
		exit(1);
	}
	for (i = 0; i < capacity; i++)
	{
		B->thequeue[i] = NULL;
	}
	return B;
}
ptreenode combine(ptreenode T1, ptreenode T2)
{
	ptreenode tmp;
	if (!T1 || !T2)
	{
		perror("T1 or T2 NULL");
		exit(1);
	}
	if (T1->key > T2->key)
	{
		tmp = T1;
		T1 = T2;
		T2 = tmp;
	}
	T2->nextsibling = T1->firstchild;
	T1->firstchild = T2;
	return T1;
}

pbinqueue merge(pbinqueue B1, pbinqueue B2)
{
	ptreenode carry = NULL, T1 = NULL, T2 = NULL;//相当于进位
	int i = 0, j = 1;
	if (!B1)return B2;
	if (!B2)return B1;
	if (B1->currentsize + B2->currentsize > B1->capacity)
	{
		perror("merge would exceed B1 capacity");
		exit(1);
	}
	B1->currentsize += B2->currentsize;
	for (i = 0, j = 1; j <= B1->currentsize; j *= 2, i++)
	{
		T1 = B1->thequeue[i];
		T2 = B2->thequeue[i];
		switch (!!T1*4 + !!T2 * 2 + !!carry)
		{
			case 0:break;
			case 1:
			{
				B1->thequeue[i] = carry;
				carry = NULL;
				break;
			}
			case 2:
			{
				B1->thequeue[i] = T2;
				B2->thequeue[i] = NULL;
				break;
			}
			case 3:
			{
				carry = combine(T2, carry);
				B2->thequeue[i] = NULL;
				break;
			}
			case 4:break;
			case 5:
			{
				carry = combine(T1, carry);
				B1->thequeue[i] = NULL;
				break;
			}
			case 6:
			{
				carry = combine(T1, T2);
				B1->thequeue[i] = NULL;
				B2->thequeue[i] = NULL;
				break;
			}
			case 7:
			{
				B1->thequeue[i] = carry;
				carry = combine(T1, T2);
				B2->thequeue[i] = NULL;
				break;
			}
		}

	}

	return B1;
}

pbinqueue insert(pbinqueue B, int key)
{
	int i = 0;
	pbinqueue tmp = (pbinqueue)malloc(sizeof(struct binomialqueue));
	if (!tmp)
	{
		perror("tmp allocate fail");
		exit(1);
	}
	tmp->capacity = 1;
	tmp->currentsize = 0;
	tmp->thequeue = (ptreenode *)malloc(sizeof(ptreenode)*10);
	if (!tmp->thequeue)
	{
		perror("tmp->thequeue allocate fail");
		exit(1);
	}
	for (i = 0; i < 10; i++)
	{
		tmp->thequeue[i] = NULL;
	}
	tmp->thequeue[0] = (ptreenode)malloc(sizeof(struct treenode));
	tmp->thequeue[0]->key = key;
	tmp->thequeue[0]->firstchild = tmp->thequeue[0]->nextsibling = NULL;
	tmp->currentsize = 1;
	B=merge(B, tmp);
	free(tmp->thequeue);
	free(tmp);
	return B;
}

int Deletemin(pbinqueue B)
{
	int i = 0;
	int minindex = 0,min=0;
	pbinqueue newbinqueue = NULL;
	if (!B)return NULL;
	ptreenode Tmin = (ptreenode)malloc(sizeof(treenode));
	ptreenode tmp;
	Tmin->key = 10000;
	for (i = 0; i <=B->currentsize; i++)
	{
		if (B->thequeue[i]&&B->thequeue[i]->key < Tmin->key)
		{
			Tmin = B->thequeue[i];
			minindex = i;
		}
	}
	B->thequeue[minindex] = NULL;
	min = Tmin->key;
	tmp = Tmin->firstchild;
	free(Tmin);
	newbinqueue = initbinqueue(20);
	for (i = minindex - 1; i >= 0; i--)
	{
		newbinqueue->thequeue[i] = tmp;
		tmp = tmp->nextsibling;
		newbinqueue->thequeue[i]->nextsibling = NULL;
	}
	merge(B, newbinqueue);
	return min;

}
void printtree(ptreenode T)
{
	if (!T)return;
	printf("%d ", T->key);
	printtree(T->firstchild);
	printtree(T->nextsibling);
}
void printbinqueue(pbinqueue B)
{
	int i = 0;
	for (i = 0; i < B->currentsize; i++)
	{
		printf("%d: ",i);
		printtree(B->thequeue[i]);
		printf("\n");
	}
	printf("====\n");
}
int main()
{
	int a[] = { 2,32,31,12,24,42,45 };
	//int a[] = { 5 };
	int b[] = { 11,3,5,65,34,22,34,56,30 };
	int lena = sizeof(a) / sizeof(a[0]);
	int lenb = sizeof(b) / sizeof(b[0]);
	pbinqueue Ba = initbinqueue(20);
	pbinqueue Bb = initbinqueue(20);
	int i = 0;
	for (i = 0; i < lena; i++)
	{
		insert(Ba, a[i]);
	}

	for (i = 0; i < lenb; i++)
	{
		insert(Bb, b[i]);
	}
	//printf("%d \n", B->thequeue[0]->key);
	printbinqueue(Ba);
	//printbinqueue(Bb);
	//merge(Ba, Bb);
	//printbinqueue(Ba);
	printf("%d-------\n",Deletemin(Ba));
//	Deletemin(Ba);
	printbinqueue(Ba);
	printf("%d-------\n", Deletemin(Ba));
//	Deletemin(Ba);
	printbinqueue(Ba);

    return 0;
}

