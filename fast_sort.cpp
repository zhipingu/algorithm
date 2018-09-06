// fast_sort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<random>

using namespace std;

void fast_sort(int a[], int left, int right)
{
	if (a == nullptr || right < 0 || left < 0 || right < left)
	{
		cerr << "fast_sort input is invalid" << endl;
		return;
	}
	if (left == right) return;

	int index = left;
	int small = left - 1;

	uniform_int_distribution<int> u(left, right);
	default_random_engine e;
	int pivot = u(e);
	swap(a[pivot], a[right]);

	for (; index < right; ++index)
	{
		if (a[index] < a[right])
		{
			++small;
			if (small != index)
			{
				swap(a[small], a[index]);
			}
		}
	}

	++small;
	swap(a[small], a[right]);

	pivot = small;//很重要，别忘了，分割点变了
	if(pivot>left)
	fast_sort(a, left, pivot - 1);
	if(pivot<right)
	fast_sort(a, pivot + 1, right);

}

void print(int a[], int len)
{
	if (a == nullptr || len <= 0)
	{
		cerr << "print input is invalid" << endl;
		return;
	}

	for (int i = 0; i < len; ++i)
		cout << a[i] << " ";
	cout << endl;
}

void fun()
{
	static uniform_int_distribution<int> u(0,50 );
	static default_random_engine e;
	//int pivot = u(e);
	for (int i = 0; i < 10; i++) cout <<u(e) << " ";
	cout << endl;
}
int main()
{
	//int a[] = {23,43,21,12,3,56,32,17,14,9,21,23,9,4,6};
	//int a[] = { 23,43,21,12,3,56,12,10};
	int a[] = { 4,4,4,4,4,4 };
	int len = sizeof(a) / sizeof(a[0]);

	print(a,len);
	fast_sort(a, 0, len - 1);
	print(a,len);

	/*fun();
	fun();
	fun();*/
    return 0;
}

