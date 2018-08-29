// merge_sort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>

void merge(int a[], int tmparr[], int lpos, int rpos, int rend)
{
	int lend = rpos - 1;
	int j = lpos;
	int i = lpos;
	while (lpos <= lend&&rpos <= rend)
	{
		if (a[lpos] < a[rpos])tmparr[i++] = a[lpos++];
		else tmparr[i++] = a[rpos++];
	}

	while (lpos <= lend) tmparr[i++] = a[lpos++];

	while (rpos <= rend) tmparr[i++] = a[rpos++];
	for (; j < i; j++)
		a[j] = tmparr[j];

}

void Msort(int a[], int tmparr[], int left, int right)
{
	int center;
	if (left < right)
	{
		center = (left + right) / 2;
		Msort(a, tmparr, left, center);
		Msort(a, tmparr, center + 1, right);
		merge(a, tmparr, left, center + 1, right);
	}
}

void merge_sort(int a[], int len)
{
	int *tmparr = (int *)malloc(sizeof(int)*len);
	if (!tmparr)
	{
		perror("tmparr malloc fail");
		exit(1);
	}
	Msort(a, tmparr, 0, len - 1);
	free(tmparr);

}

void print(int a[], int len)
{
	int i = 0;
	for (; i < len; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}
int main()
{
	int a[] = { 3,4,2,43,2,12,32,4,24,34,56,43,89,76,67,23,11,90 };
	int len = sizeof(a) / sizeof(a[0]);
	merge_sort(a, len);
	print(a, len);
    return 0;
}

