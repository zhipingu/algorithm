// bubble_sort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void bubble_sort(int a[], int len)
{
	int i, j ;
	//已经沉了len-1个了，最后一个不用沉了，i看成沉了几个最大值
	for(i=0;i<len-1;i++)
		//因为a[j+1],所以j<len-1不能等于
		for(j=0;j<len-1-i;j++)
			if (a[j] > a[j+1])
			{
				a[j] ^= a[j+1];
				a[j+1] ^= a[j];
				a[j] ^= a[j+1];
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
	int a[] = { 2,1,4,9,5,6,8,9,2,12,32,1,0,78,89,78};
	int len = sizeof(a) / sizeof(a[0]);
	bubble_sort(a, len);
	print(a, len);
    return 0;
}

