// prim.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>

#define Vertexnum 7
#define Infinity 1000


typedef struct graph *pgraph;
typedef struct PriorityQueue * pPriorityQueue;

struct QueueElement
{
	int dv;
	int vertex;
};

struct PriorityQueue
{
	int capacity;
	int size;
	struct QueueElement *array;

};

pPriorityQueue initpriorityqueue(int capacity)
{
	pPriorityQueue pPQ;
	pPQ = (pPriorityQueue)malloc(sizeof(struct PriorityQueue));
	if (!pPQ)
	{
		perror("pPQ malloc fail");
		exit(1);
	}
	pPQ->capacity = capacity;
	pPQ->size = 0;
	pPQ->array = (struct QueueElement *)malloc(sizeof(struct QueueElement)*(capacity + 1));
	if (!pPQ->array)
	{
		perror("pPQ->array malloc fail");
		exit(1);
	}
	//sentinel
	pPQ->array[0].dv = -100;
	return pPQ;
}

void percolatedown(pPriorityQueue pPQ, int i, int N)
{
	int child = 2 * i;
	struct QueueElement tmp = pPQ->array[i];
	while (child <= N)
	{
		if (child != N&&pPQ->array[child + 1].dv < pPQ->array[child].dv)
			child++;
		if (tmp.dv > pPQ->array[child].dv)
			pPQ->array[i] = pPQ->array[child];
		else break;
		i = child;
		child = 2 * i;
	}
	pPQ->array[i] = tmp;
}

void insert(pPriorityQueue pPQ, struct QueueElement element)
{
	int i = 0;
	if (pPQ->size == pPQ->capacity)
	{
		perror("Priority is full");
		return;
	}

	i = ++pPQ->size;
	while (element.dv < pPQ->array[i / 2].dv)
	{
		pPQ->array[i] = pPQ->array[i / 2];
		i /= 2;
	}
	pPQ->array[i] = element;
}

struct QueueElement Deletemin(pPriorityQueue pPQ)
{
	struct QueueElement min = pPQ->array[1];
	struct QueueElement lastelement;
	int i = 1, child = 2 * i;
	if (pPQ->size == 0)
	{
		perror("PriorityQueue is empty");
		return pPQ->array[0];
	}
	lastelement = pPQ->array[pPQ->size--];
	for (i = 1; child <= pPQ->size; i = child, child = 2 * i)
	{
		if (child != pPQ->size&&pPQ->array[child].dv > pPQ->array[child + 1].dv)
			child++;
		if (lastelement.dv > pPQ->array[child].dv)
			pPQ->array[i] = pPQ->array[child];
		else break;
	}
	pPQ->array[i] = lastelement;
	return min;
}

void decreasekey(pPriorityQueue pPQ, int i, int difference)
{
	struct QueueElement tmp;
	pPQ->array[i].dv -= difference;
	tmp = pPQ->array[i];
	for (; tmp.dv < pPQ->array[i / 2].dv; i = i / 2)
	{
		pPQ->array[i] = pPQ->array[i / 2];
	}
	pPQ->array[i] = tmp;
}

int find(pPriorityQueue pPQ, int vertex)
{
	int i = 0;
	for (i = 1; i <= pPQ->size; i++)
	{
		if (pPQ->array[i].vertex == vertex) return i;
	}
	printf("priority find no %d", vertex);
	return -1;
}
struct adjacent_node
{
	int vertex;
	int Cvw;
	struct adjacent_node *next;
};


struct header
{
	int dv;
	int pv;
	int known;
	struct adjacent_node *adjacent;
};
struct graph
{
	int capacity;
	struct header *array;
};

