// hashtable.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>

typedef struct listnode *plist;
typedef struct listnode list;
typedef struct hashtable *phashtable;
struct listnode
{
	int key;
	struct listnode *next;
};
struct hashtable
{
	int tablesize;
	plist *thelists;
};

phashtable inithash(int tablesize)
{
	phashtable H;
	plist L;
	int i = 0;
	H = (phashtable)malloc(sizeof(hashtable));
	if (!H)printf("phashtable error\n");
	H->tablesize = tablesize;
	H->thelists = (plist*)malloc(sizeof(plist)*tablesize);
	if (!H->thelists)printf("H->thelists error\n");
	L = (plist)malloc(sizeof(listnode)*tablesize);
	if (!L)printf("L error\n");
	for (i = 0; i < tablesize; i++)
	{
		H->thelists[i] = &L[i];
		H->thelists[i]->next = NULL;
	}
	return H;

}

int hash(int key,int tablesize)
{
	return key%tablesize;
}

void insert(int key, phashtable H)
{
	plist pnewnode;
	int index = hash(key, H->tablesize);
	plist tmp = H->thelists[index]->next;
	while (tmp != NULL)
	{
		if (tmp->key == key)
		{
			printf("%d exist!\n", key);
			break;
		}
		else tmp = tmp->next;
	}
	if (!tmp)
	{
		pnewnode = (plist)malloc(sizeof(list));
		pnewnode->key = key;
		pnewnode->next = H->thelists[index]->next;
		H->thelists[index]->next = pnewnode;
	}

}

void Delete(int key, phashtable H)
{
	int index = hash(key, H->tablesize);
	plist L = H->thelists[index];
	plist tmp;
	while (L->next&&L->next->key!=key) L = L->next;
	if (L->next)
	{
		tmp = L->next;
		L->next = L->next->next;
		free(tmp);
	}
}

plist find(int key, phashtable H)
{
	int index = hash(key, H->tablesize);
	plist tmp = H->thelists[index]->next;
	while (tmp)
	{
		if (tmp->key == key)return tmp;
		tmp = tmp->next;
	}
	return tmp;
}

void destroy(phashtable H)
{
	plist L = NULL, tmp = NULL;
	int i = 0;
	for (; i < H->tablesize; i++)
	{
		L = H->thelists[i]->next;
		while (L)
		{
			tmp = L->next;
			free(L);
			L = tmp;
		}
	}
	free(H->thelists[0]);
	free(H->thelists);
	free(H);
}

void print(phashtable H)
{
	plist L;
	int i = 0;
	for (; i < H->tablesize; i++)
	{
		L = H->thelists[i]->next;
		while (L)
		{
			printf("%d ", L->key);
			L = L->next;
		}
		printf("\n");
	}
}
int main(void)
{
	int a[] = { 23,32,1,2,43,22,14,52,36,87,67,59,43,24,20};
	int tablesize = 10;
	plist tmp = NULL;
	int len = sizeof(a) / sizeof(a[0]);
	int i = 0;
	phashtable H;
	H=inithash(tablesize);
	for (; i < len; i++)
	{
		insert(a[i], H);
	}
	print(H);
	printf("=======\n");
	Delete(14, H);
	print(H);
	printf("=======\n");
	tmp = find(67, H);
	Delete(tmp->key, H);
	print(H);

	destroy(H);

	return 0;
}