#include "ProcessB.h"

double ProcessB::calc(char exp[])
{
	return evaluate.calc(exp);
}

double ProcessB::calc(const char* exp)
{
	return evaluate.calc(exp);
}

double ProcessB::calc() {
	if (this->expression == "")  return -1.0;
	this->res = calc(this->expression);
	cout << res;
}




void ProcessB::sendData(double* data, const char* shmName)
{
	SharedMemory* sharedMemory = new SharedMemory(shmName, false, 1024);
	sharedMemory->write(data);
	cout << "Noi dung data gui di" <<data <<"\n";
	//cout <<*(double*) data;
	cout << "____________________________";
}

void* ProcessB::getData(const char* shmName)
{
	cout << "Doc du lieu tu SharedMemory\n";
	SharedMemory* sharedMemory = new SharedMemory(shmName, false, 1024);
	void* res = (char*)sharedMemory->read();
	for (int i = 0; i < 10; i++) {
		cout << "Gia tri doc duoc: " << *((char*)res+i) << "\n";
	}
	return res;
}

void ProcessB::reset(const char* shmName) 
{
	SharedMemory* sharedMemory = new SharedMemory(shmName, false, 1024);
	sharedMemory->reset();
}

void ProcessB::process(const char* shmName)
{
	expression = (char*)getData(shmName);
	cout << "Process B giai " << expression << endl;
	calc();
	response = &res;
	cout << "Ket qua la " << *(double*)response << "\n";
	sendData(response, shmName);
}

int main(int argc, char* argv[]) {
	ProcessB* process2 = new ProcessB();
	while (true) {
		process2->process("SharedMemory1");
		process2->reset("SharedMemory1");
		system("pause");
	}	
}