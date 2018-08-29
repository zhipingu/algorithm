// turnpike.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>

#define Distance_num 15
#define Xnum 6//C6,2=15,坐标个数

typedef struct distset * pdistset;

struct node
{
	int dist;
	int count;
	int findcount;//用于find时，作标记，避免一个dist（且count==1）被find多次,find一次减一
};

struct distset
{
	struct node * distance;
	int size;
	int distnum;//剩余的distance数目，因为有重复的，所以和size不等
};

int find_max(pdistset pd)
{
	int i;
	for (i = 0; i<pd->size; i++)
	{
		if (pd->distance[pd->size - i].count > 0)return pd->distance[pd->size - i].dist;
	}
	return 0;
}

int find(pdistset pd, int key,int left,int right)
{
	int mid = (left + right) / 2;
	if (left > right)return 0;
	if (key < pd->distance[mid].dist)return find(pd, key, left, mid - 1);
	else
		if (key > pd->distance[mid].dist)return find(pd, key, mid + 1, right);
		else
		{
			if (pd->distance[mid].findcount > 0)
			{
				pd->distance[mid].findcount--;
				return 1;
			}
			{
				pd->distance[mid].findcount--;
				return 0;
			}
		}
}

int find_undo(pdistset pdist, int key, int left, int right)
{
	int mid = (left + right) / 2;
	if (left > right) return 0;
	if (key < pdist->distance[mid].dist)return find_undo(pdist, key, left, mid - 1);
	else
		if (key > pdist->distance[mid].dist)return find_undo(pdist, key, mid + 1, right);
		else
		{
			pdist->distance[mid].findcount++;
			return 0;
		}
}

void insert(pdistset pd, int key)
{
	int i;
	for (i = 0; i < pd->size; i++)
	{
		if (pd->distance[i].dist == key)
		{
			pd->distance[i].count++;
			pd->distance[i].findcount++;
			pd->distnum++;
		}
	}
}

void Delete(pdistset pd, int key)
{
	int i;
	for (i = 0; i < pd->size; i++)
	{
		if (pd->distance[i].dist == key)
		{
			pd->distance[i].count--;
			pd->distance[i].findcount--;
			pd->distnum--;
		}
	}
}

