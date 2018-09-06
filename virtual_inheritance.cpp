// virtual_inheritance.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
/**
虚继承（虚基类）
*/

#include <iostream>
using namespace std;
// 基类A
class A
{
public:
	int dataA;
};

class B : virtual public A
{
public:
	int dataB;
};

class C : virtual public A
{
public:
	int dataC;
};

class DDD : public B, public C
{
public:
	int dataD;
};

int main()
{
	return 0;
}


