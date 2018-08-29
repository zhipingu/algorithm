// maxValueOfGift.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<algorithm>

using namespace std;

int maxValue(int *value, int rows, int cols)
{
	if (!value || rows <= 0 || cols <= 0)
		return 0;

	int *maxValue=new int[cols]();
	for(int i=0;i<rows;++i)
		for (int j = 0; j < cols; ++j)
		{
			int left = 0, up = 0;
			if (i > 0)
				up = maxValue[j];
			if (j > 0)
				left = maxValue[j - 1];

			maxValue[j] = max(left, up) + value[i*cols + j];
		}

	int result = maxValue[cols - 1];
	delete[] maxValue;

	return result;

}


int main()
{
	int value[] = { 1,12,3,4,5,6,17,18,9,10,11,12,13,14,15 };
	cout << maxValue(value, 3, 5) << endl;
    return 0;
}

