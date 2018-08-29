// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
using namespace std;

struct A
{
private:
	int value;
public:
	A(int n) { value = n; }
	A(A& other) { value = other.value; }
	void print() { cout << value << endl; }
};


int main()
{
	
	A a = 10;
	A b = a;
	b.print();


	system("pause");
    return 0;
}

