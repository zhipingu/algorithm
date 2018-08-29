// matrix_multiplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>

#define Matrixnum 4
#define Infinity 10000000

void optimal_matrix(const int C[], int(*M)[Matrixnum+1], int(*lastchange)[Matrixnum+1])
{
	int i;//�ֽ��
	int k;//left��right����
	int left, right;
	int thisM;//ͳ�Ƴ˷�����
	for (left = 1; left <= Matrixnum; left++)
	{
		M[left][left] = 0;
	}
	for (k = 1; k < Matrixnum; k++)
	{
		for (left = 1; left <= Matrixnum - k; left++)
		{
			right = left + k;
			M[left][right] = Infinity;
			for (i = left; i < right; i++)
			{
				//��Ϊleft=0ʱ��left-1=-1��C[-1]��Ч������left��1��ʼ
				thisM = M[left][i] + M[i + 1][right] + C[left - 1]*C[i]*C[right];
				if (thisM < M[left][right])
				{
					M[left][right] = thisM;
					lastchange[left][right] = i;
				}
			}
		}
	}
}


int main()
{
	int C[Matrixnum+1] = {50,10,40,30,5};
	int M[5][5];
	int lastchange[5][5] = { 0 };
	optimal_matrix(C, M, lastchange);
	printf("%d\n", M[1][4]);
	printf("%d\n", lastchange[1][4]);
	printf("%d,%d\n", lastchange[1][lastchange[1][4]], lastchange[lastchange[1][4] + 1][4]);
	printf("%d\n", lastchange[lastchange[lastchange[1][4] + 1][4]+1][4]);
    return 0;
}

