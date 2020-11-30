#pragma once
#include <iostream>
#include "Process.h"
#include "SharedMemory.h"
#include <thread>

class ProcessA: public Process
{
public:
	void GUI();
	void run();
	void sendData(const char* , const char*);
	void sendDataPipe(const char*, const char*);
	void* getData(const char*);
	void* getDataPipe(const char*);
};

