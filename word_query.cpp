// word_query.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<string>
#include<vector>
#include<new>
#include<fstream>
#include<sstream>
#include<memory>
#include<map>
#include<set>

using namespace std;

class QueryResult;

class TextQuery
{
public:
	TextQuery() :data(new vector<string>) {}
	TextQuery(shared_ptr<vector<string>> spv, map<string, shared_ptr<set<unsigned int>>> mss) :data(spv), linenum(mss) {}
	void push(const string &s);
	void set_linenum(const string &s,unsigned int n);
	QueryResult word_query(const string &s);
private:
	shared_ptr<vector<string>> data;
	map<string,shared_ptr<set<unsigned int>>> linenum;
}; 

void TextQuery::set_linenum(const string &s,unsigned int n)
{
	if (!linenum[s])
		linenum[s].reset(new set<unsigned int>);
	linenum[s]->insert(n);
}

void TextQuery::push(const string &s)
{
	data->push_back(s);
}

class QueryResult
{
public:
	friend void print(const QueryResult & qr);
	QueryResult() = default;
	QueryResult(const string &s, shared_ptr<set<unsigned int>> line, shared_ptr<vector<string>> text) :word(s), lineset(line), data(text) {}
private:
	string word;
	shared_ptr<set<unsigned int>> lineset;
	shared_ptr<vector<string>> data;

};

QueryResult TextQuery::word_query(const string &s)
{
	auto it = linenum.find(s);
	shared_ptr<set<unsigned int>> nolinenum(new set<unsigned int>);
	if (it != linenum.end())
	{
		return QueryResult(s, it->second, data);
	}
	else
		return QueryResult(s, nolinenum, data);
}


TextQuery build_map(const string &filename)
{
	ifstream infile(filename);
	TextQuery text;
	string line;
	unsigned int linenum = 0;
	while (getline(infile, line))
	{
		text.push(line);
		istringstream is(line);
		string word;
		while (is >> word)
		{
			text.set_linenum(word, linenum);
		}
		++linenum;
	}
	return text;

}

void print(const QueryResult & qr)
{
	cout << qr.word << " "<<"occurs times:"<<qr.lineset->size()<<endl;
	for (auto &linenum : *(qr.lineset))
		cout << "linenum:" << linenum + 1 <<" "<< *(qr.data->begin() + linenum) << endl;

}


int main()
{
	auto tq=build_map("infile.txt");
	auto qr=tq.word_query("auto");
	print(qr);
    return 0;
}

