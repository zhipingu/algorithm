// virtual_inheritance.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>

using namespace std;

class Base1 {
public:
	Base1();
	virtual ~Base1();
	virtual void speackClearly();
	virtual Base1* clone() const;
protected:
	float data_Base1;
};

class Base2 {
public:
	Base2();
	virtual ~Base2();
	virtual void mumble();
	virtual Base2* clone() const;
protected:
	float data_Base2;
};

class Derived : public Base1, public Base2 {
public:
	Derived();
	virtual ~Derived();
	virtual Derived* clone() const;
protected:
	float data_Derived;
};

class A
{
public:
	int dataA;
	virtual void fun() { cout << "AAAA" << endl; }
};

class B : virtual public A
{
public:
	int dataB;
	virtual void fun1() { cout << "BBBB" << endl; }
};

class C : virtual public A
{
public:
	int dataC;
	virtual void fun2() { cout << "CCCC" << endl; }
};

class DDDDD : public B, public C
{
public:
	int dataD;
	virtual void fun1() { cout << "DDDD" << endl; }
	virtual void fun2() { cout << "DDDD" << endl; }
};
int main(void)
{
	cout << "hello world" << endl;
	return 0;
}

