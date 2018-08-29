// minCombineNumOfArray.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<vector>
#include<iterator>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<algorithm>

using namespace std;

bool compare(const char *str1, const char *str2)
{
	char *Str1Str2 = new char[50];
	strcpy(Str1Str2, str1);
	strcat(Str1Str2, str2);

	char *Str2Str1 = new char[50];
	strcpy(Str2Str1, str2);
	strcat(Str2Str1, str1);

	//	return strcmp(Str1Str2,Str2Str1);
	if (strcmp(Str1Str2, Str2Str1) == -1 )
	{
		delete[] Str1Str2;
		delete[] Str2Str1;
		return true;
	}

	delete[] Str1Str2;
	delete[] Str2Str1;
	return false;
}

void MinNumber(int a[], int len)
{
	char **strNum = new char *[len];
	for (int i = 0; i<len; ++i)
	{
		strNum[i] = new char[11];
		sprintf(strNum[i], "%d", a[i]);
	}

	/*cout << "begin:" << endl;
	for (int i = 0; i<len; ++i)
		printf("%s", strNum[i]);
	printf("\n");*/


	sort(strNum, strNum + len, compare);

	cout << "after" << endl;
	for (int i = 0; i<len; ++i)
		printf("%s", strNum[i]);
	printf("\n");
}

int main()
{
	int a[] = { 12,45,34,11,233 };
	int len = sizeof(a) / sizeof(a[0]);
	MinNumber(a, len);
	/*cout << "=========" << endl;
	cout << compare("233", "34") << endl;*/

	/*const char *str[] = { "12","45","34","11","233" };
	int len = sizeof(str) / sizeof(str[0]);
	sort(str, str + len, compare);
	for (int i = 0; i < len; ++i)
		cout << str[i] << " ";
	cout << endl;*/
	return 0;
}

