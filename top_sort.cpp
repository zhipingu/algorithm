// top_sort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>

//#define  _CRT_SECURE_NO_WARNINGS
#define Vertexnum 7

typedef struct queue Queue;
typedef struct queue * pQueue;
typedef struct graph * pgraph;

typedef struct stack *pstack;
typedef struct graph *pgraph;

struct stack
{
	int top;
	int capacity;
	int *array;
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


struct node
{
	int vertex;
//	int weight;
	struct node *next;
};

struct header
{
	int indegree;
	struct node *adjacent;
};
struct graph
{
	int vertexnum;
	struct header *array;
};
void creatadjacent(struct node *adjacent[])
{
	int i = 0, j;
	int vertex;
	struct node *tmpnode = NULL;
	struct node *newnode=NULL;
	for (i = 0; i < Vertexnum; i++)
	{
		j = 0;
		printf("please input adjacent vertex of vertex %d,input -1 end\n", i);
		while (1)
		{
			scanf("%d", &vertex);
			//j是邻点的数目
			++j;
			if (vertex == -1)
			{
				if (j == 1) adjacent[i] = NULL;
				break;
			}
			newnode = (struct node *)malloc(sizeof(struct node));
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
				tmpnode = newnode;
			}
			else
			{
				tmpnode->next = newnode;
				tmpnode = tmpnode->next;
			}
		}
	}
}
pgraph initgraph(int vertexnum,int indegree[],struct node* adjacent[])
{
	pgraph pg = (pgraph)malloc(sizeof(graph));
	int i;
	if (!pg)
	{
		perror("pgraph malloc fail");
		exit(1);
	}
	pg->vertexnum = vertexnum;
	pg->array = (struct header *)malloc(sizeof(struct header)*(vertexnum));
	if (!pg->array)
	{
		perror("pg->array malloc fail");
		exit(1);
	}
	for (i = 0; i <vertexnum; i++)
	{
		pg->array[i].indegree = indegree[i];
		pg->array[i].adjacent = adjacent[i];
	}

	return pg;
}

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
	pQueue pQ=(pQueue)malloc(sizeof(queue));
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

void top_sort(pgraph pg,int topnum[])
{
	int i;
	pQueue pQ;
	int vertex;
	int count = 0;
	struct node *tmp;
	pQ=initqueue(pg->vertexnum);
	for (i = 0; i < pg->vertexnum; i++)
	{
		if (pg->array[i].indegree == 0) 
		{
			enqueue(pQ, i);
		}
		
	}
	while (!is_empty(pQ))
	{
		vertex = dequeue(pQ);
		topnum[vertex] = ++count;
		tmp = pg->array[vertex].adjacent;
		while (tmp)
		{
			if (--pg->array[tmp->vertex].indegree == 0)enqueue(pQ, tmp->vertex);
			tmp = tmp->next;
		}
	}

	if (count != pg->vertexnum)
	{
		printf("count:%d  pg->vertexnum:%d\n", count, pg->vertexnum);
		perror("graph has cycle");
		exit(1);
	}

	Deletequeue(pQ);
}

void top_sort2(pgraph pg, int topnum[])
{
	int i;
	pstack ps;
	int vertex;
	int count = 0;
	struct node *tmp;
	ps = initstack(pg->vertexnum);
	for (i = 0; i < pg->vertexnum; i++)
	{
		if (pg->array[i].indegree == 0)
		{
			push(ps, i);
		}

	}
	while (!is_empty(ps))
	{
		vertex = pop(ps);
		topnum[vertex] = ++count;
		tmp = pg->array[vertex].adjacent;
		while (tmp)
		{
			if (--pg->array[tmp->vertex].indegree == 0)push(ps, tmp->vertex);
			tmp = tmp->next;
		}
	}

	if (count != pg->vertexnum)
	{
		printf("count:%d  pg->vertexnum:%d\n", count, pg->vertexnum);
		perror("graph has cycle");
		exit(1);
	}

//	Deletequeue(ps);
}
//没有完成
void Deletegraph(pQueue pq)
{
	
}

void printtop(int topnum[])
{
	int i = 0;
	for (; i < Vertexnum; i++)
	{
		printf("%d : %d\n", i, topnum[i]);
	} 
	printf("\n");
}
int main()
{
	pgraph pg;
	int	indegree[] = { 0,1,2,3,1,3,2 };
	//int indegree[] = { 0,1,1 };
	struct node*adjacent[Vertexnum];
	int topnum[Vertexnum];
	int i = 0;
	
	creatadjacent(adjacent);
	pg = initgraph(Vertexnum, indegree, adjacent);
	top_sort2(pg,topnum);
	printtop(topnum);

	
    return 0;
}

