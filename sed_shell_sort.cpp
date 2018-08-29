// sed_shell_sort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
void sed_shell_sort(int a[], int len)
{
	int sed[] = { 1,3,7 };
	int i = 2, j, k;
	int increment;
	int tmp;
	for (; i >= 0; i--)
	{
		increment = sed[i];
		for (j = increment; j < len; j++)
		{
			k = j;
			tmp = a[j];
			while (k >= increment&&tmp < a[k - increment])
			{
				a[k] = a[k - increment];
				k -= increment;
			}
			a[k] = tmp;
		}
	}
}

void print(int a[], int len)
{
	int i;
	for (i = 0; i < len; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}
int main()
{
	int a[] = { 9,8,7,6,5,4,3,2,1 ,89,34,22,13,656,32,3,5,1,7,2,89};
	int len = sizeof(a) / sizeof(a[0]);
	sed_shell_sort(a, len);
	print(a, len);
    return 0;
}

