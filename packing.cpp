// packing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>

#define Goodnum 10
#define Volume 20

typedef struct good *pgood;
typedef struct box *pbox;

struct good
{
	int num;
	double v;
	pgood next;
};

struct box
{
	pgood first;//ָ���һ����Ʒ
	double remain;//ʣ��ռ�
	pbox next;
};

struct good_in_box
{
	int num;
	double v;
	struct good_in_box *next;
};
//�Ӵ�С��
void insert_sort(pgood a[], int len)
{
	int i = 0, j = 0;
	pgood tmp;
	for (i = 0; i < len - 1; i++)
	{
		j = i;
		tmp = a[j + 1];
		while (j >= 0 && tmp->v > a[j]->v)
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = tmp;
	}
}

pbox packing(pgood pg[])
{
	pbox pb, tmp;
	pgood tmpgood;
	int i = 0;
	pb = (pbox)malloc(sizeof(struct box));//��һ������
	if (!pb)
	{
		perror("pb malloc fail");
		exit(1);
	}
	pb->first = NULL;
	pb->next = NULL;
	pb->remain = Volume;
	insert_sort(pg, Goodnum);
	for (i = 0; i < Goodnum; i++)
	{
		tmp = pb;
		while (pg[i]->v > tmp->remain)
		{
			if (tmp->next)tmp = tmp->next;
			else break;
		}
		if (pg[i]->v > tmp->remain)
		{
			tmp->next = (pbox)malloc(sizeof(struct box));
			if (!tmp->next)
			{
				perror("new box malloc fail");
				exit(1);
			}
			tmp->next->first = pg[i];
			tmp->next->next = NULL;
			tmp->next->remain = Volume - pg[i]->v;
			pg[i]->next = NULL;
		}
		else
		{
			tmp->remain -= pg[i]->v;
			tmpgood = tmp->first;
			while (tmpgood)
			{
				if(tmpgood->next)
				tmpgood = tmpgood->next;
				else break;
			}
			if (!tmpgood)pb->first = pg[i];//��һ�����ӷ����һ����Ʒ
			else  tmpgood->next = pg[i];
		}
	}
	return pb;
}

void print(pbox pb)
{
	pbox tmpb;
	pgood tmpg;
	tmpb = pb;
	int i = 0;
	while (tmpb)
	{
		tmpg = tmpb->first;
		printf("���ӱ�ţ�%d", i++);
		while (tmpg)
		{
			printf("(��ţ�%d,�����%lf)", tmpg->num, tmpg->v);
			tmpg = tmpg->next;
		}
		printf("\n");
		tmpb = tmpb->next;
	}
}
int main()
{
	pgood pg[Goodnum];
	pbox pb;
	int i = 0;
	for (i = 0; i < Goodnum; i++)
	{
		pg[i] = (pgood)malloc(sizeof(struct good));
		pg[i]->next = NULL;
		pg[i]->num = i;
		scanf("%lf", &(pg[i]->v));
	}
	insert_sort(pg, sizeof(pg) / sizeof(pg[0]));
	pb =packing(pg);
	print(pb);
    return 0;
}

