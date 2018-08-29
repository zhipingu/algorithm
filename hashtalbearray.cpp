// hashtalbearray.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>

typedef struct hashtable *phashtable;
typedef struct hashentry *phashentry;

enum state{Legitimate,Empty};

struct hashentry
{
	int key;
	enum state info;
};

struct hashtable
{
	int tablesize;
	phashentry theentrys;
	
};

int hash(int key, int tablesize)
{
	return key%tablesize;
}

int F(int i,int key)
{
	//return i*i;
	return i*(7 - key % 7);
}

phashtable inithash(int tablesize)
{
	phashtable H;
	int i = 0;
	H = (phashtable)malloc(sizeof(hashtable));
	if (H == NULL)
	{
		printf("H allocate fail\n");
		exit(1);
	}
	H->tablesize = tablesize;
	H->theentrys = (phashentry)malloc(sizeof(hashentry)*tablesize);
	if (H->theentrys == NULL)
	{
		printf("H->theentry allocate fail\n");
		exit(1);
	}
	for (; i < tablesize; i++)
	{
		H->theentrys[i].info = Empty;
	}
	return H;
}

int find(phashtable H, int key)
{
	int index = hash(key, H->tablesize);
	int collisionnum = 0;
	//以下测试顺序不可交换，否则无法应对删除了key的情况。
	while (H->theentrys[index].info != Empty&&H->theentrys[index].key != key)
	{
		//平方探测法
		index += 2* ++collisionnum - 1;//乘2可以左移一位代替
		if (index >= H->tablesize)index -= H->tablesize;
		//相当于以下两行
		//collisionnum++;
		//index=(hash(key,H->tablesize)+collisionnum*collisionnum)%H->tablesize;
		
		//双散列
		//index = (hash(key, H->tablesize) + F(++collisionnum, key)) % H->tablesize;
	}
	return index;
}

void insert(phashtable H, int key)
{
	int index = find(H, key);
	if (H->theentrys[index].info == Empty)
	{
		H->theentrys[index].key = key;
		H->theentrys[index].info = Legitimate;
	}
}

phashtable rehash(phashtable H)
{
	phashtable newH = inithash(2 * H->tablesize);
	int i = 0;
	for (; i < H->tablesize; i++)
	{
		if (H->theentrys[i].info == Legitimate)insert(newH, H->theentrys[i].key);

	}
	free(H->theentrys);
	free(H);
	return newH;

}

void Delete(phashtable H, int key)
{
	int index = find(H, key);
	if (H->theentrys[index].info != Empty) H->theentrys[index].info = Empty;
}

void destroy(phashtable H)
{
	if (H)
	{
		free(H->theentrys);
		free(H);
	}
}
void print(phashtable H)
{
	int i = 0;
	for (; i < H->tablesize; i++)
	{
		if(H->theentrys[i].info==Legitimate)
		printf("%d:%d\n", i,H->theentrys[i].key);
	}
}


int main()
{
	int a[] = {4371,1323,6173,4199,4344,9679,1989 };
	int len = sizeof(a) / sizeof(a[0]);
	phashtable H = inithash(10);
	int i = 0;
	for (; i < len; i++)
	{
		insert(H, a[i]);
	}
	print(H);
	printf("======\n");
/*	Delete(H,89);
	print(H);
	printf("======\n");
	insert(H, 59);
	print(H);
	printf("======\n");
	//destroy(H);
	H = rehash(H);
	print(H);
	*/
    return 0;
}

