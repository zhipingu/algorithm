// shellsort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void shell_sort(int a[], int len,int increment)
{
	int i, j, tmp;
	for (; increment> 0; increment /= 2)
		for(i=increment;i<len;i++)
		{
			j = i;
			tmp = a[i];
			while (j >=increment&&tmp < a[j - increment])
			{
				a[j] = a[j-increment];
				j -= increment;
			}
			a[j] = tmp;
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
	int a[] = { 5,3,12,32,22,45,11,22,18,7,4 };
	int len = sizeof(a) / sizeof(a[0]);
	shell_sort(a, len, 4);
	print(a, len);
    return 0;
}

