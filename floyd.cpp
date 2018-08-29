// floyd.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>

#define Vertexnum 5
#define INF 100000

typedef struct outarg * poutarg;

struct outarg
{
	int D[Vertexnum][Vertexnum];
	int path[Vertexnum][Vertexnum];
};

void floyd(int A[Vertexnum][Vertexnum], poutarg po)
{
	int i, j, k;
	int tmp;
	for(i=0;i<Vertexnum;i++)
		for (j = 0; j < Vertexnum; j++)
		{
			po->D[i][j] = A[i][j];
			po->path[i][j] = -1;
		}

	for(k=0;k<Vertexnum;k++)//对于每个点作为中间点
		for(i=0;i<Vertexnum;i++)//对于每一对点
			for (j = 0; j < Vertexnum; j++)
			{
				tmp = po->D[i][k] + po->D[k][j];
				if (tmp < po->D[i][j])
				{
					po->D[i][j] = tmp;
					po->path[i][j] = k;
				}
			}
}
//递归打印
void print(int path[Vertexnum][Vertexnum], int i, int j)
{
	int tmp;
//	printf("v%d->", i);
	tmp = path[i][j];
	
	if (tmp < 0)return;
	else printf("%d\n", tmp);
	print(path, i, tmp);
	print(path, tmp, j);
	printf("\n");
	
}

int main()
{
	struct outarg og;
	int i, j;
	int A[Vertexnum][Vertexnum] = { {0,3,8,INF,-4},
	{INF,0,INF,1,7},{INF,4,0,INF,INF},{2,INF,-5,0,INF},
	{INF,INF,INF,6,0} };
	floyd(A, &og);
	for (i = 0; i < Vertexnum; i++)
	{
		for (j = 0; j < Vertexnum; j++)
		{
			printf("%d ", og.D[i][j]);
		}
		printf("\n");
	}

	print(og.path, 0, 3);

    return 0;
}

