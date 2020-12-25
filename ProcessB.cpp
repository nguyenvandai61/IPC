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



void ProcessB::run()
{
	for (int i = 3000; i < 6000; i++)
		std::cout << i << "\t\n";
}

void ProcessB::sendData(double* data, const char* shmName)
{
	SharedMemory* sharedMemory = new SharedMemory(shmName, false);
	sharedMemory->write(data);
	cout << "Noi dung data gui di" <<data <<"\n";
	//cout <<*(double*) data;
	cout << "____________________________";
}

void* ProcessB::getData(const char* shmName)
{
	cout << "Doc du lieu tu SharedMemory\n";
	SharedMemory* sharedMemory = new SharedMemory(shmName, false);
	void* res = (char*)sharedMemory->read();
	for (int i = 0; i < 10; i++) {
		cout << "Gia tri doc duoc: " << *((char*)res+i) << "\n";
	}
	return res;
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
	process2->process("SharedMemory1");
}