#include "_Pipe.h"

PipeBuf::PipeBuf() {
	currentSize = 0;
	size = PIPE_SIZE;
}
//TODO: Clean here
std::queue<const char*> PipeBuf::getBuffChar()
{
	return buffChar;
}
std::queue<double> PipeBuf::getBuffRes()
{
	return buffRes;
}
void PipeBuf::pushDataChar(const char* data)
{
	buffChar.push(data);
}
void PipeBuf::pushDataRes(double data)
{
	buffRes.push(data);
}
const char* PipeBuf::popDataChar()
{
	const char* temp = buffChar.front();
	buffChar.pop();
	return temp;
}
double PipeBuf::popDataRes()
{
	double temp = buffRes.front();
	buffRes.pop();
	return temp;
}
_Pipe::_Pipe() {
	printf("Buf duoc tao ra");
	PipeBuf pipeBuff();
}

void _Pipe::attach(unsigned long pid)
{
	if (pidIn = NULL)
		pidIn = pid;
	else if (pidOut = NULL)
		pidOut = pid;
	else
		printf("Pipe het cho ket noi!");
}


void _Pipe::detach()
{

}

void _Pipe::initBuf()
{

}

const char* _Pipe::readChar()
{
	return pipeBuff.popDataChar();
}

double _Pipe::readRes()
{
	return pipeBuff.popDataRes();
}

void _Pipe::writeRes(double value)
{
	pipeBuff.pushDataRes(value);
}

void _Pipe::writeChar(const char* str)
{
	pipeBuff.pushDataChar(str);
}
unsigned long _Pipe::getPid()
{
	unsigned long pid = GetCurrentProcessId();
	return pid;
}
