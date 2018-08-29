// cut_rope.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
using namespace std;

int cut_rope(int len)
{
	int *dp=new int[len + 1]{ 0,1,2,3};
	if (len < 2)return 0;
	if (len == 2) return 1;
	if (len == 3) return 2;
	for (int i = 4; i <= len; ++i)
	{
		int max = 0;
		for (int j = 1; j <= i/2; ++j)
		{
			if (dp[j] * dp[i - j] > max) max = dp[j] * dp[i - j];
		}
		dp[i] = max;
	}
	return dp[len];
}


int main()
{
	cout << cut_rope(5) << endl;
    return 0;
}

