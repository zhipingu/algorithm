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
			//之所以为multiset<int,greater<int>> result,因为从小到大排序，最后一个数
			//不好定位，multiset迭代器不一定定义了加减法（非自++，--）
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

