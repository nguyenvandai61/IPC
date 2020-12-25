#include "_Pipe.h"

_Pipe::_Pipe()
{
}
//
//void _Pipe::attach()
//{
//	if (pidIn = NULL)
//		pidIn = pid;
//	else if (pidOut = NULL)
//		pidOut = pid;
//	else
//		printf("Pipe het cho ket noi!");
//}
//
//
//void _Pipe::detach()
//{
//
//}
//
void *_Pipe::create(size_t bufsize)
{
    cout << "Creating a Pipe\n";
    int nMaxInstances = 1;
    LPSECURITY_ATTRIBUTES securAttrs = NULL;
    mappingHandle = CreateNamedPipe(name.c_str, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE, nMaxInstances, bufsize, bufsize, NMPWAIT_USE_DEFAULT_WAIT, securAttrs);
    if (mappingHandle == NULL || mappingHandle != INVALID_HANDLE_VALUE)
    {
        perror("Error");
        return 0;
    }
    // TODO: While at here
    if (ConnectNamedPipe(mappingHandle, NULL) != FALSE)
    {
        while (ReadFile(mappingHandle, p, ))
    }

    return nullptr;
}

void _Pipe::initBuf()
{
}

const char *_Pipe::readChar()
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

void _Pipe::writeChar(const char *str)
{
    pipeBuff.pushDataChar(str);
}
unsigned long _Pipe::getPid()
{
    unsigned long pid = GetCurrentProcessId();
    return pid;
}
