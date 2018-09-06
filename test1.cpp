// test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<io.h>
#include<string>
#include<vector>
#include<regex>
#include<iostream>

using namespace std;

void getfile(string filepath, vector<string> &files)
{
	struct _finddata_t fileinfo;
	auto handle = _findfirst(string(filepath).append("\\*").c_str(), &fileinfo);
	if (handle == -1)
	{
		perror("_findfirst fail");
		exit(1);
	}
	do
	{
		if (fileinfo.attrib & _A_SUBDIR)
		{
			//cout << string(filepath) + "\\" + string(fileinfo.name) + "\\*" << endl;
			if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				getfile(string(filepath) + "\\" + string(fileinfo.name), files);
		}
		else
			files.push_back(string(filepath) + "\\" + fileinfo.name);
	} while (_findnext(handle, &fileinfo) == 0);
	_findclose(handle);
}

int main()
{
	vector<string> files;
	string filepath("F:\\aaa");
	getfile(filepath, files);
	string pattern("([[:alnum:]]+)\\.(txt|doc)$");
	regex r(pattern, regex::icase);
	string fmt("$1&$2");
	vector<string> svec(20,"kddddddddddddddddddddddd");
	string s;
	auto it = svec.begin();
	for (int i = 0; i != files.size(); ++i)
	{
		//cout<<regex_replace(files[i], r, fmt)<<endl;
		regex_replace(files[i].begin(),files[i].begin(),files[i].end(), r, fmt);
	}
	for (auto &r : files)
		cout << r << endl;

	/*regex r("(ei)", regex::icase);
	string fmt("EI");
	string s("kdfjdkeidkfdl");
	vector<string> svec{ "dkfjkeidklfj","lllleillll","aaaaeiaaaa" };
	for(int i=0;i!=svec.size();++i)
	regex_replace(svec[i].begin(), svec[i].begin(), svec[i].end(), r, fmt);
	for(auto &r:svec)
	cout << r << endl;*/
    return 0;

	/*char buf[20];
	const char *first = "axayaz";
	const char *last = first + strlen(first);
	std::regex rx("a");
	std::string fmt("A");
	std::regex_constants::match_flag_type fonly =
		std::regex_constants::format_first_only;

	*std::regex_replace(&buf[0], first, last, rx, fmt) = '\0';
	std::cout << "replacement == " << &buf[0] << std::endl;

	*std::regex_replace(&buf[0], first, last, rx, fmt, fonly) = '\0';
	std::cout << "replacement == " << &buf[0] << std::endl;

	std::string str("adaeaf");
	std::cout << "replacement == "
		<< std::regex_replace(str, rx, fmt) << std::endl;

	std::cout << "replacement == "
		<< std::regex_replace(str, rx, fmt, fonly) << std::endl;*/
	/*return 0;*/
}

