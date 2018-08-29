// articulation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>

#define Vertexnum 7

typedef struct adjacent_node *padjacent_node;
typedef struct graph *pgraph;
typedef struct record *precord;


struct record
{
	int num[Vertexnum], low[Vertexnum];
	char visited[Vertexnum];
	//为了区分已访问的顶点到底是父节点，还是回边
	int parent[Vertexnum];
	int counter;
};

struct adjacent_node
{
	int vertex;
	struct adjacent_node *next;
};

struct header
{
	int vertex;
	padjacent_node adjacent;
};

struct graph
{
	padjacent_node *array;
	int vertexnum;
};

pgraph create_graph()
{
	pgraph pg;
	FILE *fp;
	int from;
	int i = 0;
	char line[50];
	char *p = line;
	padjacent_node tmp;
	fp = fopen("graph.txt", "r");
	if (!fp)
	{
		perror("fp open fail");
		exit(1);
	}

	pg = (pgraph)malloc(sizeof(struct graph));
	if (!pg)
	{
		perror("pg malloc fail");
		exit(1);
	}
	pg->vertexnum = Vertexnum;
	pg->array = (padjacent_node*)malloc(sizeof(padjacent_node)*Vertexnum);
	if (!pg->array)
	{
		perror("pg->array malloc fail");
		exit(1);
	}
	memset(pg->array, 0, sizeof(padjacent_node)*Vertexnum);

	//读入文件数据构建邻接表
	for (i = 0; i < Vertexnum; i++)
	{
		tmp = pg->array[i];
		fgets(line, sizeof(line), fp);
		p = line;
		while (*p != '\n'&&*p != '\0')
		{
			while (*p == ' ')p++;
			sscanf(p, "%d", &from);
			//printf("%d ", from);
			while (*p >= '0'&&*p <= '9')p++;
			//每一行第一个元素时
			if (pg->array[i]==NULL)
			{
				tmp = (padjacent_node)malloc(sizeof(struct adjacent_node));
				if (!tmp)
				{
					perror("tmp malloc fail");
					exit(1);
				}
				tmp->vertex = from;
				tmp->next = NULL;
				pg->array[i] = tmp;
			}
			else
			{
				tmp->next= (padjacent_node)malloc(sizeof(struct adjacent_node));
				if (!tmp->next)
				{
					perror("tmp malloc fail");
					exit(1);
				}
				tmp->next->vertex = from;
				tmp->next->next = NULL;
				tmp = tmp->next;
			}
	
		}
	}
	return pg;
}

void find_art(pgraph pg, int vertex, precord pr)
{
	padjacent_node tmp = NULL;
	int children = 0;
	pr->num[vertex] = pr->low[vertex]=pr->counter++;
	tmp = pg->array[vertex];
	pr->visited[vertex] = 1;
	while (tmp)
	{
		
		if (!pr->visited[tmp->vertex])//前向边
		{
			pr->parent[tmp->vertex] = vertex;
			
			children++;
			//根
			if (pr->parent[vertex] == -1 && children>1)
			{
				printf("%d is a articulation point====\n", vertex);
			}
			find_art(pg, tmp->vertex, pr);
			if (pr->low[tmp->vertex] >= pr->num[vertex]&&pr->parent[vertex]!=-1)
			{
				printf("%d is a articulation point\n", vertex);
			}
			pr->low[vertex] = pr->low[vertex] < pr->low[tmp->vertex] ? pr->low[vertex] : pr->low[tmp->vertex];

		}
		else
			if (pr->parent[vertex] != tmp->vertex)//回向边
				pr->low[vertex] = pr->low[vertex] < pr->num[tmp->vertex] ? pr->low[vertex] : pr->num[tmp->vertex];
		tmp = tmp->next;
		
	}
}
void printgraph(pgraph pg)
{
	int i = 0;
	padjacent_node tmp;
	for (i = 0; i < Vertexnum; i++)
	{
		tmp = pg->array[i];
		while (tmp)
		{
			printf("%d ", tmp->vertex);
			tmp = tmp->next;
		}
		printf("\n");
	}
}
int main()
{
	pgraph pg=create_graph();
	//printgraph(pg);
	struct record re;
	int root =3;
	memset(&re, 0, sizeof(struct record));
	re.parent[root] = -1;
	find_art(pg, root, &re);
    return 0;
}

