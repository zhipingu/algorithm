// test4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>  
using namespace std;

class Point
{
public:
	Point()
	{
		x = 0;
		y = 0;
		counter++;
	}
	~Point()
	{
		counter--;
	}
	Point(float x, float y)
	{
		this->x = x;
		this->y = y;
		counter++;
	}
	void move(float x, float y)
	{
		this->x = x;
		this->y = y;
	}
	float getX()
	{
		return x;
	}
	float getY()
	{
		return y;
	}

public:
	static int counter;
private:
	float x, y;
};

int Point::counter = 0;

int main()
{
	Point *p1 = new Point(1, 1);
	Point *p2 = new Point(2, 2);
	Point *p3 = new Point(3, 3);

	cout << "ÒÑ´´½¨µÄµãÊýÊÇ:" << Point::counter << endl;

	delete p1;
	delete p2;
	delete p3;

	cout << Point::counter << endl;

	system("pause");
	return 0;
}
