// longestSubStringWithoutDuplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<utility>

using namespace std;

int maxSubStrNoDup(const string &s,pair<int,int> &range)
{
	//cur�൱��f(i),pre�൱��f(i-1),f(i)=f(i-1)+1��d
	int cur = 0;
	//int pre = 0;
	int max = 0;

	int start = 0, end = 0;

	int position[26];
	for (int i = 0; i < 26; ++i)
		position[i] = -1;

	for (int i = 0; i < s.size(); ++i)
	{
		//position��ʼ��Ϊ-1(-1λ�ò�����)���������ַ�����û���֣�ͬʱ����һ�γ���ʱ��
		//��֤��d=i-positon=i+1һ������pre,pre���Ϊ0~i-1�ĸ���i
		int d = i - position[s[i] - 'a'];//positionΪ���ַ��ϴγ��ֵ�λ��
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

