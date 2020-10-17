#include "SharedMemory.h"

SharedMemory::SharedMemory()
{

}
SharedMemory::SharedMemory(const char* name, bool createMode)
{
	init(name, createMode);
}

SharedMemory::~SharedMemory()
{
	
}

void* SharedMemory::read()
{
	void* pt = open(1024);
	char* pchar = (char*)pt;
	for (int i = 0; i < 5; i++) {
		printf("Data[%d] = %3d\n", i, pchar[i]);
	}
	return pchar;
}

bool SharedMemory::write(const char* data)
{
	if (data == nullptr) 
		return false;
	void* p = open(1024);
	CopyMemory((PVOID)p, data, strlen(data)* sizeof(char));
	cout << "Hello";
	return true;
}





void* SharedMemory::create(size_t bufsize)
{
	HANDLE pageFile = INVALID_HANDLE_VALUE;
	LPSECURITY_ATTRIBUTES securAttrs = NULL;
	DWORD access = PAGE_READWRITE;
	DWORD sizeHigh = NULL;
	DWORD sizeLow = bufsize;
	mappingHandle = CreateFileMappingA(pageFile, securAttrs, access, sizeHigh, sizeLow, name.c_str());
	if (mappingHandle == NULL) {
		perror("Error");
		return 0;
	}
	p = MapViewOfFile(mappingHandle, FILE_MAP_ALL_ACCESS, 0, 0, bufsize);
	if (!p) {
		perror("err");
		return 0;
	}
	return NULL;
}

void* SharedMemory::open(size_t bufsize) {
	DWORD access = FILE_MAP_ALL_ACCESS;
	BOOL inherit = FALSE;
	mappingHandle = OpenFileMapping(access, inherit, name.c_str());

	if (mappingHandle == NULL || mappingHandle == INVALID_HANDLE_VALUE)
	{
		perror("OpenFileMapping failed, ");
		return 0;
	}
	p = MapViewOfFile(mappingHandle, FILE_MAP_ALL_ACCESS, 0, 0, bufsize);
	if (!p)
	{
		perror("MapViewOfFile");
		return 0;
	}
	return p;
}

void* SharedMemory::close()
{
	if (p)
		UnmapViewOfFile(p);
	if (mappingHandle > 0) CloseHandle(mappingHandle);
	return false;
}
