#include<iostream>
#include<string>
#include<vector>
#include<regex>
using namespace std;
using namespace std::regex_constants;

bool IsStrong(string s)
{
/*
	if(s.size()<8)
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
	}
*/
//斜线\\\\，-(短横线)放在开头或者结尾
	vector<string> svec1{"[-!@#[\\]$%^&*'()\\\\_=+{},.<>/?]","[[:alnum:]]"};	
//	vector<string> svec1{"[[:alnum:]]","[[:alpha:]]"}; 
//	vector<string> svec1{"[!@#$%^&*()_-={},.]","[[:alpha:]]","[0-9]"};	

	try
	{
		regex r;
		smatch result;
		for(auto &tmp:svec1)
		{	
			r.assign(tmp,regex::icase);
			if(!regex_search(s,result,r))
				return false;
		}

		return true;
	}
	catch(regex_error e)
	{
			cout<<e.what()<<"\ncode:"<<e.code()<<endl;
	}
	return false;
}

void fun()
{
	int N;
	cin>>N;

	while(N-->0)
	{
		string s;
		cin>>s;

		if(IsStrong(s))
			cout<<"yes"<<endl;
		else 
			cout<<"no"<<endl;
	}
}

int main(int argc,char **argv)
{
	if(argc!=2)
		return 0;

	string s(argv[1]);
	string fmt("$1-$2-$3");
	cout<<IsStrong(s)<<endl;
	//regex r("(\\d)([[:alpha:]]+)([*&%$#@])");
	//cout<<regex_replace(s,r,fmt)<<endl;
	return 0;
}
