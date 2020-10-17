#pragma once
#include <stdio.h>
#include <sys/types.h>
#include <cstring>
#include <Windows.h>
#include "_Memory.h"

class SharedMemory: public _Memory
{	
	HANDLE mappingHandle;
	bool isWritable;
	/*pid_t lastOperationPid;
	pid_t createdPid;
	*/
	/*int64_t total;
	int64_t used;
	int64_t free;*/

	//Permission permission;
;

public: 
	SharedMemory();
	SharedMemory(const char* name, bool createMode);
	~SharedMemory();


	void* read();
	bool write(const char* data);
	
	void* create(size_t) override;
	void* open(size_t) override;
	void* close() override;
};
