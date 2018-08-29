// test4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>

int main(int argc, const char *argv[])
{/*
	FILE *src = NULL, *dest = NULL;
	int ch = 0;
	if ((src = fopen(argv[1], "r")) == NULL)
	{
		perror("file aaa");
		exit(1);
	}
	if ((dest = fopen(argv[2], "w")) == NULL)
	{
		perror("file bbb");
		exit(1);
	}
	while ((ch = fgetc(src)) != EOF)
		fputc(ch, dest);
	fclose(src);
	fclose(dest);
*/
	int a[] = { 2,3,4,5,6 };
	int *p = (int *)malloc(sizeof(int));
	printf("%p\n",p );
	printf("%p\n", p);
	*p = 567;
	int i = 0;
	int sum = 0;
	for (; i < 10; i++)
	{
		sum += i;
	}
	free(p);
	return 0;

}