
#include "stdafx.h"
//#include<vld.h>
#include<fstream>
#include<memory>
#include<string>
#include<algorithm>  
#include<vector>  
#include<utility>
#include<iostream>  

using namespace std;

class A
{
private:
	int x;
	int y;
public:
	A(int a,int b):x(a),y(b)
	{
	}
	A() = default;
	virtual void fun4() {}
	virtual void print()
	{
		cout << "x=" << x << endl << "y=" << y << endl;
	}
};

class BBB
{
	virtual void fun() {}
	virtual void fun1() {}
	virtual void fun2() {}

};

class CCC :public A, public BBB
{
	virtual void fun5() {}
	virtual void fun() {}
	virtual void print() {}
	int ff;
};
int main()
{
	A a1(10,20);
	A a2(30,40);
	cout << hex << *(int *)&a1 << endl;
	cout << hex << *(int *)&a2 << endl;
	return 0;
	///*int *p1 = (int *)malloc(sizeof(int) * 10);
	//for (int i = 0; i < 10; ++i)
	//	*(p1 + i) = i;

	//int *p2 = (int *)malloc(sizeof(int) * 10);
	//for (int i = 0; i < 10; ++i)
	//	*(p2 + i) = i;*/
	///*free(p1);*/
}