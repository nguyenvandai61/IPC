#pragma once
#include <iostream>
#include "Process.h"
#include "Evaluate.h"

class ProcessB : public Process
{
	Evaluate evaluate;
public:
	double calc(char[]);
	double calc(const char*);
	void sendData(double value);

	void run();
};
