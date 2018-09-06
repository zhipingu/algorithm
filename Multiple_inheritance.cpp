// test2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
using namespace std;

class Base1
{
public:
	void fun1() { cout << "Base1" << endl; }
};

class Base2
{
public:
	void fun1() { cout << "Base2" << endl; }

};

class Derived:public Base1,public Base2
{
public:
	//using Base2::fun1;
	void fun2();
};

void Derived::fun2()
{
	cout << "Derived" << endl;
}

int main()
{
	Derived d;
	d.fun2();
	cout << sizeof(d) << endl;
    return 0;
}