void insert_sort(pdistset pd, int len)
{
	int i, j;
	struct node tmp;
	for (i = 0; i < len-1; i++)
	{
		j = i + 1;
		tmp = pd->distance[j];
		while (j > 0 && tmp.dist < pd->distance[j - 1].dist)
		{
			pd->distance[j] = pd->distance[j - 1];
			j--;
		}
		pd->distance[j] = tmp;
	}
}
int place(int x[], pdistset pdist, int N, int left, int right)
{
	int max;
	int i,j;
	int flag=0, flag1=1;
	if (pdist->distnum == 0)return  1;
	max = find_max(pdist);
	//测试x[right] = max行不行
	for (i = 1, j = right + 1; i < left||j <= N; i++,j++)
	{
		if (i < left)
		{
			if (!(find(pdist, max - x[i], 0, pdist->size - 1)))
			{
				flag1 = 0;
				//break;
			}
		}
		if (j <= N)
		{
			if (!(find(pdist, x[j] - max, 0, pdist->size - 1)))
			{
				flag1 = 0;
				//break;
			}
			
		}
	}
	for (i = 1, j = right + 1; i < left || j <= N; i++, j++)
	{
		if (i < left)
		{
			if (!(find_undo(pdist, max - x[i], 0, pdist->size - 1)))
			{
				//flag1 = 0;
				//break;
			}
		}
		if (j <= N)
		{
			if (!(find_undo(pdist, x[j] - max, 0, pdist->size - 1)))
			{
				//flag1 = 0;
				//break;
			}

		}
	}
	if (flag1)
	{
		x[right] = max;

		for (i = 1; i < left; i++)
		{
			Delete(pdist, max - x[i]);
		}
		for (i = right + 1; i <= N; i++)
		{
			Delete(pdist, x[i] - max);
		}
		flag = place(x, pdist, N, left, right - 1);
		if (!flag)
		{
			for (i = 1; i < left; i++)
			{
				insert(pdist, max - x[i]);
			}
			for (i = right + 1; i <= N; i++)
			{
				insert(pdist, x[i] - max);
			}
		}
	}
	flag1 = 1;
	if (!flag)
	{
		for (i = 1, j = right + 1; i < left|| j <= N; i++,j++)
		{
			if (i < left)
			{
				if (!(find(pdist, x[N] - max - x[i], 0, pdist->size - 1)))
				{
					flag1 = 0;
					//break;
				}
			}
			if (j <= N)
			{
				if (!(find(pdist, x[j] - (x[N] - max), 0, pdist->size - 1)))
				{
					flag1 = 0;
					//break;
				}
			
			}
		}

		for (i = 1, j = right + 1; i < left || j <= N; i++, j++)
		{
			if (i < left)
			{
				if (!(find_undo(pdist, x[N] - max - x[i], 0, pdist->size - 1)))
				{
					//flag1 = 0;
					//break;
				}
			}
			if (j <= N)
			{
				if (!(find_undo(pdist, x[j] - (x[N] - max), 0, pdist->size - 1)))
				{
					//flag1 = 0;
					//break;
				}

			}
		}

		if (flag1)
		{
			x[left] = x[N] - max;

			for (i = 1; i < left; i++)
			{
				Delete(pdist, x[N] - max - x[i]);
			}
			for (i = right + 1; i <= N; i++)
			{
				Delete(pdist, x[i] - (x[N] - max));
			}
			flag = place(x, pdist, N, left + 1, right);
			if (!flag)
			{
				for (i = 1; i < left; i++)
				{
					insert(pdist, x[N] - max - x[i]);
				}
				for (i = right + 1; i <= N; i++)
				{
					insert(pdist, x[i] - (x[N] - max));
				}
			}
		}
	}
	return flag;

}

int turnbike(int x[], int N,pdistset pdist)
{
	x[1] = 0;
	x[N] = find_max(pdist);
	Delete(pdist, x[N]);
	x[N - 1] = find_max(pdist);
  	Delete(pdist, x[N - 1]);
	if (find(pdist, x[N] - x[N - 1], 0, pdist->size - 1))
	{
		find_undo(pdist, x[N] - x[N - 1], 0, pdist->size - 1);
		Delete(pdist, x[N] - x[N - 1]);
		return place(x, pdist, N, 2, N - 2);
	}
	else
	{
		find_undo(pdist, x[N] - x[N - 1], 0, pdist->size - 1);
		return 0;
	}
}

void print(int x[],int len)
{
	int i = 0;
	for (i = 1; i < len; i++)
	{
		printf("x%d:%d ",i, x[i]);
	}
	printf("\n");
}

int main()                                      
{
	struct distset D;
	int x[7];
	int i;
	int d[] = { 1,2,2,2,3,3,3,4,5,5,5,6,7,8,10 };
	memset(&D, 0, sizeof(D));
	D.distance = (struct node *)malloc(sizeof(struct node) * 30);
	if (!D.distance)
	{
		perror("D.distance malloc fail");
		exit(1);
	}
	memset(D.distance, 0, sizeof(struct node) * 30);
	D.distnum = sizeof(d)/sizeof(d[0]);
	D.size = 0;
	D.distance[0].count = 1;
	D.distance[0].findcount = 1;
	D.distance[D.size++].dist = d[0];
	for (i = 1; i < D.distnum; i++)
	{
		if (d[i] != D.distance[D.size - 1].dist)
		{
			D.distance[D.size].count++;
			D.distance[D.size].findcount++;
			D.distance[D.size++].dist = d[i];
		}
		else
		{
			D.distance[D.size - 1].count++;
			D.distance[D.size-1].findcount++;
		}
	}
 	turnbike(x, 7-1, &D);
	print(x, 7);
    return 0;
}