//.txt文件中的节点，在文件中的行号为from顶点编号
struct filenode
{
	int vertex;
	int Cvw;
};
void getdata(char *filename, struct filenode result[], int len)
{
	FILE *fp;
	char ch[100];
	char *tmp = ch;
	int i = 0, j = 0, linenum = 0;
	int sum = 0;
	fp = fopen(filename, "r");
	if (!fp)
	{
		perror("fp open fail");
		exit(1);
	}
	for (linenum = 1; linenum <= Vertexnum&&j<len; linenum++)
	{
		if (!fgets(ch, 100, fp)) break;
		tmp = ch;
		//最后一行可能没有换行符
		while (*tmp != '\n'&&*tmp != '\0')
		{
			if (*tmp == '-')break;
			while (*tmp != ' ')
			{
				i++;
				tmp++;
			}
			while (*(tmp - i) != ',')sum = sum * 10 + *(tmp - i--) - 0x30;
			result[j].vertex = sum;
			sum = 0;
			i--;
			while (*(tmp - i) != ' ')sum = sum * 10 + *(tmp - i--) - 0x30;
			result[j].Cvw = sum;
			j++;
			tmp++;
			sum = 0;
			i = 0;
		}
		//-1作为每一行数据的分隔符
		result[j++].vertex = -1;
	}
	fclose(fp);
	//所有输入终止标志
	//result[j].vertex = -2;
}

void create_adjacent(struct adjacent_node *adjacent[], struct filenode inputdata[])
{
	int i = 0, j = 0, k = -1;
	struct adjacent_node *newnode = NULL, *tmp = NULL;
	for (i = 0; i < Vertexnum; i++)
	{
		//j每个顶点邻接点的个数
		j = 0;
		while (1)
		{
			j++;
			k++;
			if (inputdata[k].vertex == -1)
			{
				if (j == 1)
				{
					adjacent[i] = NULL;
				}
				break;
			}
			newnode = (struct adjacent_node *)malloc(sizeof(struct adjacent_node));
			if (!newnode)
			{
				perror("newnode malloc failed");
				exit(1);
			}
			newnode->vertex = inputdata[k].vertex;
			newnode->Cvw = inputdata[k].Cvw;
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

pgraph initgraph(struct adjacent_node *adjacent[])
{
	pgraph pg = (pgraph)malloc(sizeof(struct graph));
	int i = 0;
	if (!pg)
	{
		perror("pg malloc fail");
		exit(1);
	}
	pg->capacity = Vertexnum;
	pg->array = (struct header*)malloc(sizeof(struct header)*Vertexnum);
	if (!pg->array)
	{
		perror("pg->array malloc fail");
		exit(1);
	}
	for (i = 0; i < Vertexnum; i++)
	{
		pg->array[i].adjacent = adjacent[i];
		pg->array[i].dv = Infinity;
		pg->array[i].known = 0;
		pg->array[i].pv = -1;
	}
	return pg;
}

void prim(pgraph pg)
{
	int start = 0;
	int i = 0;
	int min = 0;
	struct adjacent_node *tmp = NULL;
	pg->array[start].dv = 0;
	while (1)
	{
		min = Infinity;
		for (i = 0; i < Vertexnum; i++)
		{
			if (pg->array[i].known == 0)
			{
				if (min == Infinity)min = i;
				else if (pg->array[i].dv < pg->array[min].dv)min = i;
			}
		}
		if (min == Infinity)break;
		pg->array[min].known = 1;
		tmp = pg->array[min].adjacent;
		while (tmp)
		{
			if (pg->array[tmp->vertex].known == 0 && pg->array[tmp->vertex].dv > tmp->Cvw)
			{
				pg->array[tmp->vertex].dv = tmp->Cvw;
				pg->array[tmp->vertex].pv = min;
			}
			tmp = tmp->next;
		}
	}
	

}

void printpath(pgraph pg, int vertex)
{
	if (pg->array[vertex].pv != -1)
	{
		printpath(pg, pg->array[vertex].pv);
		printf(" to ");
	}
	printf("%d", vertex);
	//以下是错误的
	/*
	if(pg->array[vertex].pv != -1)
	{
	printpath(pg, pg->array[vertex].pv);
	printf("to");
	}
	else
	printf("%d", vertex);
	*/
}

void print(pgraph pg)
{
	int i = 0;
	for (i = 0; i < Vertexnum; i++)
	{
		printf("vertex,dv,pv:%d,%d,%d\n", i, pg->array[i].dv, pg->array[i].pv);
	}
}

int main()
{
	struct filenode result[50];
	struct adjacent_node *adjacent[Vertexnum];
	pgraph pg = NULL;
	getdata("graph.txt", result, 50);
	create_adjacent(adjacent, result);
	pg = initgraph(adjacent);
	prim(pg);
	print(pg);

    return 0;
}

