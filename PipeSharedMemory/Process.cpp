#include "Process.h"
#include "Process.h"

Process::Process()
{
	pid = GetCurrentProcessId();
	
}


DWORD Process::getPid()
{
	return this->pid;
}
