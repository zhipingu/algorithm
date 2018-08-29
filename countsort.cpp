// countsort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>
#include<string.h>

void countsort(int a[], int len)
{
	int *count;
	int *sort;
	int i = 0;
	int max = 0;

	for (i = 0; i < len; i++)
	{
		if (a[i] > max) max = a[i];
	}
	//max+1��Ϊ�˱���34�������±�Ϊ0-33��Ϊ�˰���34������+1
	count=(int *)malloc(sizeof(int)*(max+1));
	memset(count, 0, sizeof(int)*(max + 1));
	sort = (int *)malloc(sizeof(int)*len);
	memset(sort, 0, sizeof(int)*len);
	
	for (i = 0; i < len; i++)
		count[a[i]]++;
 	for (i = 1; i < max + 1; i++)
		count[i] += count[i - 1];
	
	for (i = 0; i < len; i++)
	{
		count[a[i]]--;
		sort[count[a[i]]] = a[i];
	}
	printf("=========\n");
	for (i=0; i < len; i++)
	{
		printf("%d\n", sort[i]);
	}
	free(count);
	free(sort);
}

int main()
{
	int a[] = { 34, 22, 23, 4, 8, 13, 14, 13, 21, 45 };
	int len = sizeof(a) / sizeof(a[0]);
	countsort(a, len);
	
    return 0;
}

