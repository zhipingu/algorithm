// backpack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>

#define Cap 10

int * backpack(int v[], int num,int cost[])
{
	int i;//��Ʒ���±꣬��i����Ʒ
	int j;//������ʣ�������С

	//c[i][j]����i����Ʒ���뵽���Ϊj�ı����е�����ֵ
	int *c = (int *)malloc(sizeof(int)*(num + 1)*(Cap + 1));
	if (!c)
	{
		perror("c malloc fail");
		exit(1);
	}
	memset(c, 0, sizeof(int)*(num + 1)*(Cap + 1));
	//�����ϵ�Ҫ�赽��һ�����
  	for(i=1;i<num+1;i++)
 		for (j = 1; j < Cap + 1; j++)
		{
			//ע��������Cap+1����Cap
			if (v[i] > j)c[i*(Cap+1) + j] = c[(i - 1)*(Cap+1) + j];//c[i][j]=c[i-1][j]
			else c[i*(Cap+1) + j] = c[(i - 1)*(Cap+1) + j] > cost[i] + c[(i - 1)*(Cap+1) + j - v[i]] ? c[(i - 1)*(Cap+1) + j] : cost[i] + c[(i - 1)*(Cap+1) + j - v[i]];
  		}
	return c;
}
int main()
{

 	int v[] = { 0,3,4,5 };//��1��ʼ
	int cost[] = { 0,4,5,6 };
	int *c = NULL;
	int i, j;
	int num = sizeof(v) / sizeof(v[0]) - 1;
	c=backpack(v, num, cost);
	
	for (i = 1; i < num + 1; i++)
	{
		for (j = 1; j < Cap+1; j++)
			printf("%d ", c[i*(Cap+1) + j]);
		printf("\n");
	}

    return 0;
}

