#pragma once
#include <stdio.h>
#include <iostream>

#include <process.h>
#include <sys/types.h>
#include <ctime>
#include <fcntl.h>
#include <Windows.h>
#include <processthreadsapi.h>
#include <queue>
#include "_Memory.h"

#define PIPE_SIZE	16384
#define BIG_PIPE_SIZE	(64*1024)

class _Pipe:public _Memory
{
	HANDLE mappingHandle;
	DWORD pidIn;
	DWORD pidOut;
	
	timespec lastAccessTime;
	timespec lastModifyTime;
public: 
	_Pipe();
	_Pipe(const char* name, bool createMode);
	~_Pipe();
	void attach();
	void detach();
	
	void* read();
	bool write(const char* data);
	bool write(double* data);
	void* create(size_t) override;
	void* open(size_t) override;
	void* close() override;
};

