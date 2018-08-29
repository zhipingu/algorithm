// quicksort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void insert_sort(int a[], int len)
{
	int i = 0;
	int j;
	int tmp;
	for (i= 1; i < len; i++)
	{
		j = i;
		tmp = a[j];
		while (j > 0 && tmp < a[j-1])
		{
			a[j] = a[j-1];
			j--;
		}
		a[j] = tmp;
	}

}

int median3(int a[], int left, int right)
{
	int center = (left + right) / 2;
	if (a[left] > a[center])
	{
		a[left] ^= a[center];
		a[center] ^= a[left];
		a[left] ^= a[center];
	}
	if (a[left] > a[right])
	{
		a[left] ^= a[right];
		a[right] ^= a[left];
		a[left] ^= a[right];
	}
	if (a[center] > a[right])
	{
		a[center] ^= a[right];
		a[right] ^= a[center];
		a[center] ^= a[right];
	}
	a[right - 1] ^= a[center];
	a[center] ^= a[right - 1];
	a[right - 1] ^= a[center];

	return a[right - 1];
}

void Qsort(int a[], int left, int right)
{
	int i, j, pivot;
	if (left + 3 <= right)
	{
		pivot = median3(a, left, right);
		i = left;
		j = right - 1;
		while (1)
		{
			while (a[++i] < pivot);
			while (a[--j] > pivot);
			if (i < j)
			{
				a[i] ^= a[j];
				a[j] ^= a[i];
				a[i] ^= a[j];
			}
			else break;
		}
		a[i] ^= a[right - 1];
		a[right - 1] ^= a[i];
		a[i] ^= a[right - 1];

		Qsort(a, left, j);
		Qsort(a, i + 1, right);
	}
	else insert_sort(a+left, right-left+1);
}

void quick_sort(int a[], int len)
{
	Qsort(a, 0, len - 1);
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
	int a[] = { 32,11,45,32,34,87,1,4,2,5,7,293,40,11,45,87,344,23,66,0 };
	int len = sizeof(a) / sizeof(a[0]);
	quick_sort(a, len);
	print(a, len);
    return 0;
}

