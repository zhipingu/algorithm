// cut_steel_pipe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>

#define Length 9

double cut_pipe(double cost[], int length, double r[],int cut_point[])
{
	int i;//代表不同的总长
	int j;//代表分界点
	//double tmp;
	r[0] = 0;
	for (i = 1; i <= length; i++)
	{
		r[i] = 0;//初始化r[i]
		for (j = 1; j <= i; j++)
		{
			if (r[i] < cost[j] + r[i - j])
			{
				r[i]  = cost[j] + r[i - j];
				cut_point[i] = j;
			}
		}

	}
	return r[length];
}


int main()
{
	double cost[] = { 0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };
	double r[Length + 1] ;
	int cut_point[Length+1];
	double result = cut_pipe(cost, Length, r, cut_point);
	int tmp;
	printf("total:%f\n", result);
	tmp = Length;
	while (tmp)
	{
		printf("%d ", cut_point[tmp]);
		tmp = tmp - cut_point[tmp];
	}

    return 0;
}

