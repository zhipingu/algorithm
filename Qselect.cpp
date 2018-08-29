#include"stdafx.h"
#include<iostream>
#include<string>
#include<vector>
#include<random>

using namespace std;

int partion(int a[], int left, int right)
{
	if (!a || right - left<0)
	{
		cerr << "input is invalid" << endl;
		exit(1);
	}

	uniform_int_distribution<unsigned> u(left, right);
	default_random_engine e;
	int pivot = u(e);
	std::swap(a[pivot], a[right]);

	int small = left - 1;
	int current = left;

	for (; current<right; ++current)
	{
		if (a[current]<a[right])
		{
			++small;
			if (small != current)
			{
				std::swap(a[small], a[right]);
			}
		}
	}
	++small;
	std::swap(a[small], a[right]);

	return small;
}

int Qselect(int a[], int left, int right, int k)
{
	if (!a || right - left < 0 || k <= 0)
	{
		cerr << "input is invalid" << endl;
		exit(1);
	}

	int index = partion(a, left, right);
	if (k < index + 1)
	{
		right = index - 1;
		index = Qselect(a, left, right, k);
	}
	else
		if (k > index + 1)
		{
			left = index + 1;
			index = Qselect(a, left, right, k);
		}

	return a[index];
}

int main()
{

	int a[] = { 1,2,3,4,5,6,7,8 };
	cout << Qselect(a, 0, 7, 7) << endl;
	return 0;
}
