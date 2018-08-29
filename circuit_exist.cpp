// circuit_exist.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>

#define Vertexnum 8

typedef struct graph *pgraph;

struct graph
{
	int vertexnum;
	int edgenum;
	int weight[Vertexnum][Vertexnum];
	int visited[Vertexnum];
	int pre[Vertexnum];
};

void dfs(pgraph pg,int vertex,int *visitededge)
{
	int i = 0,j=0;
	int tmp;
	pg->visited[vertex] = 1;
	for(i=0;i<Vertexnum;i++)
	{
		if (pg->weight[vertex][i] > 0)
		{
			//pg->weight[vertex][i] = 0;
			(*visitededge)++;
			if (!pg->visited[i])
			{
				pg->pre[i] = vertex;
				dfs(pg, i,visitededge);
			}
			//注意else if与if的区别
			else if (pg->visited[i] == 1)
			{
				tmp = vertex;
				printf("it has a circuit\n");
				printf("%d,%d,", i, vertex);
				while (pg->pre[tmp] != i)
				{
					printf("%d,", pg->pre[tmp]);
					tmp = pg->pre[tmp];
				}
				printf("%d\n", pg->pre[tmp]);	
			}
			
		}
	}
	pg->visited[vertex] = 2;
}

void initgraph(pgraph pg)
{
	FILE *fp = fopen("graph.txt","r");
	char *tmp = NULL;
	int from, to;
	char line[1000];
	pg->vertexnum = Vertexnum;
	pg->edgenum = 0;
	memset(pg->pre, -1, sizeof(pg->pre));
	memset(pg->visited, 0, sizeof(pg->visited));
	memset(pg->weight, 0, sizeof(pg->weight));
	while (fgets(line, sizeof(line), fp))
	{
		tmp = line;
		while (*tmp != '\n'&&*tmp != '\0')
		{
			while (*tmp == ' ')tmp++;
			sscanf(tmp, "%d,%d", &from, &to);
			pg->weight[from][to] = 1;
			pg->edgenum++;
			while (*tmp != ' '&&*tmp!='\0')tmp++;
		}
	}

}

int main()
{
	struct graph g;
	int start = 0, visitededge = 0;
	int i, j, flag = 0;;
	initgraph(&g);
	while (visitededge != g.edgenum)
	{
		for (i = 0; i < Vertexnum; i++)
		{
			for (j = 0; j < Vertexnum; j++)
				if (g.weight[i][j] > 0)
				{
					start = i;
					flag = 1;
					break;
				}
			if (flag == 1)
			{
				flag = 0;
				break;
			}
		}

		dfs(&g, start, &visitededge);
	}
    return 0;
}

