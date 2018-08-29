// max_min_in_queue.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <deque>
#include <queue>
using namespace std;

class custom_queue
{
public:
	int front()
	{
		return data.front();
	}

	int back()
	{
		return data.back();
	}
	void pop()
	{
		if (data.front() == max.front())
			max.pop_front();
		if (data.front() == min.front())
			min.pop_front();

		data.pop();
	}

	void push(int key)
	{
		data.push(key);
		while (!max.empty() && key > max.back())
			max.pop_back();
		while (!min.empty() && key < min.back())
			min.pop_back();

		max.push_back(key);
		min.push_back(key);
	}

	int findMin()
	{
		return min.front();
	}

	int findMax()
	{
		return max.front();
	}
private:
	queue<int> data;
	deque<int> max;
	deque<int> min;
};


int main()
{
	int a[] = { 4,2,15,6,7,0,8,15,2,12 };
	int len = sizeof(a) / sizeof(a[0]);
	custom_queue cq;
	for (int i = 0; i < len; ++i)
	{
		cout << a[i] << " ";
	}
	cout << endl;

	for (int i = 0; i < len; ++i)
	{
		cq.push(a[i]);
		cout << "max:" << cq.findMax()<<" ";
		cout << "min:" << cq.findMin()<<" ";
		cout << endl;
	}
	cout << endl;

	for (int i = 0; i < len; ++i)
	{
		cout << "max:" << cq.findMax()<<" ";
		cout << "min:" << cq.findMin()<<" ";
		cout << endl;
		cq.pop();
	}
    return 0;
}

