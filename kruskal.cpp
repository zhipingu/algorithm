// kruskal.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>

#define Vertexnum 7
#define Edgenum 42  //�����7*6���ߣ�������϶���A7,2����C7,2
typedef struct edge *pedge;
typedef int disjset[Vertexnum+1];//���±�1��ʼ���
typedef struct graph *pgraph;

template<typename vertex>
struct edge
{
	vertex start;
	vertex end;
	int weight;
	//int selected;//��Ϊ���ѡ�����ı�־
};

struct graph
{
	int vertexnum;
	int edgenum;
	int cost[Vertexnum+1][Vertexnum+1];
};

void initgraph(pgraph pg)
{
	int start = 0, end = 0,cost=0;
	char str[50];
	FILE *fp = fopen("graph.txt", "r");
	int sum = 0;
	memset(pg, 0, sizeof(struct graph));
	pg->vertexnum = Vertexnum;
	pg->edgenum = Edgenum;
	//printf("please input (start,end,cost),input(-1,-1,-1) end\n");
	while (fgets(str, 50, fp))
	{
		//sscanf��fgets��ϣ���ǿ��
		sscanf(str,"%d %d %d", &start, &end, &cost);
		if (start == -1)break;
		pg->cost[start][end] = cost;
	}
	
}

void percolatedown(pedge a[], int size, int i)
{
	int child = 2 * i + 1;
	pedge tmp = a[i];
	for (; child <= size-1; i = child, child = 2 * i + 1)
	{
		if (child != size-1&&a[child]->weight > a[child + 1]->weight)
			child++;
		if (tmp->weight > a[child]->weight)a[i] = a[child];
		else break;
	}
	a[i] = tmp;
}

void buildheap(pedge a[], int size)
{
	int i = 0;
	for (i = (size-1)/ 2; i >= 0; i--)
	{
		percolatedown(a, size, i);
	}
}
pedge deletemin(pedge a[], int size)
{
	pedge min = a[0];
	a[0] = a[size - 1];
	percolatedown(a, size - 1, 0);
	return min;
}
//�������ô󶥶ѷ���һЩ
void heap_sort(pedge a[], int size)
{
	int i = 0;
	pedge tmp = NULL;
	buildheap(a, size);
	for (i=size-1;i>0;i--)
	{
		//if (a[0] != a[i])
		//���ʱ��Ҳ���ԣ���˵��ʼa[0]���0�������a=b=ԭֵ
		//����������������������ֵ
		{
			/*
			a[0] ^= a[i];
			a[i] ^= a[0];
			a[0] ^= a[i];
			*/
			tmp = a[0];
			a[0] = a[i];
			a[i] = tmp;
			percolatedown(a, i - 1, 0);
		}
	}

}
//·��ѹ������ڵ�
int find(int i, disjset s)
{
	if (s[i] <= 0)return i;
	return s[i]=find(s[i], s);
}
//����С��
void setunion(int i, int j, disjset s)
{
	int root1 = find(i,s);
	int root2 = find(j,s);
	if (s[root1] < s[root2])
	{
		s[root1] += s[root2];
		s[root2] = root1;
	}
	else
	{
		s[root2] += s[root1];
		s[root1] = root2;
	}
}

void initdisjset(disjset s)
{
	int i = 0;
	for (i = 1; i <= Vertexnum; i++)
	{
		s[i] = -1;//��ʼ��СΪ1
	}
}

int kruskal(pgraph pg, pedge minedge[],int *edgesize)
{
	int i = 0, j = 0,k=0;
	int sum = 0;
	int acceptededge = 0;
	pedge edge[Vertexnum*(Vertexnum-1)];
	//int start, end;
	pedge pe = NULL,min=NULL;
	disjset s;
	initdisjset(s);
	//װ��edge[]
	for(i=1;i<=pg->vertexnum;i++)
		for (j = 1; j <=pg->vertexnum; j++)
		{
			if (pg->cost[i][j] > 0)
			{
				pe = (pedge)malloc(sizeof(struct edge));
				if (!pe)
				{
					perror("pe malloc fail");
					exit(1);
				}
				pe->start = i;
				pe->end = j;
				pe->weight = pg->cost[i][j];
				//pe->selected = 0;
				edge[k++] = pe;
			}
		}
	//�浽k-1������Ϊk
	*edgesize = k;
	buildheap(edge, k);
	i = 0;
	while (acceptededge < Vertexnum - 1)
	{
		min = deletemin(edge, k--);
		if (find(min->start,s) != find(min->end,s))
		{
			acceptededge++;
			minedge[i++] = min;
			sum += min->weight;
			setunion(min->start, min->end, s);
		}
	}
/*	heap_sort(edge, k);

	for (i = 0; i < k; i++)
	{
		//start = edge[i]->start;
		//end = edge[i]->end;
		if (find(edge[i]->start, s) != find(edge[i]->end, s))
		{
			edge[i]->selected = 1;
			setunion(edge[i]->start, edge[i]->end, s);
			sum += edge[i]->weight;
		}
	}
*/
	return sum;
}

void print(pedge minedge[],int edgesize)
{
	int i = 0;
	for (i = 0; i < edgesize; i++)
	{
			printf("edge:(%d,%d),cost:%d\n", minedge[i]->start, minedge[i]->end, minedge[i]->weight);
	}
}
int main()
{
	struct graph G;
	int costsum = 0;
	int edgesize = 0;
	pedge minedge[Vertexnum-1];
	initgraph(&G);
	costsum=kruskal(&G,minedge,&edgesize);
	printf("costsum:%d\n", costsum);
	print(minedge,Vertexnum-1);
    return 0;
}

