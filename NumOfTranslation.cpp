// NumOfTranslation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string>

using namespace std;

int NumOfTranslation(int n)
{
	if (n < 0)
		return -1;
	string s = to_string(n);
	int len = s.size();
	int *count = new int[len]();
	count[len - 1] = 1;

	for (int i = len - 2; i >= 0; --i)
	{
		int digit1 = s[i] - '0';
		int digit2 = s[i + 1] - '0';

		if (i < len - 2)
		{
			if (digit1 * 10 + digit2 >= 10 && digit1 * 10 + digit2 <= 36)
				count[i] = count[i + 1] + count[i + 2];
			else
				count[i] = count[i + 1];
		}
		else
		{
			if (digit1 * 10 + digit2 >= 10 && digit1 * 10 + digit2 <= 25)
				count[i] = count[i + 1] + 1;
			else
				count[i] = count[i + 1];
		}
	}

	int result = count[0];
	delete[] count;

	return result;
}


int main()
{
	cout << NumOfTranslation(121) << endl;
    return 0;
}

