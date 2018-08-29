// permutation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>

using namespace std;

void permutationCore(char *a, char *beg)
{
	static int cnt = 0;
	if (*beg == '\0')
	{
		cout <<++cnt<<"£º"<< a << endl;

	}
		
	for (char* tmp = beg; *tmp != '\0'; ++tmp)
	{
		if (beg == tmp || *beg != *tmp)
		{
			swap(*beg, *tmp);

			permutationCore(a, beg + 1);

			swap(*beg, *tmp);
		}
	}
}

void permutation(char *a)
{
	if (!a)
	{
		return;
	}

	permutationCore(a,a);
}


int main()
{
	char a[] = "abcd";
	permutation(a);
    return 0;
}

