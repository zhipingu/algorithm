// BinaryHeap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>


typedef struct BinaryHeap* pBinaryHeap;
struct BinaryHeap
{
	int capacity;
	int size;
	int *elements;
};

pBinaryHeap InitBinaryHeap(int capacity)
{
	pBinaryHeap B;
	B = (pBinaryHeap)malloc(sizeof(BinaryHeap));
	if (!B)
	{
		printf("B allocate fail\n");
		exit(1);
	}
	B->capacity = capacity;
	B->size = 0;
	B->elements = (int *)malloc(sizeof(int)*(capacity + 1));
	if (!B->elements)
	{
		printf("B->elements allocate fail\n");
		exit(1);
	}
	B->elements[0] = -100;

	return B;
}

void insert(pBinaryHeap B,int key)
{
	int i = ++B->size;
	//因为加了sentinel B->element[0]=-1,所以循环一定会退出，而且不用每次检测i==1?
	while (key < B->elements[i / 2])
	{
		B->elements[i] = B->elements[i / 2];
		i = i / 2; 
	}
	B->elements[i] = key;
}

int Deletemin(pBinaryHeap B)
{
	int i = 1;
	int min = B->elements[1];
	int lastelement = B->elements[B->size--];
	int child = 2*i;
	while (child <= B->size)
	{
		if (child != B->size)
		{
			if (B->elements[child] > B->elements[child + 1])child = child + 1;
		}
		if (lastelement > B->elements[child])B->elements[i] = B->elements[child];
		else break;

		i = child;
		child = 2 * i;
	}
	B->elements[i] = lastelement;
	/*
	while (2*i <=B->size)
	{
		if ((2 * i != B->size) && B->elements[2 * i] > B->elements[2 * i + 1])
		{
			if (lastelement > B->elements[2 * i + 1])
			{
				B->elements[i] = B->elements[2 * i + 1];
				i = 2 * i + 1;
			}
			else break;
		}
		else 
			if (lastelement > B->elements[2 * i])
			{
				B->elements[i] = B->elements[2 * i];
				i = 2 * i;
			}
			else break;
	}
	
	B->elements[i] = lastelement;
*/
	return min;
}

void PercolateDown(pBinaryHeap B, int index)
{
	int child = 2 * index;
	int key = B->elements[index];
	while (child <= B->size)
	{
		if (child != B->size&&B->elements[child] > B->elements[child + 1])child++;
		if (key > B->elements[child])B->elements[index] = B->elements[child];
		else break;
		index = child;
		child = 2 * index;
	}
	B->elements[index] = key;
}

void PercolateUp(pBinaryHeap B, int index)
{
	int key = B->elements[index];
	while (key < B->elements[index / 2])
	{
		B->elements[index] = B->elements[index / 2];
		index = index / 2;
	}
	B->elements[index] = key;

}

void DecreaseKey(pBinaryHeap B, int index, int decrease)
{
	B->elements[index] -= decrease;
	PercolateUp(B, index);
}

void IncreaseKey(pBinaryHeap B, int index, int increase)
{
	B->elements[index] += increase;
	PercolateDown(B, index);

}

void BuildHeap(pBinaryHeap B,int a[],int len)
{
	int i;
	for (i = 0; i < len; i++)
	{
		B->elements[i + 1] = a[i];
		B->size++;
	}

	for (i = B->size / 2; i>0; i--)
	{
		PercolateDown(B, i);
	}
}

void Delete(pBinaryHeap B, int index)
{
	DecreaseKey(B, index,B->elements[index]);
	Deletemin(B);
}
void print(pBinaryHeap B)
{
	int i = 1;
	for (; i <= B->size; i++)
		printf("%d ", B->elements[i]);
	printf("\n");
	printf("=====\n");
}
int main()
{
	pBinaryHeap B = InitBinaryHeap(20);
	int i = 0;
	int a[] = {150,80,40,30,10,70,110,100,20,90,60,50,120,140,130};
	int len = sizeof(a) / sizeof(a[0]);

	BuildHeap(B,a,8);
	print(B);
	for (i = 8; i < len; i++)
	{
		if (a[i] > B->elements[1])
		{
			Deletemin(B);
			insert(B, a[i]);
		}
	}
	printf("%d\n", Deletemin(B));
/*
//	DecreaseKey(B, 12, 68);
//	print(B);
	IncreaseKey(B, 3, 110);
	print(B);

	Delete(B, 15);
	print(B);
//	for (i = 0; i < 8; i++)
//		printf("%d ", Deletemin(B));
*/
    return 0;
}

