#pragma once
#include <Windows.h>
#include <processthreadsapi.h>
class Process
{
	DWORD pid;
public:
	Process();
	void GUI();
	void sendData();
	void receiveData();
	DWORD getPid();
};

