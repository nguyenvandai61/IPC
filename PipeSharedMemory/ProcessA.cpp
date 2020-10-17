#include "ProcessA.h"

void ProcessA::run()
{
	// Gui bieu thuc sang
	sendData("6*3-2");
}
void ProcessA::sendData(const char* data) {
	SharedMemory* sharedMemory = new SharedMemory("SharedMemory1", true);
	for (int i = 0; i < 100; i++) {
		printf("Data[%d] = %d\n", i, data[i]);
	}
	sharedMemory->create(1024);
	sharedMemory->write(data);
	char* res = (char*) sharedMemory->read();
	cout << res;
}