// UglyNum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<algorithm>

using namespace std;

int getUglyNumOfIndex(int index)
{
	
	int *uglyNum = new int[index+1];
	uglyNum[1] = 1;
	int curIndex = 2;

	int multiply2Index = 1;
	int multiply3Index = 1;
	int multiply5Index = 1;

	while (curIndex <= index)
	{
		uglyNum[curIndex] = min(uglyNum[multiply2Index] * 2, uglyNum[multiply3Index] * 3);
		uglyNum[curIndex] = min(uglyNum[curIndex], uglyNum[multiply5Index] * 5);

		while (uglyNum[multiply2Index] * 2 <= uglyNum[curIndex])
			++multiply2Index;
		while (uglyNum[multiply3Index] * 3 <= uglyNum[curIndex])
			++multiply3Index;
		while (uglyNum[multiply5Index] * 5 <=uglyNum[curIndex])
			++multiply5Index;

		++curIndex;
	}

	for (int i = 1; i <= index; ++i)
		cout << uglyNum[i] << " ";
	cout << endl;

	return uglyNum[index];

}


int main()
{
	cout << "result:"<<getUglyNumOfIndex(1500) << endl;
    return 0;
}

