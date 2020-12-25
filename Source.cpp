#pragma once
#include <iostream> 
#include <stdio.h> 
#include <windows.h>
#include <tchar.h>


#include "_Pipe.h"
#include "ProcessA.h"
#include "ProcessB.h"

using namespace std;

int main(int argc, TCHAR *argv[]) {
	cout << "Bat dau\n";
	SharedMemory* sharedMemory = new SharedMemory("SharedMemory1", true);
	ProcessA* process1 = new ProcessA();

	ProcessB* process2 = new ProcessB();
	process1->sendData("6*5-3*2", "SharedMemory1");
	process2->process("SharedMemory1");
	double res = *(double*)process1->getData("SharedMemory1");
	cout << "Day la ket qua: " << res;
	sharedMemory->reset();
	process1->sendData("8*3-34", "SharedMemory1");
	process2->process("SharedMemory1");
	res = *(double*)process1->getData("SharedMemory1");
	cout << "Day la ket qua: " << res;
	
	
	return 0;
}
