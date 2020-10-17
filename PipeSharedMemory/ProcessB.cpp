#include "ProcessB.h"

double ProcessB::calc(char exp[])
{
	return evaluate.calc(exp);
}

double ProcessB::calc(const char* exp)
{
	return evaluate.calc(exp);
}

void ProcessB::run()
{
	for (int i = 3000; i < 6000; i++)
		std::cout << i << "\t";
}