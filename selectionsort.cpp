// selectionsort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
void selectionsort(int a[], int len)
{
	int i, j;
	int minindex;
	//0-len-2都排好了，最后一个len-1不用排了
	for (i = 0; i < len - 1; i++)
	{
		minindex = i;
		for (j = i + 1; j < len; j++)
		{
			if (a[j] < a[minindex])
			{
				//此处不用min值，同时更新最小值，好好学习这一招
				minindex = j;
			}
		}
		if (minindex != i)
		{
			//当minindex!=i时，a[i]肯定不等于a[minindex],如果相等，minindex!=i了
			a[i] ^= a[minindex];
			a[minindex] ^= a[i];
			a[i] ^= a[minindex];
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
	int a[] = { 2,344,21,32,4,2,1,4,32,1,56,76,87 };
	int len = sizeof(a) / sizeof(a[0]);
	selectionsort(a, len);
	print(a, len);
    return 0;
}

