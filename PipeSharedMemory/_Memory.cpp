#include "_Memory.h"

void _Memory::init(const char* name, bool createMode)
{
	reset();
	this->name = name;
	this->createMode = createMode;
}

void* _Memory::create(size_t)
{
	return 0;
}

void* _Memory::open(size_t)
{
	return 0;
}

void* _Memory::close()
{
	return 0;
}

void _Memory::reset()
{
	p = 0;
	createMode = false;
}

_Memory::~_Memory()
{
	close();
}

void* _Memory::allocate(size_t size)
{

	return createMode ? create(size):open(size);
}

void _Memory::deallocate(void*)
{
	close();
}


