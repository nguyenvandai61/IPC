#pragma once
#include <iostream> 
#include <stdio.h> 
// Create, Open and Destroy Shared memory segments that map to many processes
#include "_Pipe.h"
#include "ProcessA.h"
#include "ProcessB.h"

#include <thread>
using namespace std;
//
//// Create and Open Shared memory
//SharedMemory shm_obj
//(	
//	create_only                  //only create
//	, "shared_memory"              //name
//	, read_write                   //read-write mode
//);
//
//SharedMemory shm_obj
//(
//	open_or_create               //open or create
//	, "shared_memory"              //name
//	, read_only                    //read-only mode
//);
//
//SharedMemory shm_obj
//(
//	open_only                    //only open
//	, "shared_memory"              //name
//	, read_write                   //read-write mode
//);
//
//// Destroy shared memory;
//SharedMemory::remove("shared_memory");
//
//shm_obj.truncate(10000);
//
//int main()
//{
//	/*cout << "Write Data : ";
//
//	printf("Data written in memory:\n");
//	char exp[] = "5+6*2-3\0";
//	Evaluate evaluate;
//	double res = evaluate.calc(exp);
//	printf(exp);
//	printf("%lf\n", res);*/
//
//
//
//
//	return 0;
//}


int main() {
	cout << "Bat dau";
	// Tao ra 1 duong ong
	_Pipe* pipe = new _Pipe();
	// Pid cua ong
	cout << pipe->getPid();
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
	process1->sendData("6*5-3");
	return 0;
}
