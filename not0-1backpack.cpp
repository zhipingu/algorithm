// not0-1backpack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>  
using namespace std;

double KnapSack(int w[], int v[],int C)
{
	double x[10] = { 0 };           //物品可部分装入  
	double maxValue = 0;
	int i = 0;
	for (; w[i] < C; i++)
	{
		x[i] = 1;                 //将物品i装入背包  
		maxValue += v[i];
		C = C - w[i];             //背包剩余容量  
	}
	x[i] = (double)C / w[i];        //物品i装入一部分  
	maxValue += x[i] * v[i];
	return maxValue;              //返回背包获得的价值  
}


int main()
{
	int w[3] = { 10, 30, 20 }, v[3] = { 50, 120, 60 };
	int C = 50;
	double value = KnapSack(w, v, C);
	cout << "背包获得的最大价值是：" << value << endl;
	return 0;
}


