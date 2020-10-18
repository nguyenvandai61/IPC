#pragma once
#include <iostream> 
#include <stdio.h> 
// Create, Open and Destroy Shared memory segments that map to many processes
#include "_Pipe.h"
#include "ProcessA.h"
#include "ProcessB.h"

#include <thread>
using namespace std;

int main() {
	cout << "Bat dau\n";
	// Tao ra 1 duong ong
	//_Pipe* pipe = new _Pipe();
	SharedMemory* sharedMemory = new SharedMemory("SharedMemory1", true);
	// Pid cua ong
	//cout << pipe->getPid();
	// Tao 1 Process
	ProcessA* process1 = new ProcessA();
	/*cout << process1->getPid();
	pipe->attach(process1->getPid());
	cout << "Attach p1";*/

	ProcessB* process2 = new ProcessB();
	/*cout << process2->getPid();
	pipe->attach(process2->getPid());
	cout << "Attach p2";*/

	/*cout << process2->calc("6*5-3");*/
	//std::thread f1(&ProcessA::run, ProcessA());
	//std::thread f2(&ProcessB::run, ProcessB());

	//f1.join();
	//f2.join();
	process1->sendData("6*5-3*2", "SharedMemory1");
	process2->process("SharedMemory1");
	double res = *(double*)process1->getData("SharedMemory1");
	cout << "Day la ket qua: " << res;
	return 0;
}
