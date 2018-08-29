// heapsort.c.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
void PercolateDown(int a[], int pos, int len)
{
	int i=pos, tmp=a[pos];
	int child =pos;
	for (; 2*i+1 < len; i = child)
	{
		child = 2 * child + 1;
		if (child != len - 1 && a[child] < a[child + 1])
			child++;
		if (tmp < a[child])
		{
			a[i] = a[child];
		}
		else break;
	}
	a[i] = tmp;
}

void buildheap(int a[], int len)
{
	int i = len/2;
	for (; i >= 0; i--)
	{
		PercolateDown(a, i, len);
	}
}

void heapsort(int a[], int len)
{
	int i = len-1;
	buildheap(a, len);
	for (; i > 0; i--)
	{
		if (a[0] != a[i])
		{
			a[0] ^= a[i];
			a[i] ^= a[0];
			a[0] ^= a[i];
		}
		PercolateDown(a, 0, i);
	}
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
	int a[] = { 34,22,11,33,2,4,6,8,3,2,1,5,3,2,93,11,22 };
	int len = sizeof(a) / sizeof(a[0]);
	heapsort(a, len);
	print(a,len);
    return 0;
}

