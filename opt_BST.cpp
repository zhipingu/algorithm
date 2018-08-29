// opt_BST.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>

#define Num 7
#define INF 1000000

typedef struct outarg * poutarg;

struct outarg
{
	double w[Num+1][Num+1];//W[i][j]放ki到kj概率
	int root[Num+1][Num+1];//放i到j的根
	double cost[Num+1][Num+1];//放i到j的最小代价
};

double opt_bst(double p[], poutarg po)
{
	int len,i, j, k;
	double tmp;
	for (i = 1; i <= Num; i++)
	{
		po->w[i][i] = p[i];
		po->cost[i][i] = p[i];
	}
	for (len = 1; len <= Num; len++)
	{
		for (i = 1; i <= Num-len; i++)
		{
			j = i + len;
			po->cost[i][j] = INF;
			po->w[i][j] = po->w[i][j - 1] + p[j];
			for (k = i; k <= j; k++)
			{
				if(k==i)tmp= po->cost[k + 1][j] + po->w[i][j];
				else 
					if(k==j)tmp=po->cost[i][j-1]+ po->w[i][j];
					else tmp = po->cost[i][k - 1] + po->cost[k + 1][j] + po->w[i][j];
					if (tmp < po->cost[i][j])
					{
						po->cost[i][j] = tmp;
						po->root[i][j] = k;
					}
			}
		}
	}
	return po->cost[1][Num];
}

int main()
{
	double p[] = {0,0.22,0.18,0.20,0.05,0.25,0.02,0.08};
	struct outarg og;
	opt_bst(p, &og);
	printf("cost:%lf\n", og.cost[1][Num]);
	printf("root:%d\n", og.root[1][Num]);
	printf("%lf\n", p[og.root[1][Num]]);
	//printf("root:%d\n", og.root[1][og.root[1][Num] - 1]);
	//printf("%d\n", og.root[og.root[1][Num]+1][Num]);
//	printf("root:%d\n", og.root[1][og.root[1][og.root[1][Num] - 1]-1]);
	//printf("root:%d\n", og.root[1][og.root[1][og.root[1][og.root[1][Num] - 1] - 1]-1]);
    return 0;
}

