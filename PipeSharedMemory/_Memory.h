#pragma once
#include <iostream>
using namespace std;
class _Memory
{
protected:
	void* p;
	bool createMode;

	string name;
	string info;
	void init(const char*, bool);
	virtual void* create(size_t);
	virtual void* open(size_t);
	virtual void* close();
	void reset();
public:

	virtual ~_Memory();
	void* allocate(size_t);
	void deallocate(void*);
	const char* toString() const
	{
		return info.c_str();
	}

};

