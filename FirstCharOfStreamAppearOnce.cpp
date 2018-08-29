// FirstCharOfStreamAppearOnce.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<vector>
#include<limits>

using namespace std;
class charStream
{
public:
	charStream() :index(0)
	{
		for (int i = 0; i < 256; ++i)
			position[i] = -1;
	}
	void insert(char ch)
	{
		if (position[ch] == -1)
			position[ch] = index;
		else
			if (position[ch] >= 0)
				position[ch] = -2;

		++index;
	}

	char FirstAppearOnce()
	{
		char ch;
		int minIndex = numeric_limits<int>::max();

		for (char i = 0; i < 256; ++i)
		{
			if (position[i] >= 0 && position[i] < minIndex)
			{
				ch = i;
				minIndex = position[i];
			}
		}
		return ch;
	}
private:
	int index;
	int position[256];//-1?
};

int main()
{
	charStream cs;
	char ch[] = "abcda";

	char *pch = ch;
	while (*(pch++) != '\0')
	{
		cs.insert(*pch);
	}

	cout<<cs.FirstAppearOnce() << endl;
	return 0;
}

