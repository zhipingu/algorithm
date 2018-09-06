#include"stdafx.h"
#include <iostream>
#include <map>
#include<vector>

using namespace std;

int max(int n1, int n2)
{
	return n1 > n2 ? n1 : n2;
}

int maxLength(int* arr, int n, int k) {
	if (arr == NULL)
		return 0;
	map<int, int> m;
	m.insert({ 0,-1 });//ºÜÖØÒª
	int len = 0;
	int sum = 0;
	for (int i = 0; i<n; i++) {
		sum += arr[i];
		if (m.find(sum - k) != m.end()) {
			len = max(i - m[sum - k], len);
		}
		//else
		{
			m.insert({ sum,i });
		}
	}
	return len;
}

int maxsub(int a[], int len)
{
	vector<int> sum(len, 0);
	sum[0] = a[0];
	int max = 0;
	for (int i = 1; i < len; ++i)
	{
		if (sum[i - 1] <= 0)sum[i] = a[i];
		else sum[i]=sum[i-1]+a[i];
		if (sum[i] > max) max = sum[i];
	}
	return max;

}
int main()
{
	//int arr[] = { 3,1,4,7,5,2,2,2,2,2,2 };
	/*int arr[] = { 2,3, 5, 4 };
	cout << maxLength(arr, sizeof(arr)/sizeof(arr[0]), 14) << endl;*/
	map<int, int> m;
	auto ret1=m.insert({ 3,5 });
	m[3] = 20;
	cout << m[4] << endl;
	/*auto ret2=m.insert({ 3,10 });
	auto ret3 = m.insert({ 5,10 });
	if (!ret1.second)
	{
		cout << "ret1" << endl;
	}
	if (!ret2.second)
	{
		cout << "ret2" << endl;
	}*/
	//if (!ret3.second)
	//{
	//	cout << "ret3" << endl;
	//}
	/*int a[] = { 1,-2,3,10,-4,7,2,-5 };
	cout << maxsub(a, sizeof(a) / sizeof(a[0])) << endl;*/
}