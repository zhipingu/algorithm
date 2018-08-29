// strong_branch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>

#define Vertexnum 10

typedef struct stack *pstack;
typedef struct graph *pgraph;

struct stack
{
	int top;
	int capacity;
	int *array;
};

struct graph
{
	int vertexnum;
	int edgenum;
	int visited[Vertexnum];
	int (*weight)[Vertexnum];
	int (*reweight)[Vertexnum];//重要Gr用来DFS2
};
pstack initstack(int capacity)
{
	pstack ps = NULL;
	ps = (pstack)malloc(sizeof(struct stack));
	if (!ps)
	{
		perror("ps malloc fail");
		exit(1);
	}
	ps->top = 0;
	ps->capacity = capacity;
	ps->array = (int *)malloc(sizeof(int)*capacity);
	if (!ps->array)
	{
		perror("ps->array malloc fail");
		exit(1);
	}
	return ps;
}

int is_empty(pstack ps)
{
	return ps->top == 0;
}

int is_full(pstack ps)
{
	return (ps->top == ps->capacity);
}

void push(pstack ps, int key)
{
	if (is_full(ps))
	{
		printf("ps is full\n");
		return;
	}
	ps->array[(ps->top)++] = key;
}

int pop(pstack ps)
{
	if (is_empty(ps))
	{
		printf("ps is empty\n");
		return -1;
	}
	return ps->array[--ps->top];
}

pgraph initgraph()
{
	FILE *fp = fopen("graph.txt", "r");
	char line[1000];
	char *tmp = NULL;
	int from = 0, to = 0;
	pgraph pg = (pgraph)malloc(sizeof(struct graph));
	if (!pg)
	{
		perror("pg malloc fail");
		exit(1);
	}
	memset(pg->visited, 0, sizeof(int)*Vertexnum);
	pg->vertexnum = Vertexnum;
	pg->edgenum = 0;
	pg->weight = (int(*)[Vertexnum])malloc(sizeof(int[Vertexnum])*Vertexnum);
	if (!pg->weight)
	{
		perror("pg->weight malloc fail");
		exit(1);
	}
	pg->reweight = (int(*)[Vertexnum])malloc(sizeof(int[Vertexnum])*Vertexnum);
	if (!pg->reweight)
	{
		perror("pg->reweight malloc fail");
		exit(1);
	}
	if (!fp)
	{
		perror("fp open fail");
		exit(1);
	}
	while (fgets(line, sizeof(line), fp))
	{
		tmp = line;
		while (*tmp != '\n'&&*tmp != '\0')
		{
			while (*tmp == ' ')tmp++;
			sscanf(tmp, "%d,%d", &from, &to);
			pg->weight[from][to] = 1;
			pg->reweight[to][from] = 1;
			pg->edgenum++;
			while (*tmp != ' '&&*tmp != '\0')tmp++;
		}
	}
	return pg;
}

void dfs1(pgraph pg,int vertex,pstack ps)
{
	int i = 0;
	pg->visited[vertex] = 1;
	for (i = 0; i < Vertexnum; i++)
	{
		if (!pg->visited[i] && pg->weight[vertex][i] > 0)
		{
			dfs1(pg, i, ps);
		}
	}
	push(ps, vertex);
}

void dfs2(pgraph pg, int vertex)
{
	int i = 0;
	pg->visited[vertex] = 1;
	printf("%d,",vertex);
	for (i = 0; i < Vertexnum; i++)
	{
		if (pg->reweight[vertex][i] > 0 && !pg->visited[i])
		{
			dfs2(pg, i);
		}
	}
}

int strong_branch(pgraph pg, pstack ps)
{
	int tmp = 0;
	int cnt = 0;
	int i = 0;
	for (i = 0; i < Vertexnum; i++)
	{
		if(!pg->visited[i])
		dfs1(pg, i, ps);
	}
	memset(pg->visited, 0, sizeof(int)*Vertexnum);
	while (!is_empty(ps))
	{
		tmp = pop(ps);
		if (!pg->visited[tmp])
		{
			dfs2(pg, tmp);
			cnt++;
			printf("\n");
		}
	}
	return cnt;
}

int main()
{
	int cnt;
	pgraph pg = initgraph();
	pstack ps = initstack(Vertexnum);
	cnt=strong_branch(pg, ps);
	printf("cnt:%d\n", cnt);
    return 0;
}

