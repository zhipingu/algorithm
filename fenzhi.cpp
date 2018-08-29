// fenzhi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>
#include<time.h>

double eval(int N)
{
	int i = 0;
	double sum = 0,result;
	double *C = (double *)malloc(sizeof(double)*(N+1));
	if (!C)
	{
		perror("C malloc fail");
		exit(1);
	}
	C[0] = 1;
	for (i = 1; i <= N; i++)
	{
		sum += C[i - 1];
		C[i] = 2 * sum / i + i;
	}
	result = C[N];
	free(C);
	return result;
}


int main()
{
	clock_t start, end;
	double result;
	
	
	
	/*printf("%lf\n", eval(0));
	printf("%lf\n", eval(1));
	printf("%lf\n", eval(2));
	printf("%lf\n", eval(3));
	printf("%lf\n", eval(4));*/
	start = clock();
	eval(10000);//小于1ms，clock测不出来
	//eval(100000);
	//eval(1000000);
	end = clock();
	result = (double)(end - start) / CLOCKS_PER_SEC;
	printf("%d,%d\n", start, end);
//	printf("result:%lf\n", result);
/*
	start = clock();
	eval(100);
	end = clock();
	result = (double)(end - start) / CLOCKS_PER_SEC;
	printf("%d,%d\n", start, end);
	printf("result:%lf\n", result);

	start = clock();
	eval(1000);
	end = clock();
	result = (double)(end - start) / CLOCKS_PER_SEC;
	printf("%d,%d\n", start, end);
	printf("result:%lf\n", result);
*/
    return 0;
}

