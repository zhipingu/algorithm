// Euler_circuit.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>

#define Vertexnum 14

typedef struct graph* pgraph;
typedef int disjset[Vertexnum];

//static char visited[Vertexnum] = {0};
static int edgevisited= 0;
struct graph
{
	int vertexnum;
	int edgenum;
	int weight[Vertexnum][Vertexnum];
};

void initdisjset(disjset s)
{
	int i = 0;
	for (i = 0; i < Vertexnum; i++)
	{
		s[i] = -1;
	}
}
int find(disjset s, int vertex)
{
	if (s[vertex] < 0)return vertex;
	return s[vertex] = find(s, s[vertex]);

}

void setunion(disjset s, int root1, int root2)
{
	if (s[root1] <= s[root2])
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

int is_euler(pgraph pg)
{
	int degree[Vertexnum];
	int i = 0, j = 0;
	int root1 = 0, root2 = 0;
	int root_counter = 0,odd_counter=0;
	disjset s;
	initdisjset(s);
	for(i=0;i<Vertexnum;i++)
		for (j = 0; j < Vertexnum; j++)
		{
			if (pg->weight[i][j] > 0)
			{
				degree[i]++;
				degree[j]++;
				root1 = find(s, i);
				root2 = find(s, j);
				if (root1 != root2)setunion(s, root1, root2);
			}
		}
	for (i = 0; i < Vertexnum; i++)
	{
		if (s[i] < 0)root_counter++;
		if (degree[i] % 2 == 1)
		{
			odd_counter++;
		}
	}
	if (root_counter == 1 && (odd_counter == 0 || odd_counter == 2))
	{
		printf("graph is euler\n");
		return 1;
	}
	else
	{
		printf("graph is not euler\n");
		return 0;
	}
}

void dfs(pgraph pg,int start, int vertex)
{
	int i = 0;
	//visited[vertex] = 1;
	for (int i = 0; i < Vertexnum; i++)
	{
		if (pg->weight[vertex][i] > 0)
		{
			pg->weight[vertex][i] = 0;
			pg->weight[i][vertex] = 0;
			edgevisited++;
			printf("(%d,%d),", vertex, i);
			if (i == start)
			{
				printf("\n");
				return;
			}
			dfs(pg, start,i);
		}
	}
	
}

void initgraph(pgraph pg)
{
	FILE *fp = fopen("graph.txt", "r");
	char line[1000];//要考虑到能不能把信息全部读进来，比如1,2 一条边就有四个字节
	char *tmp = line;
	int from, to;

	pg->vertexnum = Vertexnum;
	pg->edgenum = 0;

	while (fgets(line, sizeof(line), fp) != NULL)
	{
		tmp = line;
		while (*tmp != '\n'&&*tmp != '\0')
		{
			while (*tmp == ' ')tmp++;
			if (sscanf(tmp, "%d,%d", &from, &to) != 2)
			{
				printf("sscanf fail near %d,%d\n",from,to);
			}
			pg->weight[from][to] = 1;
			pg->weight[to][from] = 1;
			pg->edgenum++;
			while (*tmp!=' '&&*tmp!='\0')tmp++;
			
		}
	}
}


void print(pgraph pg)
{
	int i = 0, j = 0;
	for(i=0;i<pg->vertexnum;i++)
		for (j = 0; j < pg->vertexnum; j++)
		{
			if(pg->weight[i][j]>0)
			printf("(%d,%d),", i, j);
		}
}
int main()
{
	struct graph g;
	initgraph(&g);
	int i = 0, j = 0;
	int start;
	int flag = 0;
	if (is_euler(&g))
	{
		while (edgevisited != g.edgenum)
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
			dfs(&g, start, start);
		}
	}
//	print(&g);

    return 0;
}

