#include <iostream>
#include <array>
#include <Windows.h>
#include "../Evaluate.h"

int main()
{
    Evaluate* evaluate = new Evaluate();
    char buffer[1024];
    HANDLE pipe = CreateNamedPipeA("\\\\.\\pipe\\Cryst", PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT, 1, sizeof(buffer), sizeof(buffer), NMPWAIT_USE_DEFAULT_WAIT, NULL);
    while (pipe != INVALID_HANDLE_VALUE) {
        if (ConnectNamedPipe(pipe, NULL)) {
         //Setting a breakpoint here will never trigger.
            DWORD bytesRead = 0;    
            DWORD bytesWritten;
            char* resultText;
            while (ReadFile(pipe, static_cast<LPVOID>(buffer), sizeof(buffer) - 1, &bytesRead, NULL)) {
                std::cout << buffer << std::endl;
                double result = evaluate->calc(buffer);
                std::cout << result << "\n";
                // Convert result to text
                resultText = (char*) (&result);
                WriteFile(pipe, static_cast<LPCVOID>(resultText), sizeof(resultText), &bytesWritten, NULL);
            }
        }
        DisconnectNamedPipe(pipe);
    }
    return 0;
}