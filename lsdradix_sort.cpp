// lsdradix_sort.c.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>

void print(int a[], int len)
{
	int i = 0;
	for (; i < len; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

int getdigit(int key, int d)
{
	int a[] = { 1,10,100 };
	return key / a[d] % 10;
}

void lsdredix_sort(int a[], int len,int digit)
{
	int i = 0,j=0,d=0;
	int count[10] = { 0 };
	int *sort = (int *)malloc(sizeof(int)*len);
	for (i = 0; i < digit; i++)
	{
		for (j = 0; j < 10; j++)
		{
			count[j] = 0;
		}
		for (j = 0; j < len; j++)
		{
			d = getdigit(a[j], i);
			count[d]++;
		}
		for (j = 1; j < 10; j++)
		{
			count[j] += count[j - 1];
		}
		for (j = len - 1; j >= 0; j--)
		{
			d = getdigit(a[j], i);
			sort[--count[d]] = a[j];
			//“˝»Îsort[]∑¿÷πa[]±ª∏≤∏«
		}
		for (j = 0; j < len; j++)
		{
			a[j] = sort[j];
		}
	}
	free(sort);
}

int main()
{
	int a[] = { 12,32,10,22,12,3,7,2,22,45,88,43,564,33,454,322,889 };
	int len = sizeof(a) / sizeof(a[0]);
	lsdredix_sort(a, len, 3);
	printf("%d\n",len);
	print(a, len);
    return 0;
}

