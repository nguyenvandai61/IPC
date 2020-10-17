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

#define PIPE_SIZE	16384
#define BIG_PIPE_SIZE	(64*1024)
class PipeSingle {

};

class PipeBuf {
	int currentSize;
	int size;
	std::queue<const char*> buffChar;
	std::queue<double> buffRes;

public:
	PipeBuf();
	std::queue<const char*> getBuffChar();
	std::queue<double> getBuffRes();
	void pushDataChar(const char* data);
	void pushDataRes(double data);

	const char* popDataChar();
	double popDataRes();

};
class _Pipe
{
	DWORD pidIn;
	DWORD pidOut;
	
	PipeBuf pipeBuff;
	timespec lastAccessTime;
	timespec lastModifyTime;
public: 
	_Pipe();
	void attach(unsigned long pid);
	void detach();
	
	void initBuf();
	const char* readChar();
	double readRes();
	void writeRes(double value);
	void writeChar(const char* str);
	unsigned long getPid();
};

