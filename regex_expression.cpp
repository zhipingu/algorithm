// regex_expression.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<vector>
#include<regex>
using namespace std;


bool IsStrong(string s)
{

	/*if(s.size()<8)
	return false;

	vector<string> svec={"password","admin","qwerty","hello",
	"iloveyou","112233"};

	for(auto &r:svec)
	{
	if(s.find(r)!=string::npos)
	return false;
	}




	for(size_t cur=1;cur<s.size()-1;++cur)
	{
	size_t pre=cur-1,next=cur+1;
	if(((s[cur]>'a' && s[cur]<'z') || (s[cur]>'A' && s[cur]<'Z')) && ((s[pre]>'a' && s[pre]<'z') || (s[pre]>'A' && s[pre]<'Z'))
	&& ((s[next]>'a' && s[next]<'z') || (s[next]>'A' && s[next]<'Z')))
	{
	if(1==s[cur]-s[pre] && 1==s[next]-s[cur])
	return false;
	}
	}

	for(size_t cur=1;cur<s.size()-1;++cur)
	{
	size_t pre=cur-1,next=cur+1;
	if((s[cur]>'1' && s[cur]<'9') && (s[pre]>'1' && s[pre]<'9')
	&& (s[next]>'1' && s[next]<'9'))
	{
	if(s[cur]-s[pre]==s[next]-s[cur])
	return false;
	}
	}*/

	vector<string> svec1{ "[-!@#$%^&*():_=+[\\]{}\\\\,.<>/?]","[[:alnum:]]","[[:alpha:]]" };
	for (auto &tmp : svec1)
	{
		regex r(tmp, regex::icase);
		smatch result;
		if (!regex_search(s, result, r))
			return false;
	}

	return true;


}

void fun()
{
	int N;
	cin >> N;

	while (N-->0)
	{
		string s;
		cin >> s;

		if (IsStrong(s))
			cout << "yes" << endl;
		else
			cout << "no" << endl;
	}
}

int main()
{

	string s("123455635545adfj^&%");
	cout << IsStrong(s) << endl;
}


