#include "ProcessA.h"

void ProcessA::run()
{
	//// Gui bieu thuc sang
	//sendData("6*3-2");
}
void ProcessA::sendData(const char* data, const char* shmNames) {
	for (int i = 0; i < 5; i++) {
		printf("Proces A Data gui [%d] = %d\n", i, data[i]);
	}
	SharedMemory* sharedMemory = new SharedMemory(shmNames, false);
	sharedMemory->create(1024);
	sharedMemory->write(data);;
}

void* ProcessA::getData(const char* shmNames) {
	SharedMemory* sharedMemory = new SharedMemory(shmNames, false);
	void* res = sharedMemory->read();
	printf("Process get data: %lf\n", *(double*)res);
	return res;
}