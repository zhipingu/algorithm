// theMinKnum.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<set>
#include<functional>
#include<vector>
#include<queue>

using namespace std;


void theMinKnum(vector<int> &ivec, int k, multiset<int,greater<int>> &result)
{
	if (ivec.size() == 0 || k <= 0)
		return;

	for (auto beg = ivec.begin(); beg != ivec.end(); ++beg)
	{
		if (result.size() < k)
		{
			result.insert(*beg);
		}

		else
			//֮����Ϊmultiset<int,greater<int>> result,��Ϊ��С�����������һ����
			//���ö�λ��multiset��������һ�������˼Ӽ���������++��--��
			if (*beg < *(result.begin()))
			{
				result.erase(result.begin());
				result.insert(*beg);
			}
	}
}

void TheMinKNum(vector<int> &ivec, int k, priority_queue<int> &result)
{
	if (ivec.empty() || k <= 0)
		return;

	for (auto beg = ivec.begin(); beg != ivec.end(); ++beg)
	{
		if (result.size() < k)
			result.push(*beg);

		else if(*beg < result.top())
		{
			result.pop();
			result.push(*beg);
		}
	}
}


int main()
{
	vector<int> ivec{ 10,5,2,45,23,43,1,8,20 };
	//multiset<int, greater<int>> result;
	//theMinKnum(ivec, 6, result);
	priority_queue<int> result;
	TheMinKNum(ivec, 6, result);

	while (!result.empty())
	{
		cout << result.top() << endl;
		result.pop();
	}
    return 0;
}

