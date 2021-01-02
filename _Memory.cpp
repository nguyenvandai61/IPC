#include "_Memory.h"

void _Memory::init(const char* name, bool createMode, size_t size=1024)
{
	
	this->name = name;
	this->createMode = createMode;
	allocate(size);
}

void* _Memory::create(size_t)
{
	this->size = size;
	return 0;
}

void* _Memory::open(size_t)
{
	return 0;
}

void _Memory::close()
{
}

void _Memory::reset()
{
	p = 0;
	memset(this->p, 0, this->size);
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


