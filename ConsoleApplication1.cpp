// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<stdlib.h>

using namespace std;

void insert_sort(int a[], int len)
{
	int i, j, tmp;
	for (j = 1; j < len; j++)
	{
		tmp = a[j];
		i = j - 1;
		while (i >= 0 && tmp < a[i])
		{
			a[i + 1] = a[i];
			i--;
		}
		a[i + 1] = tmp;
	}
}

int fun()
{
	int n;
	cout << "please input n:" << endl;
	cin >> n;
	int min=0, max=0;
	int cnt1 = 0;//记录小于3的个数
	int cnt2 = 0;//记录小于6的个数
	if (n != 6)cout << "please input again:" << endl;
	
	int *c= (int *)malloc(sizeof(int)*n);
	if (!c)
	{
		perror("tmp malloc fail");
		exit(1);
	}
	
	int i = 0;
	cout << "请输入n个数" << endl;
	for (i = 0; i < n; i++)
	{
		cin >> c[i];
		if (c[i] <= 2)cnt1++;
		if (c[i] <= 5)cnt2++;
	}
	if (cnt1 > 0 && cnt2 >= 3)
	{
		insert_sort(c, n);
		if (cnt2 == 3)
		{
			if (c[0] != 2)min = c[0] * 100000 + c[3]* 10000 + c[1]  * 1000 + c[4]  * 100 + c[2] * 10 + c[5];
			else cout << "invalid input" << endl;
		}
		else 
			if (cnt2 == 4)
			{
				/*if (c[0] != 2)min= c[0] * 100000 + c[1] * 10000 + c[2] * 1000 + c[4] * 100 + c[3] * 10 + c[5];
				else 
					if(c[1]==3)min = c[0] * 100000 + c[1] * 10000 + c[2] * 1000 + c[4] * 100 + c[3] * 10 + c[5];
					else cout << "invalid input" << endl;
				*/
				//如果c[0]==2,c[1],c[2],c[3]一定为3，4，5，所以不用讨论
				min = c[0] * 100000 + c[1] * 10000 + c[2] * 1000 + c[4] * 100 + c[3] * 10 + c[5];
			}
			else
				{
					//c[0]不可能等于2，否则最多只有2，3，4，5四个数小于6
					min = c[0] * 100000 + c[1] * 10000 + c[2] * 1000 + c[3] * 100 + c[4] * 10 + c[5];
				}
				
	}
	else
	{
		cout << "invalid input" << endl;
	}
	return min;
}

int main()
{
	int result;
	result=fun();
	printf("%d\n", result);
    return 0;
}

