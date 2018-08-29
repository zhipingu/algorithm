// maxflow.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>

#define Vertexnum 6
#define Infinity 1000

typedef struct queue *pQueue;

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

int bfs(int s, int t,int (*capacity)[Vertexnum],int pre[])
{
	int tmp = 0;
	int i = 0;
	int flow[Vertexnum];
	pQueue pq = initqueue(Vertexnum);
	enqueue(pq, s);
	flow[0] = Infinity;
	while (!is_empty(pq))
	{
		tmp = dequeue(pq);
		if (tmp == t)break;
		for (i = 0; i < Vertexnum; i++)
		{
			//因为pre[s]==-1,所以要加i!=s,避免绕回去
			if (i!=s&&capacity[tmp][i] > 0 && pre[i] == -1)
			{
				enqueue(pq, i);
				pre[i] = tmp;
				flow[i] = flow[tmp] < capacity[tmp][i] ? flow[tmp] : capacity[tmp][i];

			}
		}
	}

	Deletequeue(pq);
	if (pre[t] == -1)return 0;
	return flow[t];
}

int maxflow(int s, int t, int (*capacity)[Vertexnum])
{
	int tmp = 0, sumflow= 0;
	int to = 0;
	int pre[Vertexnum];
/*	int i = 0;
	for (i = 0; i < Vertexnum; i++)
	{
		pre[i] = -1;
	}
*/
	memset(pre, -1, sizeof(int)*Vertexnum);
	while (tmp = bfs(s, t, capacity, pre))
	{
		sumflow += tmp;
		to = t;
		while (pre[to] != -1)
		{
			capacity[pre[to]][to] -= tmp;
			capacity[to][pre[to]] += tmp;
			to = pre[to];
		}
		//为什么memset可以用-1初始化，因为负数在计算机中用其正数的补码表示
		//负数对应正数的补码=正数的反码+1=FF-正数+1=模-正数
		//所以负数在计算机中的表示和模-正数表示一样
		//所以-1在计算机中是256-1=255（11111111）一个字节
		//所以pre(11111111 11111111 11111111 11111111)*Vertexnum
		//所以pre（全是1）,最后还是-1
		//所以memset可以用0（二进制全是0），-1（二进制全是1）初始化int数组
		memset(pre, -1, sizeof(int)*Vertexnum);

	}
	return sumflow;
}

int main()
{
	int capacity[Vertexnum][Vertexnum];
	int from, to, cap;
	memset(capacity, 0, sizeof(int)*Vertexnum*Vertexnum);
	while (1)
	{
		printf("please input (from,to,cap),input (-1,-1,-1) end\n");
		scanf("%d %d %d", &from, &to, &cap);
		if (from == -1)break;
		capacity[from][to] += cap;
	}
	printf("maxflow:%d\n", maxflow(0, 3, capacity));
 
/*	int a, b, c;
	scanf("%dmm%dqq%d", &a, &b, &c);
	printf("%d %d %d\n", a, b, c);
*/
	return 0;
}

