// longestSubStringWithoutDuplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<utility>

using namespace std;

int maxSubStrNoDup(const string &s,pair<int,int> &range)
{
	//cur相当于f(i),pre相当于f(i-1),f(i)=f(i-1)+1或d
	int cur = 0;
	//int pre = 0;
	int max = 0;

	int start = 0, end = 0;

	int position[26];
	for (int i = 0; i < 26; ++i)
		position[i] = -1;

	for (int i = 0; i < s.size(); ++i)
	{
		//position初始化为-1(-1位置不存在)代表所有字符都还没出现，同时，第一次出现时，
		//保证了d=i-positon=i+1一定大于pre,pre最大为0~i-1的个数i
		int d = i - position[s[i] - 'a'];//position为该字符上次出现的位置
		if (d <= cur)
		{
			cur = d;
			start = position[s[i] - 'a']+1;
			end = i;
		}
		else
		{
			++cur;
			if(i>0)
				++end;
		}

		if (cur > max)
		{
			max = cur;
			range = make_pair(start, end);

		}

		position[s[i]-'a'] = i;

	}

	return max;
}


int main()
{
	string s("aabbcdbefghigh");
	pair<int, int> range;

	cout << maxSubStrNoDup(s, range) << endl;
	for (int i = range.first; i <= range.second; ++i)
		cout << s[i];
	cout << endl;
    return 0;
}

