#include "ProcessA.h"

void ProcessA::run()
{
	//// Gui bieu thuc sang
	//sendData("6*3-2");
}
void ProcessA::sendData(const char* data, const char* shmNames) {
	// for (int i = 0; i < 10; i++) {
	// 	printf("Proces A Data gui [%d] = %d\n", i, data[i]);
	// }
	SharedMemory* sharedMemory = new SharedMemory(shmNames, false, 1024);
	sharedMemory->create(1024);
	double len = strlen(data);
	double* lendouble = &len;
	//sharedMemory->write(lendouble);
	sharedMemory->write(data);
}

//void ProcessA::sendDataPipe(const char* data, const char* pipeName) {
//	for (int i = 0; i < 5; i++) {
//		printf("Proces A Data gui [%d] = %d\n", i, data[i]);
//	}
//
//	sharedMemory->create(1024);
//	sharedMemory->write(data);;
//}

void* ProcessA::getData(const char* shmNames) {
	SharedMemory* sharedMemory = new SharedMemory(shmNames, false, 1024);
	void* res = sharedMemory->read();
	printf("Process get data: %lf\n", *(double*)res);
	return res;
}

void* ProcessA::getDataPipe(const char*)
{
	return nullptr;
}

int main(int argc, char* argv[]) {
	SharedMemory* sharedMemory = new SharedMemory("SharedMemory1", true, 1024);
	ProcessA* process1 = new ProcessA();
	char mathExp[100];
	double res;
	std::cout << "Type math expression(q-quit): ";
	std::cin >> mathExp;
	strcat(mathExp, "\0");
	std::cout << strcmp(mathExp,"q");
	while (strcmp(mathExp,"q")!=0) {
		process1->sendData(mathExp, "SharedMemory1");
		system("pause");
		res = *(double*)process1->getData("SharedMemory1");
		cout << "Result: " << res << "\n";
		std::cout << "Type math expression(q-quit): ";
		std::cin >> mathExp;	
		strcat(mathExp, "\0");
	}
}
