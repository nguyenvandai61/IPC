#pragma once
#include <iostream>
#include "Process.h"
#include "Evaluate.h"
#include "SharedMemory.h"
class ProcessB : public Process
{
	Evaluate evaluate;
	const char* expression;
	double res = 0;
	double* response;

public:
	double calc();
	double calc(char[]);
	double calc(const char*);

	void run();
	void sendData(double*, const char*);
	void* getData(const char*);
	void process(const char* shmName);
	void reset(const char* shmName);
};
