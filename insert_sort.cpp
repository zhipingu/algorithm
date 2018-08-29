// insert_sort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
void insert_sort(int a[],int len)
{
	int i, j, tmp;
	for (j = 1; j < len; j++)
	{
		tmp = a[j];
		i = j - 1;
		while (i >= 0 && tmp < a[i])
		{
			a[i + 1] = a[i];
			i--;
		}
		a[i+1] = tmp;
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
	int a[] = { 4,3,1,8,5,19,21,34,3,4 };
	int len = sizeof(a) / sizeof(a[0]);
	insert_sort(a, len);
	print(a, len);
    return 0;
}

