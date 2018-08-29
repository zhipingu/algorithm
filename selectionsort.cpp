// selectionsort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
void selectionsort(int a[], int len)
{
	int i, j;
	int minindex;
	//0-len-2���ź��ˣ����һ��len-1��������
	for (i = 0; i < len - 1; i++)
	{
		minindex = i;
		for (j = i + 1; j < len; j++)
		{
			if (a[j] < a[minindex])
			{
				//�˴�����minֵ��ͬʱ������Сֵ���ú�ѧϰ��һ��
				minindex = j;
			}
		}
		if (minindex != i)
		{
			//��minindex!=iʱ��a[i]�϶�������a[minindex],�����ȣ�minindex!=i��
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

