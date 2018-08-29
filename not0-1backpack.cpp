// not0-1backpack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>  
using namespace std;

double KnapSack(int w[], int v[],int C)
{
	double x[10] = { 0 };           //��Ʒ�ɲ���װ��  
	double maxValue = 0;
	int i = 0;
	for (; w[i] < C; i++)
	{
		x[i] = 1;                 //����Ʒiװ�뱳��  
		maxValue += v[i];
		C = C - w[i];             //����ʣ������  
	}
	x[i] = (double)C / w[i];        //��Ʒiװ��һ����  
	maxValue += x[i] * v[i];
	return maxValue;              //���ر�����õļ�ֵ  
}


int main()
{
	int w[3] = { 10, 30, 20 }, v[3] = { 50, 120, 60 };
	int C = 50;
	double value = KnapSack(w, v, C);
	cout << "������õ�����ֵ�ǣ�" << value << endl;
	return 0;
}


