// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<numeric>
#include<iterator>
#include<vector>
#include<string>
#include<list>
#include<map>
#include<set>
#include<memory>
#include<new>

using namespace std;

class HasPtr
{
public:
	HasPtr() :ps(new string()), use(new unsigned(1)) {};
	HasPtr(const HasPtr &h) :ps(h.ps), use(h.use) { (*use)++; }
	HasPtr(const string &s) :ps(new string(s)), use(new unsigned(1)){}
	HasPtr& operator=(const HasPtr &h);
	~HasPtr();
	string &get_data()const { return *ps; };
private:
	string *ps;
	unsigned *use;
};
HasPtr::~HasPtr()
{
	if (--*use == 0)
	{
		delete ps;
		delete use;
	}
}

HasPtr& HasPtr::operator=(const HasPtr &h)
{
	++*h.use;
	if (--*use == 0)
	{
		delete ps;
		delete use;
	}
	ps = h.ps;
	use = h.use;
	return *this;
}

class StrVec
{
public:
	StrVec() :element(nullptr), first_free(nullptr), cap(nullptr) {}
	StrVec(const string &s);
	StrVec(const StrVec &sv);
	StrVec& operator=(StrVec &&rhs);
	~StrVec();
	unsigned size()const { return first_free - element; }
	unsigned capacity()const { return cap - element; }
	void push_back(const string &s);
	string *begin()const { return element; }
	string *end()const { return first_free; }
	
private:
	void check_and_alloc() { if (first_free == cap) reallocate(); };
	void free();
	void reallocate();
	pair<string *, string *> alloc_and_copy(const string*, const string *);
	static allocator<string> alloc;
	string *element;//指向初始化且构造内存的首元素
	string *first_free;//指向最后一个构造内存之后的下一位置
	string *cap;//指向分配的内存末尾之后的位置
};
allocator<string> StrVec::alloc;
void StrVec::push_back(const string &s)
{
	check_and_alloc();
	alloc.construct(first_free++, s);
}
StrVec::StrVec(const StrVec &sv)
{
	auto newpair = alloc_and_copy(sv.element, sv.first_free);
	element = newpair.first;
	first_free = newpair.second;
	cap = first_free;
	cout << "StrVec(const StrVec &sv)" << endl;
}

StrVec::StrVec(const string &s)
{
	auto newp = alloc.allocate(1);
	alloc.construct(newp, s);
	element = newp;
	first_free = cap=element + 1;
	cout << "StrVec(const string &s)"<<endl;
}
StrVec& StrVec::operator=(StrVec &&rhs)
{
	auto newpair = alloc_and_copy(rhs.begin(), rhs.end());
	free();
	element = newpair.first;
	first_free = cap=newpair.second;
	cout << "StrVec::operator=(const StrVec &rhs)" << endl;
	return *this;
}
pair<string *, string *> StrVec::alloc_and_copy(const string *beg, const string *end)
{
	auto newp = alloc.allocate(end - beg);
	auto new_first_free=uninitialized_copy(beg, end, newp);
	cap = new_first_free;
	return{ newp,new_first_free };
}
StrVec::~StrVec()
{
	free();
}
void StrVec::free()
{
	if (element)
	{
		
		for_each(element, first_free, [](const string &s) {alloc.destroy(&s); });
		//cout << "======" << endl;
		alloc.deallocate(element, cap - element);
		
	}
}

void StrVec::reallocate()
{
	auto newcapacity = size() ? size() * 2 : 1;
	auto newp=alloc.allocate(newcapacity);
	auto new_first_free=uninitialized_copy(make_move_iterator(element), make_move_iterator(first_free), newp);
	free();
	first_free = new_first_free;
	cap = newp +newcapacity;
	element = newp;
}

int main()
{
	
	//StrVec sv3("abcd");
	//sv3.push_back("khhkh");
	//sv3.push_back("uuuuu");
	StrVec sv4 = "dkfljdk";
	for(auto &r:sv4)
	cout << r << endl;
	cout << sv4.size() << endl;
	cout << sv4.capacity() << endl;
	return 0;
}

