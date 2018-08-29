// bubble_sort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void bubble_sort(int a[], int len)
{
	int i, j ;
	//�Ѿ�����len-1���ˣ����һ�����ó��ˣ�i���ɳ��˼������ֵ
	for(i=0;i<len-1;i++)
		//��Ϊa[j+1],����j<len-1���ܵ���
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

