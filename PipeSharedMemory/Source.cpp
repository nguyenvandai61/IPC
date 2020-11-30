#pragma once
#include <iostream> 
#include <stdio.h> 
#include <windows.h>
#include <tchar.h>


#include "_Pipe.h"
#include "ProcessA.h"
#include "ProcessB.h"

#include <thread>
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
	
	// Tạo một tiến trình mới
	//STARTUPINFO si;
	//PROCESS_INFORMATION pi;

	//ZeroMemory(&si, sizeof(si));
	//si.cb = sizeof(si);
	//ZeroMemory(&pi, sizeof(pi));

	//if (argc != 2)
	//{
	//	printf("Usage: %s [cmdline]\n", argv[0]);
	//	return 0;
	//}

	//// Start the child process. 
	//if (!CreateProcess(NULL,   // No module name (use command line)
	//	argv[1],        // Command line
	//	NULL,           // Process handle not inheritable
	//	NULL,           // Thread handle not inheritable
	//	FALSE,          // Set handle inheritance to FALSE
	//	0,              // No creation flags
	//	NULL,           // Use parent's environment block
	//	NULL,           // Use parent's starting directory 
	//	&si,            // Pointer to STARTUPINFO structure
	//	&pi)           // Pointer to PROCESS_INFORMATION structure
	//	)
	//{
	//	printf("CreateProcess failed (%d).\n", GetLastError());
	//	return 0;
	//}

	//// Wait until child process exits.
	//WaitForSingleObject(pi.hProcess, INFINITE);

	//// Close process and thread handles. 
	//CloseHandle(pi.hProcess);
	//CloseHandle(pi.hThread);
	
	return 0;
}
