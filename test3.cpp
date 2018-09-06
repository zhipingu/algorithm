// test3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<random>
#include<stack>
#include<iostream>
#include<cmath>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>
#include<functional>
using namespace std;
using namespace std::placeholders;


class Blob
{
public:
	Blob(const Blob&b) :tok(b.tok) { copyunion(b);}
	Blob() :tok(INT), a(0) {}
	Blob& operator=(Blob &b)
	{
		if (tok == STR&&b.tok != STR)s.~string();
		else if(tok == STR&&b.tok == STR) s = b.s;
		else copyunion(b);
		tok = b.tok;
		return *this;
	}
	Blob& operator=(int i)
	{
		if (tok == STR)s.~string();
		a = i;
		tok = INT;
		return *this;
	}
	Blob& operator=(double i)
	{
		if (tok == STR)s.~string();
		d = i;
		tok = DOU;
		return *this;
	}
	Blob& operator=(string i)
	{
		if (tok == STR)s=i;
		else new(&s)string(i);
		tok = STR;
		return *this;
	}
	~Blob() { if (tok == STR)s.~string(); }
	void gettok() { if(tok==0)cout << "INT" << endl; if (tok == 1)cout << "STR" << endl; if (tok == 2)cout << "DOU" << endl;}
	void copyunion(const Blob&b)
	{
		switch (b.tok)
		{
			case INT:
			{
				a = b.a;
				break;
			}
			case STR:
			{
				new (&s)string(b.s);
				break;
			}
			case DOU:
			{
				d = b.d;
				break;
			}
		}
	}
private:
	enum TOK{INT,STR,DOU} tok;
	union
	{
		int a;
		string s;
		double d;
	};
};
class Base
{
public:
	char *p;
};
class A
{
public:
	void fund() {}
	virtual void fun1() {}
	virtual void func() {}
};

class B
{
	virtual void fun2() {}
};

class C: public A
{
	//void fun1() {}
};

const class nullptr_tt
{
public:
	template<class T>
	inline operator T*() const  //隐式转化
	{
		cout <<typeid(T*).name() << endl;
		return 0;
	}

	template<class C, class T>  //隐式转化
	inline operator T C::*() const
	{
		cout << typeid(T C::*).name() << endl;
		return 0;
	}

	void operator&() const = delete;
}a;

char *strtok_new(char * string, char const * delimiter) {
	static char *source = NULL;
	char *p, *riturn = NULL;
	if (string != NULL)         source = string;
	if (source == NULL)         return NULL;

	if ((p = strpbrk(source, delimiter)) != NULL) {
		*p = 0;
		riturn = source;
		source = ++p;
	}
	return riturn;
}
int main()
{
	/*int i = 9;
	Base pb;
	char * A::*P = a;*/
	char src[] = "abcde kfd";
	char *s2 = " ";
	char *p = strpbrk(src, s2);
	cout << (*(++p)='5') << endl;
	//cout<<strtok_new("abcde dfd", " ")<<endl;
	/*int *p1 =a;
	pb.p = a;
	cout << sizeof(a) << endl;*/
	return 0;
}

