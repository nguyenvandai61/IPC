#pragma once
#include <iostream>
#include <cstring>
using namespace std;
class _Memory
{
protected:
	void* p;
	size_t size;
	bool createMode;

	string name;
	string info;
	void init(const char*, bool, size_t);
	virtual void* create(size_t);
	virtual void* open(size_t);
	virtual void close();
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

