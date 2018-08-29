// leap_table.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>

void fun()
{
	int a;
	int b;
	int c;
	int *d;
	d=(int*)malloc(sizeof(int) * 20);
	memset(d, 0, sizeof(int) * 20);
	a = 2;
	b = 3;
	c = 4;
	d[10] = 8;
}

int main()
{
	int i;
	int j;
	int k;
	for (i = 0; i < 10; i++)
	{
		if (i == 4) k = 8;
	}
	
    return 0;
}

