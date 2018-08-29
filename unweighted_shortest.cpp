// unweighted_shortest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>

#define Vertexnum 7
#define Infinity 1000

typedef struct queue *pQueue;
typedef struct adjacent_node *padjacent;
typedef struct graph *pgraph;
//front指向队首元素，rear指向队尾元素
struct queue {
	int front;
	int rear;
	int size;
	int capacity;
	int * pqueue;
};

pQueue initqueue(int capacity)
{
	pQueue pQ = (pQueue)malloc(sizeof(struct queue));
	if (!pQ)
	{
		perror("pQ malloc fail");
		exit(1);
	}
	pQ->capacity = capacity;
	pQ->pqueue = (int *)malloc(sizeof(int)*capacity);
	if (!pQ->pqueue)
	{
		perror("pQ->queue malloc fail");
		exit(1);
	}
	pQ->front = pQ->rear = 0;
	pQ->size = 0;
	return pQ;
}

void Deletequeue(pQueue pQ)
{
	free(pQ->pqueue);
	free(pQ);
}

int is_empty(pQueue pQ)
{
	return pQ->size == 0;
}

int is_full(pQueue pQ)
{
	return pQ->size == pQ->capacity;
}

void enqueue(pQueue pQ, int key)
{
	if (is_full(pQ))
	{
		perror("queue is full");
		exit(1);
	}
	pQ->pqueue[pQ->rear++] = key;
	pQ->size++;
}

int dequeue(pQueue pQ)
{
	if (is_empty(pQ))
	{
		perror("queue is empty");
		exit(1);
	}
	pQ->size--;
	return pQ->pqueue[pQ->front++];

}

struct header
{
	int dv;
	int pv;
	struct adjacent_node *adjacent;
};

struct adjacent_node
{
	int vertex;
	struct adjacent_node *next;
};

void create_adjacent(struct adjacent_node *adjacent[])
{
	struct adjacent_node *newnode=NULL;
	struct adjacent_node *tmp=NULL;
	int i,j=0;
	int vertex;
	for (i = 0; i < Vertexnum; i++)
	{
		printf("please input adjacent vertex of vertex%d:\n", i);
		j = 0;
		while (1)
		{
			scanf("%d", &vertex);
			j++;
			if (vertex == -1)
			{
				if (j == 1)
				{
					adjacent[i] = NULL;
				}
				break;
			}
			newnode = (padjacent)malloc(sizeof(struct adjacent_node));
			if (!newnode)
			{
				perror("newnode malloc fail");
				exit(1);
			}
			newnode->vertex = vertex;
			newnode->next = NULL;
			if (j == 1)
			{
				adjacent[i] = newnode;
				tmp = newnode;
			}
			else
			{
				tmp->next = newnode;
				tmp = newnode;
			}
		}
	}

}

struct graph
{
	int vertexnum;
	struct header*array;
};

pgraph initgraph(padjacent adjacent[])
{
	int i = 0;
	pgraph pg = (pgraph)malloc(sizeof(struct graph));
	pg->vertexnum = Vertexnum;
	pg->array = (struct header *)malloc(sizeof(struct header)*Vertexnum);
	if (!pg->array)
	{
		perror("pg->array malloc fail");
		exit(1);
	}
	for (; i < Vertexnum; i++)
	{
		pg->array[i].pv = -1;
		pg->array[i].dv = Infinity;
		pg->array[i].adjacent = adjacent[i];
	}
	return pg;
}

void unweighted_shortest(pgraph pg, int start_vertex)
{
	pQueue pq = initqueue(Vertexnum);
	int vertex;
	padjacent tmp = NULL;
	pg->array[start_vertex].dv = 0;
	enqueue(pq, start_vertex);
	while (!is_empty(pq))
	{
		vertex = dequeue(pq);
		tmp = pg->array[vertex].adjacent;
		while (tmp)
		{
			if (pg->array[tmp->vertex].dv == Infinity)
			{
				pg->array[tmp->vertex].dv = pg->array[vertex].dv + 1;
				pg->array[tmp->vertex].pv = vertex;
				enqueue(pq, tmp->vertex);
			}
				tmp = tmp->next;
			
		}
	}
	Deletequeue(pq);
}

void print(pgraph pg)
{
	int i = 0;
	for (; i < Vertexnum; i++)
	{
		printf("vertex%d: dv(%d) : pv(%d)\n", i, pg->array[i].dv, pg->array[i].pv);
	}
}

int main()
{

	struct adjacent_node * adjacent[Vertexnum];
	pgraph pg;
	int start = 2;

	create_adjacent(adjacent);
	pg = initgraph(adjacent);
	unweighted_shortest(pg,start);
	print(pg);

    return 0;
}

